#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <fstream>
#include <map>
#include "../include/FileInfo.h"

namespace TestHelpers {
  void createFile(std::filesystem::path const& p, std::string_view pContents);
  bool compareFileInfo (FileInfo const& f1, FileInfo const& f2);
  std::ostream& fiOut(std::ostream& os, const FileInfo& fi);
  std::string permsToString(std::filesystem::perms p);
}

#endif
