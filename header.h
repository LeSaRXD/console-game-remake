#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>



bool load_enemies(std::string const& dir);
bool load_shop(std::string const& dir);

bool user_input();

void show_shop();