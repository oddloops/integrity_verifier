#include "modes/WriteMode.h"
#include "models/AcceptedFSType.h"
#include <iostream>
#include <nlohmann/json.hpp>

#include <fstream>

bool WriteMode::run(ModeContext const& ctx) {
  // validate paths
  if (!_core.validatePath(ctx.outputPath, AcceptedFSType::DIRECTORY)
   || !_core.validatePath(ctx.directoryPath, AcceptedFSType::DIRECTORY)) {
    return false;
  }

  DirectoryContent directoryContent = _core.scanDirectory(ctx.directoryPath);
  if (writeRecord(directoryContent, ctx.outputPath)) {
    std::cerr << getErrorMsg();
  }
  return true;
}

bool WriteMode::writeRecord(DirectoryContent const& directoryContent,
			    std::filesystem::path const& outputPath) {
  _errorMessage.clear();
  
  nlohmann::json j = directoryContent;

  // create output JSON file
  std::filesystem::path outputFile = outputPath / "snapshot.json";

  // write to file
  std::ofstream ofs(outputFile, std::ofstream::out);
  if (!ofs.is_open()) {
    setErrorMsg("Failure to open file: " + outputFile.string());
    return false;
  }

  ofs << j.dump(2);

  if (!ofs.good()) {
    setErrorMsg( "Failure to write to file: " + outputFile.string());
    return false;
  }

  setErrorMsg("SUCCESS! Wrote to: " + outputFile.string());
  return true;
}
