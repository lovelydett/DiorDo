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
  Task(const std::function<void()> func, unsigned int execution_time_ms,
       unsigned int deadline_ms, const unsigned int priority)
      : priority_(priority), func_(func), execution_time_ms_(execution_time_ms),
        remaining_time_ms_(execution_time_ms), deadline_ms_(deadline_ms) {}

public:
  [[nodiscard]] std::function<void()> func() const { return func_; }
  [[nodiscard]] bool is_deadline_missed() const {
    return std::chrono::steady_clock::now() > submit_timepoint_ + deadline_ms_;
  }
  [[nodiscard]] bool is_finished() const {
    return remaining_time_ms_ <= std::chrono::milliseconds(0);
  }
  void set_submit_time() {
    // Call this func when officially take it into scheduler's account
    submit_timepoint_ = std::chrono::steady_clock::now();
  }
  void update_turnaround_time() {
    turnaround_time_ms_ = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - submit_timepoint_);
  }
  void execute_for(unsigned int time_slice_ms) {
    remaining_time_ms_ -= std::chrono::milliseconds(time_slice_ms);
  }

  [[nodiscard]] long get_deadline_ms() const { return deadline_ms_.count(); }
  [[nodiscard]] long get_remaining_time_ms() const {
    return remaining_time_ms_.count();
  }
  [[nodiscard]] long get_execution_time_ms() const {
    return execution_time_ms_.count();
  }
  [[nodiscard]] long get_turnaround_time_ms() const {
    return turnaround_time_ms_.count();
  }

private:
  // Actual task, should already be bind, and ready to execute and pause at any
  // point!
  std::function<void()> func_;
  // The smaller the prior
  unsigned int priority_;

  // Submission timestamp
  std::chrono::time_point<std::chrono::steady_clock> submit_timepoint_;

  // Expected execution time in ms
  std::chrono::milliseconds execution_time_ms_;

  // Turnaround time in ms
  std::chrono::milliseconds turnaround_time_ms_;

  // Remaining time to execute in ms
  std::chrono::milliseconds remaining_time_ms_;

  // Deadline in ms
  std::chrono::milliseconds deadline_ms_;
};

} // namespace DiorDo

#endif // DIORDO_TASK_H
