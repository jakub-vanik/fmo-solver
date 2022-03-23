#pragma once

#include <string>

class Error
{
public:
  Error(const std::string &message);
  const std::string &getMessage() const;

private:
  std::string message;
};
