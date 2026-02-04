#include <gtest/gtest.h>
#include "../include/RecordMode.h"

class RecordModeTest : public testing::Test
{
protected:
  RecordMode recordTest = RecordMode();
};

TEST_F(RecordModeTest, InvalidDirectoryName) {
  EXPECT_FALSE(recordTest.verifyDirectory("tset"));
}

TEST_F(RecordModeTest, ValidDirectoryName) {
  EXPECT_TRUE(recordTest.verifyDirectory("test/t1"));
}
