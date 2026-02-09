#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>

#include "ValidateMessage.h"
#include "FileInfo.h"

class IntegrityCore
{
 public:
  ValidateMessage validateDirectory(const std::filesystem::path& targetDirectory);
  std::string computeHash(const std::filesystem::path& filePath);
  std::map<std::filesystem::path, FileInfo> getDirectoryContents(const std::filesystem::path& targetDirectory) const;
  bool readRecord(const std::string& recordFile) const;
};

#endif
