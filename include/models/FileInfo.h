#ifndef FILEINFO_H
#define FILEINFO_H

#include <nlohmann/json.hpp>

#include <filesystem>
#include <chrono>
#include <string>
#include <sys/types.h>

struct FileInfo {
  std::string fileName;
  std::filesystem::path filePath;
  std::string fileExtension;
  u_int64_t fileSize;
  std::filesystem::perms permissions;
  std::string fileHash;
  std::filesystem::file_time_type lastModified;
  std::chrono::time_point<std::chrono::system_clock> recordTimestamp;
};

void to_json(nlohmann::json& j, FileInfo const& fi);
void from_json(nlohmann::json const& j, FileInfo& fi);

#endif
