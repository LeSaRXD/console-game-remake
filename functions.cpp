#include "header.h"
using namespace std;



// enums
enum Location {
	outside,
	mines,
	dungeon,
};

// structs
struct Enemy {
	string name;
	unsigned int health;
	unsigned int damage;
	unsigned int defense;
	unsigned int drop_chance_percent;
	bool is_boss;
};
struct ShopItem {
	string name;
	unsigned int price;
	unsigned int max_health;
	unsigned int defence;
	unsigned int damage;
	unsigned int healing;
};
using ShopLevel = vector<ShopItem>;

// consts
const string ENEMIES_FILENAME = "enemies.txt", SHOP_FILENAME = "shop.txt";

// variables
vector<Enemy> enemies;
vector<ShopLevel> shop;

// functions
bool user_input() {
	string input;
	getline(cin, input);

	return false;
}