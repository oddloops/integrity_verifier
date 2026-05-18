#ifndef MODE_CONTEXT
#define MODE_CONTEXT

#include <filesystem>

struct ModeContext {
  std::filesystem::path directoryPath;
  std::filesystem::path outputPath;
  std::filesystem::path snapshotPath;
};

#endif
