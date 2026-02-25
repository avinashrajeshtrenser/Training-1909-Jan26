#pragma once
#include <vector>
#include <memory>
#include "User.h"

class Manager : public User {
public:
    Manager(int userId, const std::string& userName, const std::string& password)
        : User(userId, userName, password) {
    }
    std::string getRole() const override;
};
