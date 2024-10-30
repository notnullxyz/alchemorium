#include "scheduler.h"

Scheduler scheduler;

void Scheduler::addTask(std::function<void()> func, unsigned long interval, bool runOnce) {
  tasks.emplace_back(func, interval, runOnce);
}

void Scheduler::run() {
  unsigned long currentMillis = millis();
  for (auto& task : tasks) {
    if (currentMillis - task.lastRun >= task.interval) {
      task.function();
      task.lastRun = currentMillis;
      if (task.runOnce) {
        task = tasks.back();
        tasks.pop_back();
      }
    }
  }
}
