#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/RecordMode.h"
/*
class RecordModeTestClass : public testing::Test
{
protected:
  RecordMode recordTest = RecordMode("/home/mintvoyager/GitHub/projects/integrity_verifier/tests/testing_directories/test");
};
*/
TEST(RecordModeTest, InvalidDirectory) {
  std::filesystem::path testDirectory = "/home/mintvoyager/GitHub/projects/integrity_verifier/tests/testing_directories/tset";

  EXPECT_THROW({
      try
	{
	  RecordMode rm {testDirectory};
	}
      catch (const std::runtime_error& e)
	{
	  std::string expected = "Invalid directory, given: " + testDirectory.string();
	  EXPECT_STREQ(expected.c_str(), e.what());
	  throw;
	}
    }, std::runtime_error);
}

TEST(RecordModeTest, ValidDirectory) {
  std::filesystem::path testDirectory = "/home/mintvoyager/GitHub/projects/integrity_verifier/tests/testing_directories/t1";
  EXPECT_NO_THROW({
      RecordMode rm {testDirectory};
    });
}
