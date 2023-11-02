#ifndef __CALC_DAO_H__
#define __CALC_DAO_H__

#include <fstream>
#include <iostream>
#include <memory>
#include <streambuf>
#include <string>
#include <string_view>

#include "user.h"

class DatabaseAccessObject {
public:
    DatabaseAccessObject() {}
    virtual ~DatabaseAccessObject() noexcept {}

    // some example functions
    virtual User get_user(int id) = 0;
    virtual User create_user(const std::string &name, const std::string &password) = 0;
    virtual User update_user(int id) = 0;
    virtual void delete_user(int id) = 0;
};

#endif // __CALC_DAO_H__
