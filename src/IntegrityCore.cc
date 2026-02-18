#include "../include/IntegrityCore.h"
#include <chrono>
#include <ostream>
#include <algorithm>
#include <sys/types.h>

bool IntegrityCore::validatePath(std::filesystem::path const& p, AcceptedFSType fType) const {
  std::error_code ec;
  std::filesystem::file_status s = std::filesystem::symlink_status(p, ec);

  if (ec) { // handles exception
    std::cout << "Filesystem error: " << ec.message() << std::endl;
    return false;
  }
  if (!std::filesystem::exists(s)) return false;
  if (fType == AcceptedFSType::DIRECTORY && std::filesystem::is_directory(s)) return true;
  if (fType == AcceptedFSType::FILE && std::filesystem::is_regular_file(s)) return true;
  return false;
}

DirectoryContent IntegrityCore::scanDirectory(std::filesystem::path const& dPath) {
  DirectoryContent contents;
  if (!validatePath(dPath, AcceptedFSType::DIRECTORY)) { // validate if given path is a directory
    return contents;
  }
  contents.directoryPath = dPath;
  
  std::error_code ec;
  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(dPath, ec)) {
    const auto dirPath = dir_entry.path();
    if (validatePath(dirPath, AcceptedFSType::DIRECTORY)) {
      std::cout << "Subdirectory: " << dirPath << std::endl;
      contents.subdirectories.push_back(dirPath);
    }
    else if (validatePath(dirPath, AcceptedFSType::FILE)) {
      std::cout << "Dir File: " << dirPath << std::endl;
      contents.files.push_back(createFileInfo(dirPath));
    }
  }
  std::sort(contents.subdirectories.begin(), contents.subdirectories.end());
  std::sort(contents.files.begin(), contents.files.end(),
            [](auto const &a, auto const &b) {
              return a.filePath.string() < b.filePath.string();
            });
  return contents;
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
