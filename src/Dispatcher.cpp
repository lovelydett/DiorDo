//
// Created by Yuting Xie
// 2022/4/13

#include "Dispatcher.h"

#include "FCFS/FcfsScheduler.h"

namespace DiorDo {

Dispatcher::Dispatcher() {
  // Todo(yuting): load config from file
  InitConfig();
}
bool Dispatcher::InitConfig() {
  // Todo(yuting): load from config file or from scheduler factory.
  scheduler_ = std::make_unique<FcfsScheduler>();
  time_slice_length_ms_ = 10;
  return true;
}
bool Dispatcher::submit_task(Task &task) {
  return scheduler_->submit_task(task);
}
void Dispatcher::run_one_time_slice() {}

} // namespace DiorDo