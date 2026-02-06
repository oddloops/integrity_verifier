#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <string>

class IntegrityCore
{
 public:
  bool validateDirectory(const std::filesystem::path& targetDirectory);
};

#endif
