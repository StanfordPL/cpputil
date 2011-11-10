#ifndef SQLITE_H
#define SQLITE_H

#include <list>
#include <string>
#include <vector>

#include "sqlite3.h"

class Sqlite
{
  public: 
    typedef std::vector<std::string> Row;

    Sqlite(const char* path);
    ~Sqlite();

    int status() const;
    bool okay() const;

    void query(const std::string& s);
    void tableQuery();

    unsigned int resultSize() const;

    typedef std::list<Row>::const_iterator const_result_iterator;
    const_result_iterator begin() const;
    const_result_iterator end() const; 

  private:
    sqlite3* db_;
    int status_;
    std::list<Row> rows_;
};

inline Sqlite::Sqlite(const char* path)
{
  status_ = sqlite3_open(path, &db_); 
}

inline Sqlite::~Sqlite()
{
  status_ = sqlite3_close(db_);
}

inline int Sqlite::status() const
{
  return status_;
}

inline bool Sqlite::okay() const
{
  return status_ == SQLITE_OK;
}

static inline int callback(void* arg, int nCols, char** vals, char** names)
{
  Sqlite::Row row(nCols);
  for ( int i = 0; i < nCols; ++i )
    row[i] = vals[i];

  auto rows = (std::list<Sqlite::Row>*) arg;
  rows->push_back(row);

  return SQLITE_OK;
}

inline void Sqlite::query(const std::string& s)
{
  rows_.clear();
  status_ = sqlite3_exec(db_, s.c_str(), callback, &rows_, 0);
}

inline void Sqlite::tableQuery()
{
  query("SELECT name FROM sqlite_master WHERE type = 'table';");
}

inline unsigned int Sqlite::resultSize() const
{
  return rows_.size();
}

inline Sqlite::const_result_iterator Sqlite::begin() const
{
  return rows_.begin();
}

inline Sqlite::const_result_iterator Sqlite::end() const
{
  return rows_.end();
}

#endif
