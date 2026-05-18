#include "ReadMode.h"
#include "AcceptedFSType.h"
#include <fstream>

bool ReadMode::run(ModeContext const& ctx) {
  _errorMessage.clear();
  if (!_core.validatePath(ctx.snapshotPath, AcceptedFSType::FILE)) {
    setErrorMsg("Invalid file: " + ctx.snapshotPath.string());
    return false;
  }

  std::ifstream ifs(ctx.snapshotPath);
  nlohmann::json j;
  ifs >> j;

  DirectoryContent dc = j.get<DirectoryContent>();
  
  _core.outputDirectoryContent(dc);
  return true;
}
