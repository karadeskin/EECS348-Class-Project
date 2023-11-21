#ifndef __AUTH_SERVICE_HPP__
#define __AUTH_SERVICE_HPP__

#include <iostream>
#include <unordered_map>
#include <string>
#include <random>
#include "../db/user_dao.hpp"

class AuthService {
private:
    std::unordered_map<std::string, std::string> userTokens; //store user session tokens
    std::unordered_map<std::string, std::string> userPasswords; 
    std::shared_ptr<UserDatabaseAccessObject> _user_dao {};

    std::string generateToken() {
        //function to generate random token 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, INT_MAX);
        return std::to_string(dis(gen));
    }

public:
    AuthService(std::shared_ptr<UserDatabaseAccessObject> user_dao) : _user_dao(std::move(user_dao)) {}

    bool createAccount(const std::string& username, const std::string& password) {
        if (_user_dao->userExists(username)) {
            return false;
        }

        userPasswords[username] = password;

        _user_dao->createUser(username, password);

        return true;
    }

    std::string login(const std::string& username, const std::string& password) {
        if (userPasswords.find(username) != userPasswords.end() && userPasswords[username] == password) {
            std::string token = generateToken();
            userTokens[username] = token;
            return token;
        }

        return ""; 
    }

    bool checkSessionToken(const std::string& username, const std::string& token) {
        return (userTokens.find(username) != userTokens.end() && userTokens[username] == token);
    }
};

#endif // __AUTH_SERVICE_HPP__
