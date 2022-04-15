//
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_FCFSSCHEDULER_H
#define DIORDO_FCFSSCHEDULER_H

#include "queue"

#include "SchedulerNonPreemptive.h"

namespace DiorDo {

class FcfsScheduler : public SchedulerNonPreemptive {
public:
  FcfsScheduler() = default;

public:
  std::optional<Task> pop_task() override;
  bool submit_task(const Task &task) override;
  bool is_empty() override;

private:
  std::queue<Task> task_queue_;
};

} // namespace DiorDo

#endif // DIORDO_FCFSSCHEDULER_H
