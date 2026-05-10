#ifndef DIRECTORY_CONTENT_H
#define DIRECTORY_CONTENT_H

#include <filesystem>
#include <vector>

#include "FileInfo.h"

#include <nlohmann/json.hpp>

struct DirectoryContent {
  std::filesystem::path directoryPath;
  std::vector<FileInfo> files;
  std::vector<DirectoryContent> subdirectories;
};

void to_json(nlohmann::json& j, DirectoryContent const& dc);
void from_json(nlohmann::json const& j, DirectoryContent& dc);

#endif
