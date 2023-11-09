#ifndef __CALC_SQL_HISTORY_DAO_HPP__
#define __CALC_SQL_HISTORY_DAO_HPP__

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>

#include <sqlite/sqlite3.h>
#include <nlohmann/json.hpp>

#include "sql_dao.hpp"
#include "history_dao.hpp"

class SQLHistoryDatabaseAccessObject : public HistoryDatabaseAccessObject, public SQLDatabaseAccessObject {
public:
    SQLHistoryDatabaseAccessObject(const nlohmann::json &config)
        : HistoryDatabaseAccessObject(), SQLDatabaseAccessObject(config) {}

    ~SQLHistoryDatabaseAccessObject() noexcept {}
};

#endif // __CALC_SQL_HISTORY_DAO_HPP__
