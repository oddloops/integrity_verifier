#ifndef INTEGRITY_CORE_H
#define INTEGRITY_CORE_H

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <sys/types.h>

#include "ValidateMessage.h"
#include "FileInfo.h"

class IntegrityCore
{
 public:
  bool validateDirectory(std::filesystem::path const& targetDirectory) const;
  std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> getDirectoryContents(std::filesystem::path const& targetDirectory) const;
  std::string computeHash(std::filesystem::path const& filePath) const;
  FileInfo createFileInfo(std::filesystem::path const& directory_entry) const;
  bool readRecord(std::string const& recordFile) const;

private:
  void setFileInfo(FileInfo& fi, std::filesystem::path const& p);
  std::string getFileName(std::filesystem::path& p) const;
  std::string getFileExtension(std::filesystem::path const& p) const;
  u_int64_t getFileSize(std::filesystem::path const& p) const;
  std::filesystem::perms getPermissions(std::filesystem::path const& p) const;
  std::chrono::time_point<std::chrono::system_clock> getLastModifiedTime(std::filesystem::path const& p) const;
  std::chrono::time_point<std::chrono::system_clock> setRecordTime(std::filesystem::path const& p) const;
};

#endif
