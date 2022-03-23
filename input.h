#pragma once

#include "config.h"
#include "fluorochrom.h"

#include <string>

class Input
{
public:
  Input(const std::string &input_path, float threshold);
  unsigned int getFluorochromsCount();
  Fluorochrom &getFluorochrom(unsigned int fluorochrom_number);
  unsigned long long getCollisions(unsigned int fluorochrom_number);

private:
  unsigned int fluorochroms_count;
  Fluorochrom fluorochroms[Config::size];
  unsigned long long collisions[Config::size];
  void load(const std::string &input_path);
  void prepare(float threshold);
};
