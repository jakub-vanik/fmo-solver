#pragma once

#include "input.h"
#include "state.h"

class Search
{
public:
  Search(Input &input, State &state);

protected:
  void start(unsigned int last_fluorochrom);
  virtual void processState(State &state) = 0;

private:
  Input &input;
  State state;
  void placeFluorochrom(unsigned int fluorochrom_number,
                        unsigned int last_fluorochrom);
  bool addToGroup(unsigned int group_number, unsigned int fluorochrom_number,
                  unsigned long long &collisions_backup);
  void removeFromGroup(unsigned int group_number,
                       unsigned int fluorochrom_number,
                       unsigned long long &collisions_backup);
};
