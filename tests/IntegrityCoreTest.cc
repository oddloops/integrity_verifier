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
  EXPECT_FALSE(core.validatePath(p/"fileP1.txt", AcceptedFSType::FILE));
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
  
  EXPECT_TRUE(core.validatePath(p1, AcceptedFSType::DIRECTORY));
  
  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateFile) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  TestHelpers::createFile(p/"fileP1.txt", "Hello c1");
  
  EXPECT_TRUE(core.validatePath(p/"fileP1.txt", AcceptedFSType::FILE));

  std::filesystem::remove_all("sandbox");
}

TEST_F(IntegrityCoreTestClass, ValidateBadFile) {
  const std::filesystem::path p = "sandbox/t1";
  std::filesystem::create_directories(p);
  
  EXPECT_FALSE(core.validatePath("sandbox/t2", AcceptedFSType::FILE));

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

// Directory Scan Tests
TEST_F(IntegrityCoreTestClass, ScanDirectoryContents) {
  const std::filesystem::path root = "sandbox";
  const std::filesystem::path p1 = root/"c1";
  const std::filesystem::path p2 = root/"c2";
  const std::filesystem::path p3 = root/"c3";
  const std::filesystem::path p4 = p3/"t1";
  
  std::filesystem::create_directories(p1);
  std::filesystem::create_directories(p2);
  std::filesystem::create_directories(p3);
  std::filesystem::create_directories(p4);
  
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");

  TestHelpers::createFile(p2/"testImage.png", "");
  TestHelpers::createFile(p2/"testImage.jpg", "");
  TestHelpers::createFile(p2/"testVideo.mp4", "");
  
  TestHelpers::createFile(p3/".bin", "");
  TestHelpers::createFile(p3/"makefile", "");

  TestHelpers::createFile(p4/"test1.zip", "");

  DirectoryContent actualDC = core.scanDirectory(root);

  EXPECT_EQ(root, actualDC.directoryPath);

  std::cout << "|------------ SCAN OUTPUT ------------|" << std::endl;
  int i = 0;
  std::cout << "Root Directory: " << actualDC.directoryPath.string() << std::endl;
  for (auto sub_dir : actualDC.subdirectories) {
    i++;
    std::cout << "Sub (" << i << "): " << sub_dir << "\n";
  }
  i = 0;
  for (auto& fi : actualDC.files) {
    i++;
    std::cout << "File (" << i << ")\n";
    TestHelpers::fiOut(std::cout, fi);
  }
  
  EXPECT_TRUE(true);

  std::filesystem::remove_all("sandbox");
}
