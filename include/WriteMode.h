#ifndef WRITEMODE_H
#define WRITEMODE_H

#include "Mode.h"
#include "DirectoryContent.h"
#include "ModeContext.h"

#include <filesystem>
#include <string>

class WriteMode : public Mode
{
public:
  using Mode::Mode;
  bool run(ModeContext const& ctx) override;
  
private:
  bool writeRecord(DirectoryContent const& directoryContent,
		   std::filesystem::path const& outputPath); // produce JSON file
};

#endif
