#ifndef SQLITE_H
#define SQLITE_H

#include <list>
#include <string>
#include <vector>

#include "sqlite3.h"

// This is a note which should move out to documentation
// Table query:  query("SELECT name FROM sqlite_master WHERE type = 'table';");

namespace cpputil
{

template <typename _Row = std::vector<std::string>, typename _Sequence = std::list<_Row> >
class basic_Sqlite
{
  public: 
    typedef           int                      status_type;
    typedef          _Row                      row_type;
    typedef typename _Sequence::const_iterator const_iterator;

    basic_Sqlite() = delete;
    basic_Sqlite(const char* path) { status_ = sqlite3_open(path, &db_); }
    basic_Sqlite& operator=(basic_Sqlite& s) = delete;
    ~basic_Sqlite() { status_ = sqlite3_close(db_); }

    status_type status() const { return status_; }
    bool okay() const { return status_ == SQLITE_OK; }

    void query(const char* query)
    {
      results_.clear();
      status_ = sqlite3_exec(db_, query, callback, &results_, 0);
    }

    const_iterator begin() const { return results_.begin(); }
    const_iterator cbegin() const { return results_.cbegin(); }
    const_iterator end() const { return results_.end(); } 
    const_iterator cend() const { return results_.cend(); } 

  private:
    sqlite3* db_;
    status_type status_;
    _Sequence results_;

    static status_type callback(void* arg, int nCols, char** vals, char** names)
    {
      row_type row;
      row.reserve(nCols);

      for ( int i = 0; i < nCols; ++i )
        row.push_back(vals[i]);

      auto rows = (_Sequence*) arg;
      rows->push_back(row);

      return SQLITE_OK;
    }
};

typedef basic_Sqlite<std::vector<std::string> > Sqlite;

}

#endif
