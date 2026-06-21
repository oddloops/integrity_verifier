#include "modes/ReadMode.h"
#include "models/AcceptedFSType.h"
#include <fstream>
#include <iostream>

// Only valid file name based will be snapshot.json
bool ReadMode::run(ModeContext const& ctx) {
  _errorMessage.clear();
  if (!_core.validatePath(ctx.snapshotPath, AcceptedFSType::FILE)) {
    setErrorMsg("Invalid file: " + ctx.snapshotPath.string());
    std::cerr << getErrorMsg();
    return false;
  }

  std::ifstream ifs(ctx.snapshotPath);
  nlohmann::json j;
  ifs >> j;

  DirectoryContent dc = j.get<DirectoryContent>();
  
  _core.outputDirectoryContent(dc);
  return true;
}
