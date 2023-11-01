#ifndef __CALC_DAO_H__
#define __CALC_DAO_H__

#include <fstream>
#include <iostream>
#include <memory>
#include <streambuf>
#include <string>
#include <string_view>

#include <sqlite/sqlite3.h>

#include "sql_interface.h"
#include "sql_errors.h"

class DatabaseAccessObject {
public:
    DatabaseAccessObject() {}
    virtual ~DatabaseAccessObject() noexcept {}
};

#endif // __CALC_DAO_H__
