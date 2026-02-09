#ifndef FILEINFO_H
#define FILEINFO_H

#include <filesystem>
#include <chrono>
#include <string>

struct FileInfo {
  std::string fileName;
  std::filesystem::path filePath;
  std::string fileType;
  std::string fileExtension;
  std::string fileHash;
  std::chrono::time_point<std::chrono::system_clock> recordTimestamp;
};

#endif
