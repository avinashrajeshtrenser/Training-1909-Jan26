#include "ReadUtility.h"

void readString(std::string& value)
{
    getline(std::cin >> std::ws, value);
}