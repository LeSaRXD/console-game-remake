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

int accessible_shop_level();
void show_shop();
bool buy_item(int shop_level, unsigned int index);
void clear_shop_level(int shop_level);

void show_inventory();