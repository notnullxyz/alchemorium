/*
 * Alchemorium - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>
#include <functional>
#include <vector>

// Sonnet helped me with this. Brain hurt.

class Task {
public:
  Task(std::function<void()> func, unsigned long interval, bool runOnce = false)
    : function(func), interval(interval), lastRun(0), runOnce(runOnce) {}

  std::function<void()> function;
  unsigned long interval;
  unsigned long lastRun;
  bool runOnce;
};

class Scheduler {
public:
  void addTask(std::function<void()> func, unsigned long interval, bool runOnce = false);
  void run();

private:
  std::vector<Task> tasks;
};

extern Scheduler scheduler;

#endif
