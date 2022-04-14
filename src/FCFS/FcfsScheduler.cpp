//
// Created by Yuting Xie
// 2022/4/13

#include "FcfsScheduler.h"

namespace DiorDo {

std::optional<Task> FcfsScheduler::pop_task() {
  std::lock_guard<mutex_task_queue_> lock;
  if (task_queue_.empty()) {
    return std::nullopt;
  }
  auto task = task_queue_.top();
  task_queue_.pop();
  return task;
}
bool FcfsScheduler::submit_task(const Task &) {
  std::lock_guard<mutex_task_queue_> lock;
  task_queue_.emplace(task);
  return true;
}
bool FcfsScheduler::is_empty() { return task_queue_.size() == size_t(0); }

} // namespace DiorDo