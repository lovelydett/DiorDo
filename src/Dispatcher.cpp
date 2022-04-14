//
// Created by Yuting Xie
// 2022/4/13

#include "Dispatcher.h"

#include "FCFS/FcfsScheduler.h"

namespace DiorDo {

Dispatcher::Dispatcher() {
  // Todo(yuting): load config from file
  InitConfig();
}
bool Dispatcher::InitConfig() {
  // Todo(yuting): load from config file or from scheduler factory and capacity.
  scheduler_ = std::make_unique<FcfsScheduler>();
  time_slice_length_ms_ = 10;
  thread_pool_capacity_ = 100;
  return true;
}

bool Dispatcher::InitThreadPool() {
  thread_pool_.reserve(thread_pool_capacity_);
  for (int i = 0; i < thread_pool_capacity_; ++i) {
    thread_pool_.emplace_back(std::thread(&Dispatcher::thread_callback, this));
  }
  return true;
}

bool Dispatcher::submit_task(Task &task) {
  return scheduler_->submit_task(task);
}
void Dispatcher::thread_callback() {
  auto last = std::chrono::system_clock::now();
  while (true) {
    // First get a task
    auto task = scheduler_->pop_task();
    if (!task) {
      continue;
    }
    // Then do this task for a time slice. Todo(yuting): sync time slice
    last = std::chrono::system_clock::now();
    while (std::chrono::system_clock::now() - last <=
           std::chrono::milliseconds(time_slice_length_ms_)) {
      task->func();
    }
  }
}

} // namespace DiorDo