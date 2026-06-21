#ifndef VERIFYMODE_H
#define VERIFYMODE_H

#include "Mode.h"
#include "WriteMode.h"

class VerifyMode : public Mode
{
public:
  using Mode::Mode;
  bool run(ModeContext const& ctx) override;
  
private:
  bool verifyRecord(std::filesystem::path const& directoryPath,
		    std::filesystem::path const& recordPath);
  bool verifyTraversal(DirectoryContent const& recordContent,
		       DirectoryContent const& currenContent);
  WriteMode _writer;
};

#endif
