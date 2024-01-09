#include "header.h"
using namespace std;



// enums
enum Location {
	outside,
	mines,
	shop,
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
struct DungeonLevel {
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
	unsigned int required_dungeon_level = 0;
};

// consts
const string ENEMIES_FILENAME = "enemies.txt", SHOP_FILENAME = "shop.txt";

// variables
unsigned long current_money = 0, money_modifier = 1;
unsigned int current_shop_level = 0, current_dungeon_level = 0;
Location current_location = outside;
vector<DungeonLevel> dungeon_levels;
vector<ShopLevel> shop_levels;



// functions
bool load_enemies(string const& dir) {

	const string filename = dir + ENEMIES_FILENAME;
	ifstream file(filename);
	if (!file.is_open()) return false;

	unsigned int level_number = 0;
	DungeonLevel current_level;

	string line;
	while (getline(file, line)) {
		if (line.rfind("//", 0) != string::npos) {
			continue;
		}

		if (line.rfind("#level", 0) != string::npos) {
			if (level_number > 0) {
				dungeon_levels.push_back(current_level);
			}
			current_level = DungeonLevel();
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
	dungeon_levels.push_back(current_level);

	// cout << "loaded " << dungeon_levels.size() << " enemy levels\n" << dungeon_levels[0].enemies[0].name << "\n";
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
				shop_levels.push_back(current_level);
			}
			current_level = ShopLevel();
			stringstream level_stream(line);
			level_stream >> line >> current_level.columns >> current_level.rows >> current_level.required_dungeon_level;
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
	shop_levels.push_back(current_level);

	return true;

}



bool user_input() {
	
	string input;
	getline(cin, input);

	if (input == "exit") {
		cout << "bai\n";
		return false;
	}
	if (input == " ") {
		if (current_location != mines) {
			cout << "Enter the mines to earn money\n";
			return true;
		}
		current_money += money_modifier;
		cout << "You have " << current_money << " money\n";
		return true;
	}
	if (input == "mines") {
		current_location = mines;
		return true;
	}
	if (input == "shop") {
		current_location = shop;
		show_shop();
		return true;
	}
	if (input == "dungeon") {
		// TODO: make dungeon work
		current_location = dungeon;
		return true;
	}

	return true;

}



void show_shop() {
	
	int display_shop_level = current_shop_level;
	if (display_shop_level >= shop_levels.size()) display_shop_level = shop_levels.size() - 1;
	while (display_shop_level >= 0 && shop_levels.at(display_shop_level).required_dungeon_level > current_dungeon_level) display_shop_level--;
	if (display_shop_level < 0) {
		cout << "There is nothing to buy :(\n";
		return;
	}
	ShopLevel level = shop_levels.at(display_shop_level);
	for (int row = 0; row < level.rows; row++) {
		for (int col = 0; col < level.columns; col++) {
			int index = row * level.columns + col;
			if (index >= level.items.size()) break;

			ShopItem item = level.items.at(index);
			string item_str = "- SOLD -";
			if (!item.sold) item_str = item.name + " (" + to_string(item.price) + ")";
			cout << setw(20) << item_str;
		}
		cout << "\n";
	}

}