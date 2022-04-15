// A scheduler should maintain a task queue with some policy
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_SCHEDULERBASE_H
#define DIORDO_SCHEDULERBASE_H

#include "Task.h"

#include <mutex>
#include <optional>

namespace DiorDo {

class SchedulerBase {
public:
  SchedulerBase() = default;
  virtual bool is_preemptive() = 0;
  virtual std::optional<Task> pop_task() = 0;
  virtual bool submit_task(const Task &) = 0;
  virtual bool is_empty() = 0;

protected:
  std::mutex mutex_task_queue_;
};

} // namespace DiorDo

#endif // DIORDO_SCHEDULERBASE_H
