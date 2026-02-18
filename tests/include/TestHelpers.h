#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <fstream>
#include <map>
#include <ostream>
#include <iostream>

#include "../../include/FileInfo.h"
#include "../../include/DirectoryContent.h"

namespace TestHelpers {
  void createFile(std::filesystem::path const& p, std::string_view pContents);
  bool compareFileInfo(FileInfo const& f1, FileInfo const& f2);
  void contentsOut(DirectoryContent const& dc);
  std::ostream& fiOut(std::ostream& os, FileInfo const& fi);
  std::string permsToString(std::filesystem::perms p);
}

#endif
