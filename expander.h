#pragma once

#include "input.h"
#include "queue.h"
#include "search.h"
#include "state.h"

class Expander : public Search
{
public:
  Expander(Input &input, State &state, Queue &queue);
  void expand(unsigned int last_fluorochrom);

private:
  Queue &queue;
  void processState(State &state);
};
