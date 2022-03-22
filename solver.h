#pragma once

#include "aggregator.h"
#include "input.h"
#include "search.h"
#include "state.h"

class Solver : public Search
{
public:
  Solver(Input &input, State &state, Aggregator &aggregator);
  void solve();

private:
  Input &input;
  Aggregator &aggregator;
  void processState(State &state);
};
