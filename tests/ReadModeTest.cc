#include "IntegrityCore.h"
#include "modes/WriteMode.h"
#include "modes/ReadMode.h"
#include "models/ModeContext.h"
#include "include/TestHelpers.h"

#include <gtest/gtest.h>

class ReadModeTestClass : public testing::Test
{
protected:
  IntegrityCore Core;
  WriteMode Writer{Core};
  ReadMode Reader{Core};
};

TEST_F(ReadModeTestClass, ReadNoManifest) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "pathRoot";
  const std::filesystem::path p1 = root/"c1";
 
  std::filesystem::create_directories(p1);  
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1/"testImage.png", "");
  
  ModeContext badCtxDirectory{p1, p1, ""};
  ModeContext ctx{p1, p1, p1/"snapshot.json"};
    
  // Bad output location test
  EXPECT_FALSE(Reader.run(badCtxDirectory));
  EXPECT_FALSE(Reader.run(ctx));

  EXPECT_TRUE(Writer.run(ctx));
  EXPECT_TRUE(Reader.run(ctx));
	      
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

