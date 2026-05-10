#ifndef WRITEMODE_H
#define WRITEMODE_H

#include "IntegrityCore.h"
#include "DirectoryContent.h"

#include <filesystem>
#include <string>

class WriteMode
{
public:
  explicit WriteMode (IntegrityCore& core) : _core(core){}

  public:
  bool run(std::filesystem::path const& directoryPath,
	   std::filesystem::path const& outputPath); // calls writeRecord
  std::string getErrorMessage() const { return _errorMessage; }
  
  private:
  IntegrityCore& _core;
  std::string _errorMessage;
  
  bool writeRecord(DirectoryContent const& directoryContent,
		   std::filesystem::path const& outputPath); // produce JSON file
};

#endif
