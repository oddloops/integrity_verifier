#include "ReadMode.h"
#include "AcceptedFSType.h"
#include <fstream>

bool ReadMode::run(std::filesystem::path const& snapshotPath) {
  _errorMessage.clear();
  if (!_core.validatePath(snapshotPath, AcceptedFSType::FILE)) {
    _errorMessage = "Invalid file: " + snapshotPath.string();
    return false;
  }

  std::ifstream ifs(snapshotPath);
  nlohmann::json j;
  ifs >> j;

  DirectoryContent dc = j.get<DirectoryContent>();
  
  _core.outputDirectoryContent(dc);
  return true;
}
