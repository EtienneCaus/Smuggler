#pragma once
#include <map>
#include <iostream>

std::map<std::string, std::string> colour
{
    {"clears", "\033[2J\033[1;1H"}, // clears screen
    {"blue", "\033[1;34m"},
    {"red", "\033[1;31m"},
    {"yellow", "\033[1;33m"},
    {"white", "\033[0m"}
};