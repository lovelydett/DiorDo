//
// Created by Yuting Xie
// 2022/4/13

#include "Dispatcher.h"

#include "FCFS/FcfsScheduler.h"

#include "../logging/logging.h"

namespace DiorDo {

Dispatcher::Dispatcher() {
  LOG_INFO("Enter %s", __FUNCTION__);
  // Todo(yuting): load config from file
  InitConfig();
  InitThreadPool();
}
bool Dispatcher::InitConfig() {
  LOG_INFO("Enter %s", __FUNCTION__);
  // Todo(yuting): load from config file or from scheduler factory and capacity.
  scheduler_.reset((SchedulerBase *)new FcfsScheduler);
  time_slice_length_ms_ = 100;
  thread_pool_capacity_ = 10;
  is_preemptive = scheduler_->is_preemptive();
  LOG_INFO("Leave %s", __FUNCTION__);
  return true;
}

bool Dispatcher::InitThreadPool() {
  LOG_INFO("Enter %s", __FUNCTION__);
  thread_pool_.reserve(thread_pool_capacity_);
  for (int i = 0; i < thread_pool_capacity_; ++i) {
    thread_pool_.emplace_back(std::thread(&Dispatcher::thread_callback, this));
  }
  LOG_INFO("Leave %s", __FUNCTION__);
  return true;
}

bool Dispatcher::submit_task(Task &task) {
  return scheduler_->submit_task(task);
}

void Dispatcher::join_threads() {
  for (auto &thread : thread_pool_) {
    thread.join();
  }
}

void Dispatcher::thread_callback() {
  LOG_INFO("Thread %d starts", std::this_thread::get_id());
  auto last = std::chrono::system_clock::now();
  while (true) {
    // First get a task
    auto task = scheduler_->pop_task();
    if (!task) {
      continue;
    }
    LOG_INFO("Thread %d assigned a task and starts its time slice",
             std::this_thread::get_id());
    // Then do this task for a time slice. Todo(yuting): sync time slice
    last = std::chrono::system_clock::now();
    while (!is_preemptive ||
           std::chrono::system_clock::now() - last <=
               std::chrono::milliseconds(time_slice_length_ms_)) {
      task->func()();
    }
    LOG_INFO("End of time slice for thread %d", std::this_thread::get_id());
  }
}

} // namespace DiorDo