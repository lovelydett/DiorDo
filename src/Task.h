// Base class for tasks
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_TASK_H
#define DIORDO_TASK_H

#include <chrono>
#include <functional>

namespace DiorDo {

class Task {
public:
  Task() = delete;
  Task(const std::function<void()> func) { func_ = func; }

public:
  std::function<void()> func() const { return func_; }
  std::chrono::duration<int, std::ratio<1, 1000>> time_since_summit() {
    return std::chrono::system_clock::now() - time_submit_;
  }

private:
  // Actual task, should already be bind and ready to execute
  std::function<void()> func_;
  // The smaller the prior
  unsigned int priority;
  std::chrono::system_clock::time_point time_submit_;
};

} // namespace DiorDo

#endif // DIORDO_TASK_H
