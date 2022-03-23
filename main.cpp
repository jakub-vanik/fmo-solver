
#include "aggregator.h"
#include "expander.h"
#include "input.h"
#include "queue.h"
#include "worker.h"

#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "FmoSolver " << VERSION << std::endl << std::endl;
  if (argc == 3) {
    std::string input_path(argv[1]);
    std::string threshold(argv[2]);
    Input input(input_path, std::stof(threshold));
    for (unsigned int groups_count = 1;
         groups_count <= input.getFluorochromsCount(); groups_count++) {
      std::cout << "Trying " << groups_count << " groups" << std::endl;
      Queue queue(8);
      Aggregator aggregator(input);
      std::unique_ptr<Worker> workers[8];
      for (auto &worker : workers) {
        worker.reset(new Worker(input, queue, aggregator));
        worker->start();
      }
      State state = {0, groups_count};
      Expander expander(input, state, queue);
      expander.expand(input.getFluorochromsCount() / 2);
      queue.finish();
      for (auto &worker : workers) {
        worker->join();
      }
      aggregator.print();
    }
  } else {
    std::cout << "Incorrect arguments" << std::endl;
  }
  return 0;
}
