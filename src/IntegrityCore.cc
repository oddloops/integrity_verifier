#include "../include/IntegrityCore.h"
#include <chrono>
#include <map>
#include <sys/types.h>

bool IntegrityCore::validatePath(std::filesystem::path const& p, AcceptedFile fType) const {
  std::error_code ec;
  std::filesystem::file_status s = std::filesystem::symlink_status(p, ec);

  if (ec) {
    std::cout << "Filesystem error: " << ec.message() << std::endl;
    return false;
  }
  if (!std::filesystem::exists(s)) return false;
  if (fType == AcceptedFile::DIRECTORY && std::filesystem::is_directory(s)) return true;
  if (fType == AcceptedFile::FILE && std::filesystem::is_regular_file(s)) return true;
  return false;
}

std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> IntegrityCore::getDirectoryContents(std::filesystem::path const& targetDirectory) const
{
  std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> directoryPaths;
  if (!this->validatePath(targetDirectory, AcceptedFile::DIRECTORY)) {
    return directoryPaths;
  }

  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(targetDirectory)) {
    std::cout << dir_entry << std::endl;
    auto const& fileData = std::filesystem::status(dir_entry);
    if (std::filesystem::is_directory(fileData)) continue;
  }
  return directoryPaths;
}

std::string IntegrityCore::computeHash(std::filesystem::path const& filePath) const {
  return ""; // TODO
}

FileInfo IntegrityCore::createFileInfo(std::filesystem::path const& p)
{
  FileInfo fileDetails;
  setFileInfo(fileDetails, p);
  return fileDetails;
}

void IntegrityCore::setFileInfo(FileInfo& fi, std::filesystem::path const& p) {
  fi.fileName = getFileName(p);
  fi.filePath = p.lexically_normal();
  fi.fileExtension = getFileExtension(p);
  fi.fileSize = getFileSize(p);
  fi.permissions = getPermissions(p);
  fi.lastModified = getLastModifiedTime(p);
  fi.recordTimestamp = recordTimestamp();
}

std::string IntegrityCore::getFileName(std::filesystem::path const& p) const {
  return p.stem().string();
}

std::string IntegrityCore::getFileExtension(std::filesystem::path const& p) const {
  return p.extension().string();
}

u_int64_t IntegrityCore::getFileSize(std::filesystem::path const& p) const {
  return std::filesystem::file_size(p);
}

std::filesystem::perms IntegrityCore::getPermissions(std::filesystem::path const& p) const {
  return std::filesystem::status(p).permissions();
}

std::filesystem::file_time_type IntegrityCore::getLastModifiedTime(std::filesystem::path const& p) const {
  const auto lTime = std::filesystem::last_write_time(p);
  return lTime;
}

std::chrono::time_point<std::chrono::system_clock> IntegrityCore::recordTimestamp() const {
  return std::chrono::system_clock::now();
}
