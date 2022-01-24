#pragma once

#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <functional>

#define CHECK(exp)\
    if(!exp) \
    { \
       fprintf(stderr,"file:%s,line:%d Exp:[" #exp "] not return 0\n",__FILE__,__LINE__);abort();\
    }

typedef std::function<void()> funcCallback;

class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}

private:
    // emphasize the following members are private
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

class MyThread : public noncopyable {
public:
    MyThread();
    ~MyThread();

    void join();
    void start();
    pthread_t getThreadId() {
        return tid_;
    }
    void setCallback(const funcCallback& c) {
        callback_ = c;
    }

private:
    static void* func(void* arg);

private:
    pthread_t tid_;
    bool isrunning_;
    funcCallback callback_;
};

