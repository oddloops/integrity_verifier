#include "IntegrityCore.h"
#include "ValidateMessage.h"
#include "status_out.h"
#include "Statuses.h"
#include "models/AcceptedFSType.h"
#include "models/FileInfo.h"
#include "models/DirectoryContent.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include <openssl/evp.h>

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
  for (auto const& dir_entry : std::filesystem::directory_iterator(dPath, ec)) {
    const auto dirPath = dir_entry.path();
    if (validatePath(dirPath, AcceptedFSType::DIRECTORY)) {
      contents.subdirectories.push_back(scanDirectory(dirPath));
    }
    else if (validatePath(dirPath, AcceptedFSType::FILE)) {
      contents.files.push_back(createFileInfo(dirPath));
    }
  }
  std::sort(contents.subdirectories.begin(), contents.subdirectories.end(),
	    [](auto const& a, auto const& b) {
	      return a.directoryPath.string() < b.directoryPath.string();
	    });
  std::sort(contents.files.begin(), contents.files.end(),
            [](auto const &a, auto const &b) {
              return a.filePath.string() < b.filePath.string();
            });
  return contents;
}

void IntegrityCore::outputDirectoryContent(DirectoryContent const &dc, int _indent) {
  std::string indent(_indent, ' ');

  if (_indent == 0) {
    std::cout << "Root Directory: " << dc.directoryPath.string() << "\n";
  } else {
    std::cout << indent << "Directory: " << dc.directoryPath.string() << "\n";
  }

  // Files
  std::cout << indent << "[Files]\n";
  if (dc.files.size() == 0) {
    std::cout << indent << "NO FILES\n";
  } else {
    std::cout << indent << "Num of files: " << dc.files.size() << '\n';
    for (auto const &fi : dc.files) {
      fiOut(std::cout, fi, _indent);
    }
  }
  std::cout << '\n';

  // Subdirectories
  std::cout << indent << "[Subdirectories]\n";
  if (dc.subdirectories.size() == 0) {
    std::cout << indent << "NO SUBDIRECTORIES\n";
  } else {
    std::cout << indent << "Num of subdirectories: " << dc.subdirectories.size()
              << '\n';
    for (auto &sd : dc.subdirectories) {
      outputDirectoryContent(sd, _indent + 4);
      std::cout << "\n";
    }
  }
}

FileInfo IntegrityCore::createFileInfo(std::filesystem::path const& p)
{
  FileInfo fileDetails;
  setFileInfo(fileDetails, p);
  return fileDetails;
}

std::ostream& IntegrityCore::fiOut(std::ostream& os, const FileInfo& fi, int _indent) {
  std::string indent(_indent, ' ');
  os << indent << "Name: " << fi.fileName << "\n"
     << indent << "Path: " << fi.filePath.string() << "\n"
     << indent << "Extension: " << fi.fileExtension << "\n"
     << indent << "Size: " << fi.fileSize << "\n"
     << indent << "Permissions: " << permsToString(fi.permissions) << "\n"
     << indent << "Hash: " << fi.fileHash << "\n";
  //       << " Last Modified: " << fi.lastModified << "\n"
  //       << " Timestamp: " << fi.recordTimestamp << "\n";
  return os;
}

std::string IntegrityCore::permsToString(std::filesystem::perms p) {
  std::string s;
  s += (p & std::filesystem::perms::owner_read)  != std::filesystem::perms::none ? 'r' : '-';
  s += (p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? 'w' : '-';
  s += (p & std::filesystem::perms::owner_exec)  != std::filesystem::perms::none ? 'x' : '-';
 
  s += (p & std::filesystem::perms::group_read)  != std::filesystem::perms::none ? 'r' : '-';
  s += (p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? 'w' : '-';
  s += (p & std::filesystem::perms::group_exec)  != std::filesystem::perms::none ? 'x' : '-';

  s += (p & std::filesystem::perms::others_read)  != std::filesystem::perms::none ? 'r' : '-';
  s += (p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? 'w' : '-';
  s += (p & std::filesystem::perms::others_exec)  != std::filesystem::perms::none ? 'x' : '-';

  return s;
}
  
void IntegrityCore::setFileInfo(FileInfo& fi, std::filesystem::path const& p) {
  fi.fileName = getFileName(p);
  fi.filePath = p.lexically_normal();
  fi.fileExtension = getFileExtension(p);
  fi.fileSize = getFileSize(p);
  fi.permissions = getPermissions(p);
  fi.fileHash = computeHash(p);
  fi.lastModified = getLastModifiedTime(p);
  fi.recordTimestamp = recordTimestamp();
}

std::string IntegrityCore::computeHash(std::filesystem::path const& filePath) {
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    std::cout << "Error reading file" << std::endl;
    return "";
  }

  EVP_MD_CTX* ctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);

  std::vector<char> buffer(8192);
  while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
    EVP_DigestUpdate(ctx, buffer.data(), file.gcount());
  }

  unsigned char hash[EVP_MAX_MD_SIZE];
  unsigned int length = 0;
  EVP_DigestFinal_ex(ctx, hash, &length);
  EVP_MD_CTX_free(ctx);

  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  
  for (unsigned int i = 0; i < length; ++i) {
    oss << std::setw(2) << static_cast<unsigned int>(hash[i]);
  }
  return oss.str();
}

std::string IntegrityCore::getFileName(std::filesystem::path const& p) {
  return p.stem().string();
}

std::string IntegrityCore::getFileExtension(std::filesystem::path const& p) {
  return p.extension().string();
}

u_int64_t IntegrityCore::getFileSize(std::filesystem::path const& p) {
  return std::filesystem::file_size(p);
}

std::filesystem::perms IntegrityCore::getPermissions(std::filesystem::path const& p) {
  return std::filesystem::status(p).permissions();
}

std::filesystem::file_time_type IntegrityCore::getLastModifiedTime(std::filesystem::path const& p) {
  const auto lTime = std::filesystem::last_write_time(p);
  return lTime;
}

std::chrono::time_point<std::chrono::system_clock> IntegrityCore::recordTimestamp() {
  return std::chrono::system_clock::now();
}
