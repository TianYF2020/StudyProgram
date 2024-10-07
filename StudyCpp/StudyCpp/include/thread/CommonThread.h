#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include "ThreadClass.h"
#include "ThreadAsync.h"

int TestMutex();
//测试线程同步条件变量
int TestThreadSync_condition_variable();


int testAtomic();

int testSemaphore();

int TestSemaphore();

int TestBarrier();