// Dispatcher owns a thread pool and decides which task to perform
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_DISPATCHER_H
#define DIORDO_DISPATCHER_H

#define _GNU_SOURCE /* See feature_test_macros(7) */

#include <chrono>
#include <memory>
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

public:
  bool submit_task(Task &task);
  void join_threads();

private:
  std::vector<std::thread> thread_pool_;
  std::shared_ptr<Scheduler> scheduler_;
  unsigned int thread_pool_capacity_;
  unsigned int time_slice_length_ms_;

private:
  bool InitConfig();
  bool InitThreadPool();

  // This is what the thread actually runs.
  void thread_callback();
};

} // namespace DiorDo

#endif // DIORDO_DISPATCHER_H
