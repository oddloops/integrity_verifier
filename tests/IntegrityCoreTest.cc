#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"
#include "TestHelpers.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

// validateDirectory Tests
TEST_F(IntegrityCoreTestClass, InvalidDirectoryBool) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  const std::filesystem::path p2 = "sandbox/t2";
  EXPECT_FALSE(core.validateDirectory(p2));
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidDirectoryBool) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  EXPECT_TRUE(core.validateDirectory(p));
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateThrow) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec,
			       std::filesystem::perm_options::remove
			      );
  EXPECT_FALSE(core.validateDirectory(p));
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add
			      ); 
  std::filesystem::remove_all("sandbox");
}	       

// getDirectoryContents Tests
TEST_F(IntegrityCoreTestClass, getEmptyDirectory) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::map<std::filesystem::path, FileInfo> actualMap = core.getDirectoryContents(p);
  std::map<std::filesystem::path, FileInfo> expectedMap{};
  EXPECT_TRUE(TestHelpers::getDirectoryTestHelper(actualMap, expectedMap));
  std::filesystem::remove_all("sandbox");
}

