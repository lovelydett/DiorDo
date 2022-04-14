// Simple tests.
// Created by Yuting Xie
// 2022/4/14

#include "../src/Dispatcher.h"

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
  DiorDo::Task task1(std::bind(test_func_1, &a, &b, &c));
  DiorDo::Task task2(std::bind(test_func_2, &d, &e));

  DiorDo::Dispatcher dispatcher;
  dispatcher.submit_task(task1);
  dispatcher.submit_task(task2);

  return 0;
}