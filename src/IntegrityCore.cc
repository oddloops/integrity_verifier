#include "../include/IntegrityCore.h"
#include <map>

bool IntegrityCore::validateDirectory(std::filesystem::path const& targetDirectory) const
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

std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> IntegrityCore::getDirectoryContents(std::filesystem::path const& targetDirectory) const
{
  std::map<std::filesystem::path, FileInfo> directoryPaths;
  if (!this->validateDirectory(targetDirectory)) {
    return directoryPaths;
  }

  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(targetDirectory)) {
    std::cout << dir_entry << std::endl;
    auto const& fileData = std::filesystem::status(dir_entry);
    if (std::filesystem::is_directory(fileData)) continue;
  }
  return directoryPaths;
}

std::string IntegrityCore::computeHash(std::filesystem::path const& filePath) {
  return ""; // TODO
}

FileInfo IntegrityCore::createFileInfo(std::filesystem::path const& p) const
{
  FileInfo fileDetails;
  setFileInfo(fileDetails);
  return fileDetails;
}

void IntegrityCore::setFileInfo(FileInfo& fi, std::filesystem::path const& p) {
  fi.fileName = getFileName(p);
  fi.filePath = p;
  fi.fileExtension = getFileExtension(p);
  fi.fileSize = getFileSize(p);
  fi.permissions = getPermissions(p);
  fi.lastModified = getLastModifiedTime(p);
  fi.recordTimestamp = setRecordTime(p);
}
