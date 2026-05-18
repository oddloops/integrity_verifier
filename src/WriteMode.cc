#include "WriteMode.h"
#include "AcceptedFSType.h"
#include <nlohmann/json.hpp>

#include <fstream>

bool WriteMode::run(std::filesystem::path const& directoryPath,
		    std::filesystem::path const& outputPath) {
  // validate paths
  if (!_core.validatePath(outputPath, AcceptedFSType::DIRECTORY)
   || !_core.validatePath(directoryPath, AcceptedFSType::DIRECTORY)) {
    return false;
  }

  DirectoryContent directoryContent = _core.scanDirectory(directoryPath);
  return writeRecord(directoryContent, outputPath);
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
    _errorMessage = "Failure to open file: " + outputFile.string();
    return false;
  }

  ofs << j.dump(2);

  if (!ofs.good()) {
    _errorMessage = "Failure to write to file: " + outputFile.string();
    return false;
  }

  _errorMessage = "SUCCESS! Wrote to: " + outputFile.string();
  return true;
}
