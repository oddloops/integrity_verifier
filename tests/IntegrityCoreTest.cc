#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

TEST_F(IntegrityCoreTestClass, InvalidDirectoryBool) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  const std::filesystem::path p2 = "sandbox/t2";
  EXPECT_FALSE(core.validateDirectory(p2).validateBool);
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, InvalidDirectoryMessage) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  const std::filesystem::path p2 = "sandbox/t2";
  const std::string invalidMessage = "invalid directory path";
  EXPECT_EQ(core.validateDirectory(p2).message, invalidMessage);
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidDirectoryBool) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  EXPECT_TRUE(core.validateDirectory(p).validateBool);
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidDirectoryMessage) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::string validMessage = "valid directory path";
  EXPECT_EQ(core.validateDirectory(p).message, validMessage);
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
  EXPECT_FALSE(core.validateDirectory(p).validateBool);
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add
			      ); 
  std::filesystem::remove_all("sandbox");
}
