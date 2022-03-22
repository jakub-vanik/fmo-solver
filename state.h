#pragma once

#include "group.h"
#include "input.h"

struct State
{
  unsigned int placed_fluorochroms;
  unsigned int groups_count;
  Group groups[Config::size];
};
