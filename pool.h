/*** 
 * @Author: Jacob-biu 2777245228@qq.com
 * @Date: 2023-06-03 01:34:26
 * @LastEditors: Jacob-biu 2777245228@qq.com
 * @LastEditTime: 2023-06-03 01:39:50
 * @FilePath: /http_web_file_server_dev/threadpool.h
 * @Description: 
 * @Copyright (c) 2023 by Jacob John, All Rights Reserved. 
 */
#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <queue>
#include <stdexcept>

#include <pthread.h>
#include <semaphore.h>

#include "event.h"

static int tnum = 0;
class ThreadPool{
public:
    // 初始化线程池、互斥访问时间队列的互斥量、表示队列中事件的信号量
    ThreadPool(int threadNum);
    ~ThreadPool();
public:
    // 向事件队列中添加一个待处理的事件，线程池中的线程会循环处理其中的事件
    int appendEvent(EventBase* event, const std::string eventType);

private:
    // 创建线程时指定的运行函数，参数传递 this，实现在子线程中可以访问到该对象的成员
    static void *worker(void *arg);
    
    // 在线程中执行该函数等待处理事件队列中的事件
    void run();

private:
    int m_threadNum;                  // 线程池中的线程个数
    pthread_t *m_threads;             // 保存线程池中的所有线程
    
    std::queue<EventBase*> m_workQueue;  // 保存所有待处理的事件
    pthread_mutex_t queueLocker;     // 用于互斥访问事件队列的锁
    sem_t queueEventNum;             // 表示队列中事件个数变化的信号量

};

#endif
