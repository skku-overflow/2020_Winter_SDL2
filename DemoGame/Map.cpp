#include "Headers/Map.h"
#include "Headers/TextureManager.h"
#include <fstream>

using namespace std;

Map::Map() {

}

Map::~Map() {
	
}

void Map::LoadMap(string path, int sizeX, int sizeY) {
	char tile;
	fstream mapfile;
	mapfile.open(path);

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapfile.get(tile);
			Game::AddTile(atoi(&tile),x*32, y*32);
			mapfile.ignore();
		}
	}

	mapfile.close();
}
