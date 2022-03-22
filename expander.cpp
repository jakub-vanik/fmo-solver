#include "expander.h"

Expander::Expander(Input &input, State &state, Queue &queue) :
  Search(input, state), queue(queue)
{
}

void Expander::expand(unsigned int last_fluorochrom)
{
  start(last_fluorochrom);
}

void Expander::processState(State &state)
{
  queue.pushState(state);
}
