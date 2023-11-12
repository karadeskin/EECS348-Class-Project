#ifndef __CALC_EXAMPLE_SERVICE_HPP__
#define __CALC_EXAMPLE_SERVICE_HPP__

#include <iostream>
#include <memory>
#include <optional>

#include "../db/user_dao.hpp"

class ExampleService {
private:
    std::shared_ptr<UserDatabaseAccessObject> _user_dao {};
public:
    ExampleService(std::shared_ptr<UserDatabaseAccessObject> user_dao) : _user_dao(std::move(user_dao)) {}

    // given an id, query the user dao for the user with that id
    std::optional<std::string> query_username(int id) noexcept {
        auto user = _user_dao->get_user(id);

        if (user) {
            return user.value()._username;
        }

        return std::nullopt;
    }
};

#endif // __CALC_EXAMPLE_SERVICE_HPP__
