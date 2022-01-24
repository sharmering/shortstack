#pragma once
#include <iostream>
#include <mutex>
#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>

using namespace std;
class MyTimer {

public:
	MyTimer() {
		expired = true;
		tryToExpire = false;
	}

	//interval: ms
	void start(int interval, std::function<void()> task)
	{

		if (expired == false)//has already started, do not start again
			return;

		// start async timer, launch thread and wait in that thread
		expired = false;
		//将lambda函数传递给线程，做线程函数
		std::thread([this, interval, task]() {

			//小缺点：在task执行的过程中设置tryToExpire为true的话，需要等到本次task执行完毕后才能被while条件判断检测到。
			while (!tryToExpire)
			{
				// sleep every interval and do the task again and again until times up
				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
				task(); //call this function every interval milliseconds.
			}

			// timer be stopped, update the condition variable expired and wake main thread
			std::lock_guard<std::mutex> locker(mut);
			expired = true;
			cv.notify_one();

			}).detach();
	}

	void stop()//该接口负责修改tryToExipired的值。
	{
		// do not stop again
		if (expired)
			return;

		if (tryToExpire)
			return;

		// wait until timer 
		tryToExpire = true; // change this bool value to make timer while loop stop. This val is atomic type.

		std::unique_lock<std::mutex> locker(mut);
		cv.wait(locker, [this] {return expired == true; });//不给lambda函数串this，不能使用成员变量expired!

		// reset the timer， 
		//成功停止后，设置tryToExpire为false. 其实，可以不使用wait动作，将tryToExpire=false的动作放到
		//start函数，当while循环被打断后，立即设置tryToExpire为false。
		//但是，这样单独放在这里设置也有好处吧，实现了tryToExipired的值仅仅由该stop函数负责。例如，任务线程成功结束后，这里可以进行一些额外的善后动作，

		if (expired == true)
			tryToExpire = false;

	}

private:
	condition_variable cv;
	mutex mut;//与cv配合

	atomic<bool> expired; //timer stop status
	atomic<bool> tryToExpire;//timer is in stop process.

};

/*
Note:

1）start函数，开辟一个新的线程，并detach，在这个线程中周期性地执行task。

建立一个std::thread线程时，需要传入一个可调用对象，这里使用了lambda函数，非常方便。
start函数的入参是，周期时间ms, 以及一个std::function<void()>


2) 使用了c++11的原子变量automic<bool>, 比较方便。


3)stop函数的作用是给已经正在运行的任务线程发一个通知(通过改变一个bool成员变量)，然后使用一个conditon_variable进入等待状态。

任务线程会在每次执行新一轮的任务时检查该变量的值，并判断是否停止， 停止后，会使用condition_variable通知stop函数不用等待了。
————————————————
版权声明：本文为CSDN博主「小沙与贝壳」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/qq_35865125/article/details/109701454
*/
