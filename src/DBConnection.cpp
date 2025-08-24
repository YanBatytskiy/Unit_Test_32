#include "DBConnection.h"

DBConnection::DBConnection() : socket_descriptor(0), is_open(false) {}

void DBConnection::init() { socket_descriptor = 110; }

bool DBConnection::open() {
  if (!is_open) {
    if (socket_descriptor == 0) init();
    is_open = true;
  }
  return true;
}

bool DBConnection::close() {
  if (is_open) is_open = false;
  return true;
}

bool DBConnection::execQuery(const std::string& /*sql*/) {
  if (!is_open) {
    if (!open()) return false;
  }
  return true;
}
