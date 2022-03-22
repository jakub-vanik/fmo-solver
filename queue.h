#pragma once

#include "state.h"

#include <condition_variable>
#include <mutex>
#include <queue>

class Queue
{
public:
  Queue(unsigned int capacity);
  void pushState(State &state);
  bool pullState(State &state);
  void finish();

private:
  unsigned int capacity;
  bool finished;
  std::mutex mutex;
  std::condition_variable push_wait;
  std::condition_variable pull_wait;
  std::queue<State> states;
};
