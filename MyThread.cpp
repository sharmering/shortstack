#include "MyThread.h"
#include <assert.h>

MyThread::MyThread() :tid_(0), isrunning_(false) {

}

void MyThread::start() {
    CHECK(!pthread_create(&tid_, NULL, MyThread::func, (void*)this));
    isrunning_ = true;
}

void MyThread::join() {
    assert(isrunning_ == true);
    CHECK(!pthread_join(tid_, NULL));
    isrunning_ = false;
}

void* MyThread::func(void* arg) {
    MyThread* t = (MyThread*)arg;
    t->callback_();

    return NULL;
}

MyThread::~MyThread() {
    if (isrunning_) {
        CHECK(!pthread_detach(tid_));
    }
}
