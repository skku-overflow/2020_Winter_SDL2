#include "Headers/Map.h"
#include "Headers/Game.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <fstream>
#include <iostream>
#include <random>

extern Manager manager;
using namespace std;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) {
	scaledSize = ts * ms;
}

Map::~Map() {
	
}

void Map::readMapFile(string path, int sizeX, int sizeY) {
	Map::mapW = sizeX;
	Map::mapH = sizeY;
	
	Map::mapTileInfo = new mapTile * [Map::mapH]();
	for (int i = 0; i < Map::mapW; i++)
		Map::mapTileInfo[i] = new mapTile[Map::mapW]();

	Map::terrainTileInfo = new int* [Map::mapH]();
	for (int i = 0; i < Map::mapW; i++)
		Map::terrainTileInfo[i] = new int[Map::mapW]();

	char c;
	fstream mapFile;
	mapFile.open(path);	

	for (int y = 0; y < Map::mapH; y++) {
		for (int x = 0; x < Map::mapW; x++) {
			mapFile.get(c);
			Map::mapTileInfo[y][x].tsY = atoi(&c);
			mapFile.get(c);
			Map::mapTileInfo[y][x].tsX = atoi(&c);

			mapFile.ignore();
		}
	} mapFile.ignore();

	for (int y = 0; y < Map::mapH; y++) {
		for (int x = 0; x < Map::mapW; x++) {
			mapFile.get(c);
			Map::terrainTileInfo[y][x] = atoi(&c);
			mapFile.ignore();
		}
	}mapFile.close();


	for (int y = 0; y < Map::mapH; y++) {
		for (int x = 0; x < Map::mapW; x++) {
			AddTile(Map::mapTileInfo[y][x].tsX, Map::mapTileInfo[y][x].tsY, x, y);
		}
	}

	for (int y = 0; y < Map::mapH; y++) {
		for (int x = 0; x < Map::mapW; x++) {
			if (Map::terrainTileInfo[y][x] == 1) {
				auto& tool(manager.addEntity());
				tool.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tool.addGroup(Game::groupTerrain);
			}
		}
	}

}

void Map::mapRandomize() {
	std::random_device rand;

	manager.getGroup(Game::groupMap).clear();
	//manager.getGroup(Game::groupTerrain).clear();

	for (int i = Map::mapH - 1; i > 0; i--) {
		for (int j = 0; j < Map::mapW; j++) {
			Map::mapTileInfo[i][j] = Map::mapTileInfo[i-1][j];
		}
	}

	for (int i = 0; i < Map::mapW; i++) {
		Map::mapTileInfo[0][i] = { static_cast<int>(rand() % 3), static_cast<int>(rand() % 10) };
	}
}

void Map::LoadMap() {
	for (int y = 0; y < Map::mapH; y++) {
		for (int x = 0; x < Map::mapW; x++) {
			AddTile(Map::mapTileInfo[y][x].tsX, Map::mapTileInfo[y][x].tsY, x, y);
		}
	}
}

void Map::AddTile(int tsX, int tsY, int epX, int epY) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(tsX, tsY, epX, epY, tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}

int Map::getMapScale() {
	return this->mapScale;
}