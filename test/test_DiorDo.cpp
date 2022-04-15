// Simple tests.
// Created by Yuting Xie
// 2022/4/14

#include "../src/Dispatcher.h"

#include "../logging/logging.h"

#include <cstdio>
#include <functional>

// Simple addition
void test_func_1(int *pa, int *pb, int *pc) { *pc = *pa + *pb; }

// Simple swap
void test_func_2(int *pa, int *pb) {
  *pa += *pb;
  *pb = *pa - *pb;
  *pa -= *pb;
}

int main() {
  int a = 1, b = 2, c, d = 1, e = 2;

  LOG_INFO("Initializing tasks");

  DiorDo::Task task1(std::bind(test_func_1, &a, &b, &c), 0);
  DiorDo::Task task2(std::bind(test_func_2, &d, &e), 0);

  LOG_INFO("Tasks initialized");

  DiorDo::Dispatcher dispatcher;

  LOG_INFO("Submitting task 1");
  dispatcher.submit_task(task1);
  LOG_INFO("Submitting task 2");
  dispatcher.submit_task(task2);

  dispatcher.join_threads();

  return 0;
}