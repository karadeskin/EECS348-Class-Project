#ifndef __AUTH_SERVICE_HPP__
#define __AUTH_SERVICE_HPP__

#include <iostream>
#include <unordered_map>
#include <string>
#include <random>

class AuthService {
private:
    std::unordered_map<std::string, std::string> userTokens; //store user session tokens
    std::unordered_map<std::string, std::string> userPasswords; 

    std::string generateToken() {
        //function to generate random token 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, INT_MAX);
        return std::to_string(dis(gen));
    }

public:
    AuthService() {} 

    bool createAccount(const std::string& username, const std::string& password) {
        if (userPasswords.find(username) != userPasswords.end()) {
            return false;
        }

        //store the username and password in the map
        userPasswords[username] = password;
        return true; 
    }

    std::string login(const std::string& username, const std::string& password) {
        if (userPasswords.find(username) != userPasswords.end() && userPasswords[username] == password) {
            //generate a session token and store it for the user
            std::string token = generateToken();
            userTokens[username] = token;
            return token;
        }

        return ""; //if login fails
    }

    bool checkSessionToken(const std::string& username, const std::string& token) {
        //checking if the session token matches the one stored for the user
        return (userTokens.find(username) != userTokens.end() && userTokens[username] == token);
    }
};

#endif
