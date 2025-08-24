#pragma once
#include "IDBConnection.h"
#include <cstddef>
#include <string>

class DBConnection final : public IDBConnection {
public:
  DBConnection();
  ~DBConnection() override = default;

  bool open() override;
  bool close() override;
  bool execQuery(const std::string& sql) override;

private:
  void init();
  std::size_t socket_descriptor{0};
  bool is_open{false};
};
