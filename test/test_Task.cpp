// Test cases for Task
// Created by Yuting Xie
// 2022/4/15

// Todo(yuting): use GTEST

#include "Task.h"
#include "logging.h"

int main() {
  int a = 1, b = 2, c = 3, d = 4, e = 5;

  DiorDo::Task task1(std::bind(
                         [=](int *pa, int *pb, int *pc) {
                           LOG_INFO("Doing task1");
                           *pc = *pa + *pb;
                         },
                         &a, &b, &c),
                     100, 200, 0);

  DiorDo::Task task2(std::bind(
                         [=](int *pa, int *pb) {
                           LOG_INFO("Doing task2");
                           *pa += *pb;
                           *pb = *pa - *pb;
                           *pa -= *pb;
                         },
                         &d, &e),
                     1000, 1500, 0);

  task1.func()();
  task2.func()();

  return 0;
}