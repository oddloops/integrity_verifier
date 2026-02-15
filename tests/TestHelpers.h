#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <map>
#include "../include/FileInfo.h"

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
}

#endif
