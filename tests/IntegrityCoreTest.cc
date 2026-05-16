#include "IntegrityCore.h"
#include "include/TestHelpers.h"

#include <filesystem>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

class IntegrityCoreTestClass : public testing::Test
{
protected:
  IntegrityCore core;
};

TEST_F(IntegrityCoreTestClass, ValidateThrowHandle) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ValidateThrowTest";
  const std::filesystem::path p = root/"t1";
  
  std::filesystem::create_directories(p);
  TestHelpers::createFile(p/"fileP1.txt", "Hello c1");
  
  std::filesystem::permissions(
			       root,
			       std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec,
			       std::filesystem::perm_options::remove
			      );
  
  EXPECT_FALSE(core.validatePath(p/"fileP1.txt", AcceptedFSType::FILE));

  std::error_code ec;
  std::filesystem::permissions(
			       root,
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add,
			       ec
			      ); 
  std::filesystem::remove_all(root, ec);
}

TEST_F(IntegrityCoreTestClass, ValidateDirectory) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ValidateDTest";
  const std::filesystem::path p1 = root/"t1";
  std::filesystem::create_directories(p1);
  
  EXPECT_TRUE(core.validatePath(p1, AcceptedFSType::DIRECTORY));

  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

TEST_F(IntegrityCoreTestClass, ValidateFile) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ValidateFTest";
  const std::filesystem::path p = root/"t1";
  std::filesystem::create_directories(p);
  TestHelpers::createFile(p/"fileP1.txt", "Hello c1");
  
  EXPECT_TRUE(core.validatePath(p/"fileP1.txt", AcceptedFSType::FILE));

  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

TEST_F(IntegrityCoreTestClass, ValidateBadFile) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ValidateBTest";
  const std::filesystem::path p = root/"t1";
  std::filesystem::create_directories(p);
  
  EXPECT_FALSE(core.validatePath(root/"t2", AcceptedFSType::FILE));

  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

TEST_F(IntegrityCoreTestClass, CreateFileInfo) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "CreateFITest";
  const std::filesystem::path p1 = root/"c1";
  std::filesystem::create_directories(p1);
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");
  
  FileInfo actualFileInfo = core.createFileInfo(p1/"fileP1.txt");
  FileInfo expectedFileInfo;
  expectedFileInfo.fileName = "fileP1";
  expectedFileInfo.filePath = p1/"fileP1.txt";
  expectedFileInfo.fileExtension = ".txt";
  EXPECT_TRUE(TestHelpers::compareFileInfo(expectedFileInfo, actualFileInfo));

  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}

// Directory Scan Tests
TEST_F(IntegrityCoreTestClass, ScanDirectoryPermissionsContents) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ScanDCPermTests";
  const std::filesystem::path p1 = root/"c1";
 
  std::filesystem::create_directories(p1);
 
  TestHelpers::createFile(p1/"fileP1.txt", "Hello c1");

  std::filesystem::permissions(
			       p1,
			       std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec | std::filesystem::perms::others_exec,
			       std::filesystem::perm_options::remove
			      );

  DirectoryContent actualDC = core.scanDirectory(root);
  EXPECT_EQ(root, actualDC.directoryPath);

  std::cout << "|------------ SCAN OUTPUT ------------|" << std::endl;
  core.outputDirectoryContent(actualDC);
  
  EXPECT_EQ(actualDC.subdirectories.size(), 1);
  std::error_code ec;
  std::filesystem::permissions(
			       p1,
			       std::filesystem::perms::owner_all,
			       std::filesystem::perm_options::add,
			       ec
			      ); 
  std::filesystem::remove_all(root, ec);
}

TEST_F(IntegrityCoreTestClass, ScanDirectoryContents) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ScanDCTests";
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
  EXPECT_EQ(actualDC.subdirectories.size(), 3);

  std::cout << "|------------ SCAN OUTPUT ------------|" << std::endl;
  core.outputDirectoryContent(actualDC);
  
  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}
 
// Computehash Tests
TEST_F(IntegrityCoreTestClass, FileInfoComparison) {
  const std::filesystem::path root = std::filesystem::temp_directory_path() / "ScanDCPermTests";
  const std::filesystem::path newFile = root/"fileP1.txt";
  std::filesystem::create_directories(root);
 
  TestHelpers::createFile(newFile, "Hello c1");
  FileInfo f1 = core.createFileInfo(newFile);

  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  {
    std::ofstream temp(newFile);
    temp << "New written line";
  }

  FileInfo f2 = core.createFileInfo(newFile);

  EXPECT_EQ(f1.fileName, f2.fileName);
  EXPECT_EQ(f1.filePath, f2.filePath);
  EXPECT_EQ(f1.fileExtension, f2.fileExtension);
  EXPECT_NE(f1.fileSize, f2.fileSize);
  EXPECT_EQ(f1.permissions, f2.permissions);
  EXPECT_NE(f1.fileHash, f2.fileHash);
  EXPECT_NE(f1.lastModified, f2.lastModified);

  std::error_code ec;
  std::filesystem::remove_all(root, ec);
}
