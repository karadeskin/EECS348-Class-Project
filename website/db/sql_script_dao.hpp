#ifndef __CALC_SQL_SCRIPT_DAO_HPP__
#define __CALC_SQL_SCRIPT_DAO_HPP__

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>

#include <sqlite/sqlite3.h>
#include <nlohmann/json.hpp>

#include "sql_dao.hpp"
#include "script_dao.hpp"

class SQLScriptDatabaseAccessObject : public ScriptDatabaseAccessObject, public SQLDatabaseAccessObject {
public:
    SQLScriptDatabaseAccessObject(const nlohmann::json &config)
        : ScriptDatabaseAccessObject(), SQLDatabaseAccessObject(config) {}

    ~SQLScriptDatabaseAccessObject() noexcept {}
};

#endif // __CALC_SQL_SCRIPT_DAO_HPP__
