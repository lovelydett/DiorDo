// Base class for all preemptive schedule algorithms
// Created by Yuting Xie
// 2022/4/15

#ifndef DIORDO_SCHEDULERPREEMPTIVE_H
#define DIORDO_SCHEDULERPREEMPTIVE_H

#include "SchedulerBase.h"

namespace DiorDo {

class SchedulerPreemptive : public SchedulerBase {
public:
  bool is_preemptive() override { return true; }
};

} // namespace DiorDo

#endif // DIORDO_SCHEDULERPREEMPTIVE_H
