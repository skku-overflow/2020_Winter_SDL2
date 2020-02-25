#include "Headers/Map.h"
#include "Headers/Game.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <fstream>

extern Manager manager;
using namespace std;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
	scaledSize = ts * ms;
}

Map::~Map() {
	
}

void Map::LoadMap(string path, int sizeX, int sizeY) {
	char c;
	fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x*scaledSize, y*scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			if (c == '1') {
				auto& tool(manager.addEntity());
				tool.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tool.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}


void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}

int Map::getMapScale() {
	return this->mapScale;
}