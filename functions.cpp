#include "header.h"
using namespace std;



// enums
enum Location {
	outside,
	mines,
	dungeon,
};
enum ItemType {
	weapon = 0,
	armor = 1,
	amulet = 2,
	potion = 3,
};

// structs
struct Enemy {
	string name;
	unsigned int health;
	unsigned int damage;
	unsigned int defense;
	unsigned int drop_chance_percent;
};
struct EnemyLevel {
	vector<Enemy> enemies;
	Enemy boss;
};
struct ShopItem {
	string name;
	unsigned int price;
	ItemType type;
	int modifier = 0, optional_modifier = 0;
	bool sold = false;
};
struct ShopLevel {
	vector<ShopItem> items;
	unsigned int columns, rows;
	unsigned int required_enemy_level = 0;
	bool all_sold = false;
};

// consts
const string ENEMIES_FILENAME = "enemies.txt", SHOP_FILENAME = "shop.txt";

// variables
vector<EnemyLevel> enemy_levels;
vector<ShopLevel> shop;



// functions
bool load_enemies(string const& dir) {

	const string filename = dir + ENEMIES_FILENAME;
	ifstream file(filename);
	if (!file.is_open()) return false;

	unsigned int level_number = 0;
	EnemyLevel current_level;

	string line;
	while (getline(file, line)) {
		if (line.rfind("//", 0) != string::npos) {
			continue;
		}

		if (line.rfind("#level", 0) != string::npos) {
			if (level_number > 0) {
				enemy_levels.push_back(current_level);
			}
			current_level = EnemyLevel();
			level_number++;
			continue;
		}
		
		bool is_boss = false;
		if (line.rfind("#boss", 0) != string::npos) {
			is_boss = true;
			getline(file, line);
		}
		Enemy enemy;
		enemy.name = line;
		getline(file, line);
		stringstream attributes(line);
		attributes >> enemy.health >> enemy.damage >> enemy.defense >> enemy.drop_chance_percent;
		if (is_boss) {
			current_level.boss = enemy;
		} else {
			current_level.enemies.push_back(enemy);
		}
	}
	enemy_levels.push_back(current_level);

	// cout << "loaded " << enemy_levels.size() << " enemy levels\n" << enemy_levels[0].enemies[0].name << "\n";
	return true;

}

bool load_shop(string const& dir) {

	const string filename = dir + SHOP_FILENAME;
	ifstream file(filename);
	if (!file.is_open()) return false;

	unsigned int level_number = 0;
	ShopLevel current_level;

	string line;
	while (getline(file, line)) {
		if (line.rfind("//", 0) != string::npos) {
			continue;
		}

		if (line.rfind("#level", 0) != string::npos) {
			if (level_number > 0) {
				shop.push_back(current_level);
			}
			current_level = ShopLevel();
			stringstream level_stream(line);
			level_stream >> line >> current_level.columns >> current_level.rows >> current_level.required_enemy_level;
			level_number++;
			continue;
		}

		ShopItem item;
		int item_type;
		item.name = line;
		getline(file, line);
		stringstream attributes(line);
		attributes >> item.price >> item_type >> item.modifier >> item.optional_modifier;
		item.type = static_cast<ItemType>(item_type);
		current_level.items.push_back(item);
	}
	shop.push_back(current_level);

	return true;

}

bool user_input() {
	string input;
	getline(cin, input);

	return false;
}