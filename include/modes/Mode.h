#ifndef MODE_CLASS
#define MODE_CLASS

#include "IntegrityCore.h"
#include "models/DirectoryContent.h"
#include "models/ModeContext.h"

#include <filesystem>
#include <string>

class Mode
{
public:
  explicit Mode (IntegrityCore& core) : _core(core){}
  virtual ~Mode() = default;

  virtual bool run(ModeContext const& ctx)=0;

  std::string const& getErrorMsg() const {
    return _errorMessage;
  }

protected:
  IntegrityCore _core;
  std::string _errorMessage;

  void setErrorMsg(std::string msg) {
    _errorMessage = msg;
  }
};

#endif
