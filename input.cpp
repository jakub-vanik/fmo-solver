#include "input.h"

#include "error.h"

#include <fstream>
#include <sstream>
#include <vector>

Input::Input(const std::string &input_path, float threshold) :
  fluorochroms_count(0), fluorochroms{}, collisions{}
{
  load(input_path);
  prepare(threshold);
}

unsigned int Input::getFluorochromsCount()
{
  return fluorochroms_count;
}

Fluorochrom &Input::getFluorochrom(unsigned int fluorochrom_number)
{
  return fluorochroms[fluorochrom_number];
}

unsigned long long Input::getCollisions(unsigned int fluorochrom_number)
{
  return collisions[fluorochrom_number];
}

void Input::load(const std::string &input_path)
{
  std::ifstream input_file;
  input_file.open(input_path);
  if (input_file.fail()) {
    throw Error("Unable to read input file!");
  }
  unsigned int expected_count = 0;
  std::string line;
  while (std::getline(input_file, line)) {
    std::stringstream stream(line);
    std::vector<std::string> parts;
    std::string part;
    while (std::getline(stream, part, '\t')) {
      parts.push_back(part);
    }
    if (!parts.empty()) {
      if (fluorochroms_count >= Config::size) {
        throw Error("Too many fluorochroms!");
      }
      unsigned int spreads_count = parts.size() - 1;
      if (spreads_count > Config::size) {
        throw Error("Too many fluorochroms!");
      }
      if (fluorochroms_count == 0) {
        expected_count = spreads_count;
      }
      if (spreads_count != expected_count) {
        throw Error("Not a square matrix!");
      }
      auto &fluorochrom = fluorochroms[fluorochroms_count++];
      fluorochrom.name = parts[0];
      for (unsigned int i = 0; i < spreads_count; i++) {
        fluorochrom.spreads[i] = std::stof(parts[i + 1]);
      }
    }
  }
  if (fluorochroms_count == 0) {
    throw Error("Empty input!");
  }
  if (fluorochroms_count != expected_count) {
    throw Error("Not a square matrix!");
  }
}

void Input::prepare(float threshold)
{
  for (unsigned int i = 0; i < fluorochroms_count; i++) {
    for (unsigned int j = 0; j < fluorochroms_count; j++) {
      float max_spread =
          std::max(fluorochroms[i].spreads[j], fluorochroms[j].spreads[i]);
      fluorochroms[i].spreads[j] = max_spread;
      fluorochroms[j].spreads[i] = max_spread;
      if (max_spread > threshold) {
        collisions[i] |= (1ULL << j);
        collisions[j] |= (1ULL << i);
      }
    }
  }
}
