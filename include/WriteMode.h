#ifndef WRITEMODE_H
#define WRITEMODE_H

#include "Mode.h"

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
