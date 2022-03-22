
#include "queue.h"

Queue::Queue(unsigned int capacity) : capacity(capacity), finished(false) {}

void Queue::pushState(State &state)
{
  std::unique_lock<std::mutex> lock(mutex);
  while (states.size() >= capacity) {
    push_wait.wait(lock);
  }
  states.push(state);
  pull_wait.notify_one();
}

bool Queue::pullState(State &state)
{
  std::unique_lock<std::mutex> lock(mutex);
  while (states.empty()) {
    if (finished) {
      return false;
    }
    pull_wait.wait(lock);
  }
  state = states.front();
  states.pop();
  push_wait.notify_one();
  return true;
}

void Queue::finish()
{
  std::unique_lock<std::mutex> lock(mutex);
  finished = true;
  pull_wait.notify_all();
}
