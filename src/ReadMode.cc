#include "ReadMode.h"
#include "AcceptedFSType.h"

bool ReadMode::run(std::filesystem::path const& snapshotPath) {
  _errorMessage.clear();
  if (!_core.validatePath(snapshotPath, AcceptedFSType::FILE)) {
    _errorMessage = "Invalid file: " + snapshotPath.string();
    return false;
  }

  _core.outputDirectoryContent(snapshotPath);
  return true;
}
