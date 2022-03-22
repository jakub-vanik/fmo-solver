#pragma once

#include "input.h"
#include "state.h"

#include <mutex>

class Aggregator
{
public:
  Aggregator(Input &input);
  void propose(unsigned int solution_groups, unsigned int solution_value,
               float max_spread_sum, State &solution);
  void print();

private:
  Input &input;
  std::mutex mutex;
  unsigned int best_solution_groups;
  unsigned int best_solution_value;
  float best_max_spread_sum;
  State best_solution;
};
