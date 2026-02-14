#ifndef FILEINFO_H
#define FILEINFO_H

#include <filesystem>
#include <chrono>
#include <string>
#include <sys/types.h>

struct FileInfo {
  std::string fileName;
  std::filesystem::path filePath;
  std::string fileExtension;
  u_int64_t fileSize;
  std::string fileHash;
  std::chrono::time_point<std::chrono::system_clock> lastModified;
  std::chrono::time_point<std::chrono::system_clock> recordTimestamp;
  std::filesystem::perms permissions;
};

#endif
