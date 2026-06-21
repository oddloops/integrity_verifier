#include "modes/VerifyMode.h"

#include <algorithm>
#include <fstream>
#include <iostream>

bool VerifyMode::run(ModeContext const& ctx) {
  if (!_core.validatePath(ctx.directoryPath, AcceptedFSType::DIRECTORY)) {
      setErrorMsg("Invalid directory path " + ctx.directoryPath.string());
  }
  if (!_core.validatePath(ctx.snapshotPath, AcceptedFSType::FILE)) {
    // no snapshot file exists at given path, create it
    if(!_writer.run(ctx)) {
      std::cerr << _writer.getErrorMsg();
      return false;
    }
  }
  return verifyRecord(ctx.directoryPath, ctx.snapshotPath);
}

bool VerifyMode::verifyRecord(std::filesystem::path const& directoryPath
			      ,std::filesystem::path const& recordPath) {
  std::ifstream in(recordPath);
  nlohmann::json j;
  in >> j;

  const DirectoryContent recordContent = j.get<DirectoryContent>();
  const DirectoryContent currentContent = _core.scanDirectory(directoryPath);

  if (!verifyTraversal(recordContent, currentContent)) {
    std::cerr << getErrorMsg();
    return false;
  }

  return true;
}

bool VerifyMode::verifyTraversal(DirectoryContent const& recordContent,
				 DirectoryContent const& currentContent) {
  // compare files
  for (const auto& recFile : recordContent.files) {
    auto it = std::find_if(currentContent.files.begin(),
			   currentContent.files.end(),
			   [&](FileInfo const& fi) { return fi.fileName == recFile.fileName; });

    if (it == currentContent.files.end()) {
      setErrorMsg("Missing file: " + recFile.fileName);
      return false;
    }

    const FileInfo& currentFile = *it;

    if (recFile.fileHash != currentFile.fileHash) {
      setErrorMsg("Mismatch hash: " + recFile.fileName);
      return false;
    }
  }

  // compare subdirectories
  for (const auto& recSub : recordContent.subdirectories) {
    std::string directoryName = recSub.directoryPath.string();

    auto it = std::find_if(currentContent.subdirectories.begin(),
			   currentContent.subdirectories.end(),
			   [&](DirectoryContent const& dc) { return dc.directoryPath.string() == directoryName; });

    if (it == currentContent.subdirectories.end()) {
      setErrorMsg("Missing directory: " + recSub.directoryPath.string());
      return false;
    }

    if (!verifyTraversal(recSub, *it)) {
      return false;
    }
  }

  return true;
}
