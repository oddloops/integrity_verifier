#include <string.h>

#include "DirectoryContent.h"

void to_json(nlohmann::json& j, DirectoryContent const& dc) {
  j = {
    {"directoryPath", dc.directoryPath},
    {"files", dc.files},
    {"subdirectories", dc.subdirectories}
  };
}

void from_json(nlohmann::json const& j, DirectoryContent& dc) {
  std::string pathStr;
  j.at("directoryPath").get_to(pathStr);
  dc.directoryPath = pathStr;

  j.at("files").get_to(dc.files);

  j.at("subdirectories").get_to(dc.subdirectories);
}
