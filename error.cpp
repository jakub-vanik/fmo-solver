#include "error.h"

Error::Error(const std::string &message) : message(message) {}

const std::string &Error::getMessage() const
{
  return message;
}