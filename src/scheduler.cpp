/*
 * Alchemorium - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

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
    }
  }
  
  tasks.erase(
    std::remove_if(tasks.begin(), tasks.end(), 
      [](const Task& task) { return task.runOnce && (millis() - task.lastRun >= task.interval); }),
    tasks.end()
  );
}
