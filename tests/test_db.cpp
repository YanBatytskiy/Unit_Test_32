#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IDBConnection.h"
#include "ClassThatUsesDB.h"

class MockDBConnection : public IDBConnection {
public:
  MOCK_METHOD(bool, open, (), (override));
  MOCK_METHOD(bool, close, (), (override));
  MOCK_METHOD(bool, execQuery, (const std::string&), (override));
};

TEST(ClassThatUsesDB_Test, OpenCallsOpen) {
  MockDBConnection mock;
  ClassThatUsesDB u(&mock);
  EXPECT_CALL(mock, open()).Times(1).WillOnce(::testing::Return(true));
  EXPECT_TRUE(u.openConnection());
}

TEST(ClassThatUsesDB_Test, UseCallsExecQuery) {
  MockDBConnection mock;
  ClassThatUsesDB u(&mock);
  EXPECT_CALL(mock, execQuery("SELECT 1")).Times(1).WillOnce(::testing::Return(true));
  EXPECT_TRUE(u.useConnection("SELECT 1"));
}

TEST(ClassThatUsesDB_Test, CloseCallsClose) {
  MockDBConnection mock;
  ClassThatUsesDB u(&mock);
  EXPECT_CALL(mock, close()).Times(1).WillOnce(::testing::Return(true));
  EXPECT_TRUE(u.closeConnection());
}
