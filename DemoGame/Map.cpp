#include "Headers/Map.h"
#include "Headers/TextureManager.h"
#include <fstream>

using namespace std;

Map::Map() {

}

Map::~Map() {
	
}

void Map::LoadMap(string path, int sizeX, int sizeY) {
	char c;
	fstream mapfile;
	mapfile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapfile.get(c);
			srcY = atoi(&c) * 32;
			mapfile.get(c);
			srcX = atoi(&c) * 32;
			Game::AddTile(srcX, srcY, x*64, y*64);
			mapfile.ignore();
		}
	}

	mapfile.close();
}
