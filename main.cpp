#include "header.h"

using namespace std;

int main(int argc, char *argv[]) {
	string mod_dir = string(argv[0]);
	mod_dir = mod_dir.substr(0, mod_dir.find_last_of("/"));
	mod_dir.append("/");
	if (!load_enemies(mod_dir)) {
		cout << "Couldn't load enemies file\n";
		return 0;
	}

	bool keep_alive = true;
	while (keep_alive) {
		keep_alive = user_input();
	}
}