// A scheduler should maintain a task queue with some policy
// Created by Yuting Xie
// 2022/4/13

#ifndef DIORDO_SCHEDULER_H
#define DIORDO_SCHEDULER_H

#include "Task.h"

namespace DiorDo {

class Scheduler {
public:
  virtual Task pop_task() = 0;
};

} // namespace DiorDo

#endif // DIORDO_SCHEDULER_H
