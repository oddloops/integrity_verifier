#ifndef READMODE_H
#define READMODE_H

#include "IntegrityCore.h"
#include "DirectoryContent.h"

#include <filesystem>
#include <string>

class ReadMode
{
 public:
  explicit ReadMode (IntegrityCore& core) : _core(core){}
  bool run(std::filesystem::path const& snapshotPath);
  std::string getErrorMessage() const { return _errorMessage; }
  
 private:
  IntegrityCore& _core;
};

#endif
