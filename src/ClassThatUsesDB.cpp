#include "ClassThatUsesDB.h"

ClassThatUsesDB::ClassThatUsesDB(IDBConnection* conn) : conn_(conn) {}

bool ClassThatUsesDB::openConnection() {
  return conn_ ? conn_->open() : false;
}

bool ClassThatUsesDB::useConnection(const std::string& sql) {
  return conn_ ? conn_->execQuery(sql) : false;
}

bool ClassThatUsesDB::closeConnection() {
  return conn_ ? conn_->close() : false;
}
