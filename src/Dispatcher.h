// Dispatcher owns a thread pool and decides which task to perform
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_DISPATCHER_H
#define DIORDO_DISPATCHER_H

#define _GNU_SOURCE /* See feature_test_macros(7) */

#include <memory>
#include <queue>
#include <sched.h> // For assign thread to CPU core
#include <thread>
#include <vector>

#include "Scheduler.h"
#include "Task.h"

namespace DiorDo {

class Dispatcher {
public:
  Dispatcher();
  Dispatcher(Dispatcher const &) = delete;
  Dispatcher &operator=(Dispatcher const &) = delete;

private:
  bool InitConfig();

private:
  std::vector<std::thread> thread_pool_;
  Scheduler *scheduler;

public:
  bool submit_task(Task &task);
};

} // namespace DiorDo

#endif // DIORDO_DISPATCHER_H
