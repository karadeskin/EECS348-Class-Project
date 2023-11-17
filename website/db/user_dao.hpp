#ifndef __CALC_USER_DAO_HPP__
#define __CALC_USER_DAO_HPP__

#include <memory>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "../user.hpp"

class UserDatabaseAccessObject {
protected:
    UserDatabaseAccessObject() {}
    virtual ~UserDatabaseAccessObject() noexcept {}
public:
    virtual std::optional<User> get_user(int id) noexcept = 0;
    virtual std::optional<int> create_user(const std::string &name, const std::string &password) noexcept = 0;
    virtual std::optional<User> update_user(int id) noexcept = 0;
    virtual bool delete_user(int id) noexcept = 0;
};

#endif // __CALC_USER_DAO_HPP__
