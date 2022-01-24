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
		//��lambda�������ݸ��̣߳����̺߳���
		std::thread([this, interval, task]() {

			//Сȱ�㣺��taskִ�еĹ���������tryToExpireΪtrue�Ļ�����Ҫ�ȵ�����taskִ����Ϻ���ܱ�while�����жϼ�⵽��
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

	void stop()//�ýӿڸ����޸�tryToExipired��ֵ��
	{
		// do not stop again
		if (expired)
			return;

		if (tryToExpire)
			return;

		// wait until timer 
		tryToExpire = true; // change this bool value to make timer while loop stop. This val is atomic type.

		std::unique_lock<std::mutex> locker(mut);
		cv.wait(locker, [this] {return expired == true; });//����lambda������this������ʹ�ó�Ա����expired!

		// reset the timer�� 
		//�ɹ�ֹͣ������tryToExpireΪfalse. ��ʵ�����Բ�ʹ��wait��������tryToExpire=false�Ķ����ŵ�
		//start��������whileѭ������Ϻ���������tryToExpireΪfalse��
		//���ǣ���������������������Ҳ�кô��ɣ�ʵ����tryToExipired��ֵ�����ɸ�stop�����������磬�����̳߳ɹ�������������Խ���һЩ������ƺ�����

		if (expired == true)
			tryToExpire = false;

	}

private:
	condition_variable cv;
	mutex mut;//��cv���

	atomic<bool> expired; //timer stop status
	atomic<bool> tryToExpire;//timer is in stop process.

};

/*
Note:

1��start����������һ���µ��̣߳���detach��������߳��������Ե�ִ��task��

����һ��std::thread�߳�ʱ����Ҫ����һ���ɵ��ö�������ʹ����lambda�������ǳ����㡣
start����������ǣ�����ʱ��ms, �Լ�һ��std::function<void()>


2) ʹ����c++11��ԭ�ӱ���automic<bool>, �ȽϷ��㡣


3)stop�����������Ǹ��Ѿ��������е������̷߳�һ��֪ͨ(ͨ���ı�һ��bool��Ա����)��Ȼ��ʹ��һ��conditon_variable����ȴ�״̬��

�����̻߳���ÿ��ִ����һ�ֵ�����ʱ���ñ�����ֵ�����ж��Ƿ�ֹͣ�� ֹͣ�󣬻�ʹ��condition_variable֪ͨstop�������õȴ��ˡ�
��������������������������������
��Ȩ����������ΪCSDN������Сɳ�뱴�ǡ���ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https ://blog.csdn.net/qq_35865125/article/details/109701454
*/
