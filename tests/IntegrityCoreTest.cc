#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/IntegrityCore.h"
#include "include/TestHelpers.h"

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

TEST_F(IntegrityCoreTestClass, ValidateThrowHandle) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  TestHelpers::createFile(p/"fileP1.txt", "Hello c1");
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec,
			       std::filesystem::perm_options::remove
			      );
  EXPECT_FALSE(core.validatePath(p/"fileP1.txt", AcceptedFile::FILE));
  std::filesystem::permissions(
			       "sandbox",
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add
			      ); 
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateDirectory) {
  const std::filesystem::path p1 = "sandbox/t1";
  std::filesystem::create_directories(p1);
  
  EXPECT_TRUE(core.validatePath(p1, AcceptedFile::DIRECTORY));
  
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateFile) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  TestHelpers::createFile(p/"fileP1.txt", "Hello c1");
  
  EXPECT_TRUE(core.validatePath(p/"fileP1.txt", AcceptedFile::FILE));

  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateBadFile) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  
  EXPECT_FALSE(core.validatePath("sandbox/t2", AcceptedFile::FILE));

  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, CreateFileInfo) {
  const std::filesystem::path root = "sandbox";
  const std::filesystem::path p1 = root/"c1";
  std::filesystem::create_directories(p1);
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  
  FileInfo actualFileInfo = core.createFileInfo(p1/"fileP1.txt");
  FileInfo expectedFileInfo;
  expectedFileInfo.fileName = "fileP1";
  expectedFileInfo.filePath = p1/"fileP1.txt";
  expectedFileInfo.fileExtension = ".txt";
  EXPECT_TRUE(TestHelpers::compareFileInfo(expectedFileInfo, actualFileInfo));

  std::filesystem::remove_all("sandbox");
}
/*
// getDirectoryContents Tests
TEST_F(IntegrityCoreTestClass, getEmptyDirectory) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> actualMap = core.getDirectoryContents(p);
  std::map<std::filesystem::path, std::map<std::filesystem::path, FileInfo>> expectedMap{};

  EXPECT_TRUE(TestHelpers::getDirectoryTestHelper(actualMap, expectedMap));

  std::filesystem::remove_all("sandbox");
}


TEST_F(IntegrityCoreTestClass, getDirectoryContentsOutput) {
  auto createFile = [](const std::filesystem::path& p, std::string_view pContents){
    std::ofstream newFile(p);
    newFile << pContents;
  };
  
  const std::filesystem::path root = "sandbox";
  const std::filesystem::path p1 = root/"c1";
  const std::filesystem::path p2 = root/"c2";
  std::filesystem::create_directories(p1);
  std::filesystem::create_directories(p2);

  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  TestHelpers::createFile(p1/"config.json", "{ \"key\": 1 }");
  TestHelpers::createFile(p1/"image.png", "png");
  TestHelpers::createFile(p1/"fileP2.txt", "Hello c2");
  TestHelpers::createFile(p2/"script.py", "print('Hello World!')");
  TestHelpers::createFile(p2/"archive.zip", "dummy zip");

  EXPECT_TRUE(true); //TODO

  std::filesystem::remove_all("sandbox");
}
*/
