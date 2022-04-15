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
  // Todo(yuting): should be equal to number of CPU cores.
  thread_pool_capacity_ = 1;
  is_preemptive = scheduler_->is_preemptive();
  LOG_INFO("Leave %s", __FUNCTION__);
  return true;
}

bool Dispatcher::InitThreadPool() {
  LOG_INFO("Enter %s", __FUNCTION__);
  thread_pool_.reserve(thread_pool_capacity_);
  for (int i = 0; i < thread_pool_capacity_; ++i) {
    // Todo(yuting): should assign each thread to each CPU core.
    thread_pool_.emplace_back(std::thread(&Dispatcher::thread_callback, this));
  }
  LOG_INFO("Leave %s", __FUNCTION__);
  return true;
}

bool Dispatcher::submit_task(Task &task) {
  // Fixme(yuting): this feels weird, should move set_submit_time into scheduler
  task.set_submit_time();
  if (!scheduler_->submit_task(task)) {
    return false;
  }
  return true;
}

void Dispatcher::join_threads() {
  for (auto &thread : thread_pool_) {
    thread.join();
  }
}

void Dispatcher::thread_callback() {
  LOG_INFO("Thread %d starts", std::this_thread::get_id());
  auto last = std::chrono::steady_clock::now();
  while (true) {
    // First get a task
    auto task = scheduler_->pop_task();
    if (!task) {
      continue;
    }
    LOG_INFO("Thread %d assigned a task and starts its time slice",
             std::this_thread::get_id());
    last = std::chrono::steady_clock::now();
    while (true) {
      // Do the actual job
      task->func()();

      // On finishing a single time slice
      if (std::chrono::steady_clock::now() - last >=
          std::chrono::milliseconds(time_slice_length_ms_)) {
        last = std::chrono::steady_clock::now();
        // Update remaining time
        task->execute_for(time_slice_length_ms_);
        task->update_turnaround_time();
        // If in preemptive case or the task has finished, break the loop
        if (is_preemptive || task->is_finished()) {
          break;
        }
      }
    }
    if (task->is_finished()) {
      LOG_INFO("A task (ET=%dms, RT=%dms, DDL=%dms) is finished in %dms after "
               "submission",
               task->get_execution_time_ms(), task->get_remaining_time_ms(),
               task->get_deadline_ms(), task->get_turnaround_time_ms());
    }
    if (is_preemptive && !task->is_finished()) {
      // In the preemptive case, the task may have not finished, recycle it
      scheduler_->submit_task(*task);
    }
  }
}

} // namespace DiorDo