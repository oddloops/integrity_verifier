#ifndef READMODE_H
#define READMODE_H

#include "Mode.h"

class ReadMode : public Mode
{
 public:
  using Mode::Mode;
  bool run(ModeContext const& ctx);
};

#endif
