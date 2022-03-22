#include "solver.h"

Solver::Solver(Input &input, State &state, Aggregator &aggregator) :
  Search(input, state), input(input), aggregator(aggregator)
{
}

void Solver::solve()
{
  start(input.getFluorochromsCount());
}

void Solver::processState(State &state)
{
  int solution_value = 0;
  float max_spread_sum = 0;
  for (unsigned int i = 0; i < state.groups_count; i++) {
    int count = 0;
    float max_spread = 0;
    for (unsigned int j = 0; j < input.getFluorochromsCount(); j++) {
      if (state.groups[i].contains & (1ULL << j)) {
        count++;
        for (unsigned int k = 0; k < input.getFluorochromsCount(); k++) {
          if (state.groups[i].contains & (1ULL << k)) {
            float spred = input.getFluorochrom(j).spreads[k];
            if (spred > max_spread) {
              max_spread = spred;
            }
          }
        }
      }
    }
    solution_value += count * count;
    max_spread_sum += max_spread;
  }
  aggregator.propose(state.groups_count, solution_value, max_spread_sum, state);
}
