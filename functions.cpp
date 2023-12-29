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
};
struct EnemyLevel {
	vector<Enemy> enemies;
	Enemy boss;
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
vector<EnemyLevel> enemy_levels;
vector<ShopLevel> shop;



bool load_enemies(string const& dir) {

	const string filename = dir + ENEMIES_FILENAME;
	cout << filename << "\n";
	ifstream file(filename);
	if (!file.is_open()) return false;

	unsigned int level_number = 0;
	EnemyLevel current_level;

	string line;
	while (getline(file, line)) {
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
		file >> enemy.health >> enemy.damage >> enemy.defense >> enemy.drop_chance_percent;
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

// functions
bool user_input() {
	string input;
	getline(cin, input);

	return false;
}