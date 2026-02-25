#pragma once
#include "User.h"

class Staff : public User {
public:
    Staff(int userId, const std::string& userName, const std::string& password)
        : User(userId, userName, password) {
    }

    std::string getRole() const override;
};
