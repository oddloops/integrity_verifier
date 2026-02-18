#include "include/TestHelpers.h"
#include <system_error>

namespace TestHelpers {
  void createFile(std::filesystem::path const& p, std::string_view pContents) {
    std::ofstream newFile(p);
    newFile << pContents;
  }

  bool compareFileInfo (FileInfo const& f1, FileInfo const& f2) {
    if (f1.fileName != f2.fileName) return false;
    if (f1.filePath != f2.filePath) return false;
    if (f1.fileExtension != f2.fileExtension) return false;
    return true;
  }

  void contentsOut(DirectoryContent const& dc) {
    int i = 0;
    std::cout << "Root Directory: " << dc.directoryPath.string() << std::endl;
    std::cout << "Subdirectories" << std::endl;
    for (auto& sd : dc.subdirectories) {
      std::cout << "(" << ++i << ") " << sd.string() << "\n";
    }
    i = 0;
    std::cout << "Files" << std::endl;
    for (auto& fi : dc.files) {
      std::cout << "File (" << ++i << ")\n";
      TestHelpers::fiOut(std::cout, fi);
    }
  }
  
  std::ostream& fiOut(std::ostream& os, const FileInfo& fi) {
    os << " Name: " << fi.fileName << "\n"
       << " Path: " << fi.filePath.string() << "\n"
       << " Extension: " << fi.fileExtension << "\n"
       << " Size: " << fi.fileSize << "\n"
       << " Permissions: " << permsToString(fi.permissions) << "\n"
       << " Hash: " << fi.fileHash << "\n";
      //       << " Last Modified: " << fi.lastModified << "\n"
      //       << " Timestamp: " << fi.recordTimestamp << "\n";
    return os;
  }

  std::string permsToString(std::filesystem::perms p) {
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
}
