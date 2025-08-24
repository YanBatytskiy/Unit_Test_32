#pragma once
#include <string>

struct IDBConnection {
  virtual ~IDBConnection() = default;
  virtual bool open() = 0;
  virtual bool close() = 0;
  virtual bool execQuery(const std::string& sql) = 0;
};
