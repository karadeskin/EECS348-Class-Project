#ifndef __CALC_SQL_INTERFACE_HPP__
#define __CALC_SQL_INTERFACE_HPP__

#include <memory>
#include <sqlite/sqlite3.h>

struct SQLDeleter {
    void operator()(sqlite3 *db) noexcept { sqlite3_close_v2(db); }
    void operator()(sqlite3_stmt *stmt) noexcept { sqlite3_finalize(stmt); }
};

using SQLiteHandle = std::unique_ptr<sqlite3, SQLDeleter>;
using SQLiteStatementHandle = std::unique_ptr<sqlite3_stmt, SQLDeleter>;

#endif // __CALC_SQL_INTERFACE_HPP__
