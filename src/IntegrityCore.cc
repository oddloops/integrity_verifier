#include "../include/IntegrityCore.h"

bool IntegrityCore::validateDirectory(const std::filesystem::path& targetDirectory) const
{
  try {
    std::filesystem::file_status tDirectory = std::filesystem::status(targetDirectory);
    if (!std::filesystem::is_directory(tDirectory)) {
      return false;
    }
    
    return true;
  }
  catch (std::filesystem::filesystem_error const& e) {
    std::cout << "Filesystem error: " << e.what() << std::endl;
    return false;
  }
}

std::map<std::filesystem::path, FileInfo> IntegrityCore::getDirectoryContents(const std::filesystem::path& targetDirectory) const
{
  std::map<std::filesystem::path, FileInfo> directoryPaths;
  if (!this->validateDirectory(targetDirectory)) {
    return directoryPaths;
  }
  return directoryPaths;
}
