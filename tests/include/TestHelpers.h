#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <filesystem>
#include <string_view>

#include "models/FileInfo.h"
#include "models/DirectoryContent.h"

namespace TestHelpers {
  void createFile(std::filesystem::path const& p, std::string_view pContents);
  bool compareFileInfo(FileInfo const& f1, FileInfo const& f2);
}

#endif
