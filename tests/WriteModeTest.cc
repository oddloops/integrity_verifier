#include "IntegrityCore.h"
#include "WriteMode.h"
#include "include/TestHelpers.h"

#include <gtest/gtest.h>

class WriteModeTestClass : public testing::Test
{
protected:
  IntegrityCore Core;
  WriteMode Writer{Core};
};

TEST_F(WriteModeTestClass, ValidateWriteModePaths) {
    const std::filesystem::path inputDir  = std::filesystem::temp_directory_path() / "ValidateInput";
    const std::filesystem::path outputDir = std::filesystem::temp_directory_path() / "ValidateOutput";

    std::filesystem::create_directory(inputDir);
    std::filesystem::create_directory(outputDir);

    EXPECT_TRUE(Writer.run(inputDir, outputDir));

    std::error_code ec;
    std::filesystem::remove_all(inputDir, ec);

    EXPECT_FALSE(Writer.run(inputDir, outputDir));
    
    std::filesystem::remove_all(outputDir, ec);

    EXPECT_FALSE(Writer.run(inputDir, outputDir));
}

TEST_F(WriteModeTestClass, WriteRecordTest) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "pathRoot";
  const std::filesystem::path p1 = root/"c1";
 
  std::filesystem::create_directories(p1);  
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1/"testImage.png", "");

  const std::filesystem::path badPath = "bad";
  // Bad output location test
  EXPECT_FALSE(Writer.run(p1, badPath));
  EXPECT_TRUE(Writer.run(p1, p1));
  EXPECT_TRUE(std::filesystem::exists(p1/"snapshot.json"));
	      
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

