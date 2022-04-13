//
// Created by Yuting Xie
// 2022/4/13

#include "FcfsScheduler.h"

namespace DiorDo {

Task FcfsScheduler::pop_task() {
  auto task = task_queue_.top();
  task_queue_.pop();
  return task;
}
bool FcfsScheduler::submit_task(const Task &) {
  task_queue_.emplace(task);
  return true;
}
bool FcfsScheduler::is_empty() { return task_queue_.size() == size_t(0); }

} // namespace DiorDo