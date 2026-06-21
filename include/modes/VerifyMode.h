#ifndef VERIFYMODE_H
#define VERIFYMODE_H

#include "Mode.h"
#include "WriteMode.h"

class VerifyMode : public Mode
{
public:
  explicit VerifyMode(IntegrityCore& core)
        : Mode(core), _writer(core) {}
  bool run(ModeContext const& ctx) override;
  
private:
  bool verifyRecord(std::filesystem::path const& directoryPath,
		    std::filesystem::path const& recordPath);
  bool verifyTraversal(DirectoryContent const& recordContent,
		       DirectoryContent const& currentContent);
  WriteMode _writer;
};

#endif
