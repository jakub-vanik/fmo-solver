#pragma once

#include "aggregator.h"
#include "input.h"
#include "queue.h"

#include <thread>

class Worker
{
public:
  Worker(Input &input, Queue &queue, Aggregator &aggregator);
  void start();
  void join();

private:
  Input &input;
  Queue &queue;
  Aggregator &aggregator;
  std::thread thread;
};
