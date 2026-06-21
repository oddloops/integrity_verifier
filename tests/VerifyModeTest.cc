#include "IntegrityCore.h"
#include "modes/WriteMode.h"
#include "modes/VerifyMode.h"
#include "models/ModeContext.h"
#include "include/TestHelpers.h"

#include <gtest/gtest.h>

class VerifyModeTestClass : public testing::Test
{
protected:
  IntegrityCore Core;
  VerifyMode Verifier{Core};
  WriteMode Writer{Core};
};

TEST_F(VerifyModeTestClass, VerifyRecord) {
  const std::filesystem::path root =
      std::filesystem::temp_directory_path() / "pathRoot";
  const std::filesystem::path p1 = root / "c1";

  std::filesystem::create_directories(p1);
  TestHelpers::createFile(p1 / "fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1 / "testImage.png", "");

  ModeContext goodCtx{p1, p1, p1 / "snapshot.json"};
  EXPECT_TRUE(Writer.run(goodCtx));
  EXPECT_TRUE(std::filesystem::exists(p1 / "snapshot.json"));

  EXPECT_TRUE(Verifier.run(goodCtx));
  
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

TEST_F(VerifyModeTestClass, VerifyChanges) {
  const std::filesystem::path root =
      std::filesystem::temp_directory_path() / "pathRoot";
  const std::filesystem::path p1 = root / "c1";

  std::filesystem::create_directories(p1);
  TestHelpers::createFile(p1 / "fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1 / "testImage.png", "");

  ModeContext goodCtx{p1, p1, p1 / "snapshot.json"};
  EXPECT_TRUE(Writer.run(goodCtx));
  EXPECT_TRUE(std::filesystem::exists(p1 / "snapshot.json"));
  EXPECT_TRUE(Verifier.run(goodCtx));

  std::filesystem::remove(p1 / "testImage.png");

  EXPECT_FALSE(Verifier.run(goodCtx));
  
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}
