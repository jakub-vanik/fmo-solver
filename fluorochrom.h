#pragma once

#include "config.h"

#include <string>

struct Fluorochrom
{
  std::string name;
  float spreads[Config::size];
};
