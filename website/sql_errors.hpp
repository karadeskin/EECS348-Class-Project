#ifndef __CALC_SQL_ERRORS_HPP__
#define __CALC_SQL_ERRORS_HPP__

#include <cstdio>
#include <memory>
#include <sqlite/sqlite3.h>

#include "sql_interface.hpp"

struct SQLError {
protected:
    char _buffer[1024];
    int _error_code = 0;
    const char *_error_string = nullptr;
    SQLError() {}
    SQLError(const SQLiteHandle &db) {
        _error_code = sqlite3_errcode(db.get());
        _error_string = sqlite3_errstr(_error_code);
    }
public:
    char *what() {
        return _buffer;
    }
};

struct SQLNotAttachedError : public SQLError {
    SQLNotAttachedError() : SQLError() {
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLNotAttachedError: object is not attached to any database");
    }
};

struct SQLBusyError : public SQLError {
    SQLBusyError(const SQLiteHandle &db, const SQLiteStatementHandle &stmt) : SQLError(db) {
        const char *statement = sqlite3_sql(stmt.get());
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLBusyError (%d) on input '%s': %s", _error_code, statement, _error_string);
    }
};

struct SQLGenericError : public SQLError {
    SQLGenericError(const SQLiteHandle &db, const SQLiteStatementHandle &stmt) : SQLError(db) {
        const char *statement = sqlite3_sql(stmt.get());
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLGenericError (%d) on input '%s': %s", _error_code, statement, _error_string);
    }
};

struct SQLPrepareError : public SQLError {
    SQLPrepareError(const SQLiteHandle &db, char *statement) : SQLError(db) {
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLPrepareError (%d) on input '%s': %s", _error_code, statement, _error_string);
    }
};

struct SQLConstraintError : public SQLError {
    SQLConstraintError(const SQLiteHandle &db, const SQLiteStatementHandle &stmt) : SQLError(db) {
        const char *statement = sqlite3_sql(stmt.get());
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLConstraintError (%d) on input '%s': %s", _error_code, statement, _error_string);
    }
};

struct SQLNotFoundError : public SQLError {
    SQLNotFoundError(const SQLiteHandle &db, const SQLiteStatementHandle &stmt) : SQLError(db) {
        const char *statement = sqlite3_sql(stmt.get());
        std::snprintf(_buffer, sizeof(_buffer), "[ERROR] SQLNotFoundError (%d) on input '%s': %s", _error_code, statement, _error_string);
    }
};

#endif // __CALC_SQL_ERRORS_HPP__
