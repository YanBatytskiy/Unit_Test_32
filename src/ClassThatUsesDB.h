#pragma once
#include "IDBConnection.h"
#include <string>

class ClassThatUsesDB {
public:
  explicit ClassThatUsesDB(IDBConnection* conn);
  bool openConnection();
  bool useConnection(const std::string& sql);
  bool closeConnection();

private:
  IDBConnection* conn_;
};
