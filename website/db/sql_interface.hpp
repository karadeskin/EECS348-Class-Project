#ifndef __CALC_SQL_INTERFACE_HPP__
#define __CALC_SQL_INTERFACE_HPP__

#include <vector>

#include <memory>
#include <sqlite/sqlite3.h>

#include "../user.hpp"

struct SQLDeleter {
    void operator()(sqlite3 *db) noexcept { sqlite3_close_v2(db); }
    void operator()(sqlite3_stmt *stmt) noexcept { sqlite3_finalize(stmt); }
};

using SQLiteHandle = std::unique_ptr<sqlite3, SQLDeleter>;
using SQLiteStatementHandle = std::unique_ptr<sqlite3_stmt, SQLDeleter>;

struct SQLError {
protected:
    char _buffer[1024];
    int _error_code = 0;
    const char *_error_string = nullptr;
    const char *_extended_error = nullptr;
    SQLError() {}
    SQLError(const SQLiteHandle &db) {
        _error_code = sqlite3_errcode(db.get());
        _error_string = sqlite3_errstr(_error_code);
        _extended_error = sqlite3_errstr(sqlite3_extended_errcode(db.get()));
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

class SQLiteDatabase {
private:
    SQLiteHandle _db {};
    char _stmt_buffer[4096];
public:
    SQLiteDatabase() {}

    void attach_memory() {
        sqlite3 *db;
        int rc = sqlite3_open_v2(":memory:", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_MEMORY, nullptr);

        if (rc != SQLITE_OK || db == nullptr) {
            throw std::runtime_error("Error opening db in memory");
        } else {
            _db = SQLiteHandle(db);
        }
    }

    void attach(const std::string &database_path) {
        sqlite3 *db;
        int rc = sqlite3_open_v2(database_path.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

        // TODO get the sqlite3 error from `rc`
        if (rc != SQLITE_OK || db == nullptr) {
            throw std::runtime_error("Error opening db file");
        } else {
            _db = SQLiteHandle(db);
        }
    }

    void close() noexcept {
        _db.reset();
    }

    SQLiteHandle& handle() {
        return _db;
    }

    SQLiteStatementHandle prepare_sql_statement(const char *statement, ...) {
        if (!_db) {
            throw SQLNotAttachedError();
        }

        va_list argp;
        va_start(argp, statement);

        int rc = 0;
        sqlite3_stmt *compiled_stmt = nullptr;
        int bytes_written = std::vsnprintf(_stmt_buffer, sizeof(_stmt_buffer), statement, argp);

        va_end(argp);

        rc = sqlite3_prepare_v2(_db.get(), _stmt_buffer, bytes_written, &compiled_stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw SQLPrepareError(_db, _stmt_buffer);
        }

        return SQLiteStatementHandle(compiled_stmt);
    }

    void execute_sql_statement(const char *statement, ...) {
        va_list argp;
        va_start(argp, statement);

        auto stmt = prepare_sql_statement(statement, argp);

        va_end(argp);

        int rc = sqlite3_step(stmt.get());
        if (rc != SQLITE_DONE) {
            if (rc == SQLITE_BUSY) {
                throw SQLBusyError(_db, stmt);
            } else if (rc == SQLITE_CONSTRAINT) {
                throw SQLConstraintError(_db, stmt);
            }

            throw SQLGenericError(_db, stmt);
        }
    }

    int select_int(const char *statement, ...) {
        va_list argp;
        va_start(argp, statement);

        auto stmt = prepare_sql_statement(statement, argp);

        va_end(argp);

        int rc;
        int id;
        while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt.get(), 0);
        }

        if (rc != SQLITE_DONE) {
            if (rc == SQLITE_BUSY) {
                throw SQLBusyError(_db, stmt);
            } else if (rc == SQLITE_CONSTRAINT) {
                throw SQLConstraintError(_db, stmt);
            }

            throw SQLGenericError(_db, stmt);
        }

        return id;
    }
};

#endif // __CALC_SQL_INTERFACE_HPP__
