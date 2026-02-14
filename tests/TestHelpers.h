#ifndef TESTHELPERS_H
#define TESTHELPERS_H

#include <map>
#include "../include/FileInfo.h"

namespace TestHelpers {
  bool getDirectoryTestHelper(
			      const std::map<std::filesystem::path, FileInfo>& m1,
			      const std::map<std::filesystem::path, FileInfo>& m2
			      ) {
    if (m1.size() != m2.size()) {
      return false;
    }
    
    for (const auto& [path, m1Info] : m1) {
      auto m2Path = m2.find(path);
      if (m2Path == m2.end()) return false;
      
      const FileInfo m2Info = m2Path->second;
      if (m1Info.fileName != m2Info.fileName) return false;
      if (m1Info.filePath != m2Info.filePath) return false;
      if (m1Info.fileExtension != m2Info.fileExtension) return false;
      if (m1Info.fileHash != m2Info.fileHash) return false;
    }
    return true;
  }
}

#endif
