#include "aggregator.h"

#include <iostream>
#include <limits>

Aggregator::Aggregator(Input &input) :
  input(input),
  best_solution_groups(std::numeric_limits<int>::max()),
  best_solution_value(0),
  best_max_spread_sum(0.0f),
  best_solution{}
{
}

void Aggregator::propose(unsigned int solution_groups,
                         unsigned int solution_value, float max_spread_sum,
                         State &solution)
{
  std::unique_lock<std::mutex> lock(mutex);
  if (solution_groups > best_solution_groups) {
    return;
  }
  if (solution_groups == best_solution_groups &&
      solution_value > best_solution_value) {
    return;
  }
  if (solution_groups == best_solution_groups &&
      solution_value == best_solution_value &&
      max_spread_sum >= best_max_spread_sum) {
    return;
  }
  best_solution_groups = solution_groups;
  best_solution_value = solution_value;
  best_max_spread_sum = max_spread_sum;
  best_solution = solution;
}

void Aggregator::print()
{
  if (best_solution_groups != std::numeric_limits<int>::max()) {
    std::cout << "Solution:" << std::endl;
    for (unsigned int i = 0; i < best_solution_groups; i++) {
      std::cout << "|";
      for (unsigned int j = 0; j < input.getFluorochromsCount(); j++) {
        if (best_solution.groups[i].contains & (1ULL << j)) {
          std::cout << "X";
        } else {
          std::cout << " ";
        }
      }
      std::cout << "|";
      for (unsigned int j = 0; j < input.getFluorochromsCount(); j++) {
        if (best_solution.groups[i].contains & (1ULL << j)) {
          std::cout << " " << input.getFluorochrom(j).name;
        }
      }
      std::cout << std::endl;
    }
    std::cout << "Max spread sum: " << best_max_spread_sum << std::endl;
  } else {
    std::cout << "No solution!" << std::endl;
  }
  std::cout << std::endl;
}