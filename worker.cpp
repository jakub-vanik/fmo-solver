#include "worker.h"

#include "solver.h"
#include "state.h"

Worker::Worker(Input &input, Queue &queue, Aggregator &aggregator) :
  input(input), queue(queue), aggregator(aggregator)
{
}

void Worker::start()
{
  thread = std::thread([this]() {
    State state;
    while (queue.pullState(state)) {
      Solver solver(input, state, aggregator);
      solver.solve();
    }
  });
}

void Worker::join()
{
  thread.join();
}
