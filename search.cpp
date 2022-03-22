#include "search.h"

Search::Search(Input &input, State &state) : input(input), state(state) {}

void Search::start(unsigned int last_fluorochrom)
{
  placeFluorochrom(state.placed_fluorochroms, last_fluorochrom);
}

void Search::placeFluorochrom(unsigned int fluorochrom_number,
                              unsigned int last_fluorochrom)
{
  if (fluorochrom_number == last_fluorochrom) {
    state.placed_fluorochroms = last_fluorochrom;
    processState(state);
  } else {
    for (unsigned int i = 0; i < state.groups_count; i++) {
      unsigned long long collisions_backup;
      if (addToGroup(i, fluorochrom_number, collisions_backup)) {
        placeFluorochrom(fluorochrom_number + 1, last_fluorochrom);
        removeFromGroup(i, fluorochrom_number, collisions_backup);
        if (collisions_backup == 0) {
          break;
        }
      }
    }
  }
}

bool Search::addToGroup(unsigned int group_number,
                        unsigned int fluorochrom_number,
                        unsigned long long &collisions_backup)
{
  Group &group = state.groups[group_number];
  if ((group.collisions & (1ULL << fluorochrom_number))) {
    return false;
  }
  group.contains |= (1ULL << fluorochrom_number);
  collisions_backup = group.collisions;
  group.collisions |= input.getCollisions(fluorochrom_number);
  return true;
}

void Search::removeFromGroup(unsigned int group_number,
                             unsigned int fluorochrom_number,
                             unsigned long long &collisions_backup)
{
  Group &group = state.groups[group_number];
  group.contains &= ~(1ULL << fluorochrom_number);
  group.collisions = collisions_backup;
}
