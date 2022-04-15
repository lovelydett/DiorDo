//
// Created by Yuting Xie
// 2022/4/15

#ifndef DIORDO_SCHEDULERNONPREEMPTIVE_H
#define DIORDO_SCHEDULERNONPREEMPTIVE_H

#include "SchedulerBase.h"

namespace DiorDo {

class SchedulerNonPreemptive : public SchedulerBase {
public:
  bool is_preemptive() override { return false; }
};

} // namespace DiorDo

#endif // DIORDO_SCHEDULERNONPREEMPTIVE_H
