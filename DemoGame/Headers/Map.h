#ifndef MAP
#define MAP
#include "Headers/Game.h"
#include <string>

using namespace std;

struct mapTile {
	int srcX, srcY;
};

class Map {
public:
	Map(const char* mfp, int ms, int ts);
	~Map();	

	void createMapFile(string path, int sizeX, int sizeY);
	void readMapFile(string path, int sizeX, int sizeY);
	void mapRandomize();

	void LoadMap();
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	//void DrawMap();

	int getMapScale();

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;

	int mapW, mapH;

	mapTile** mapTileInfo;
	int** terrainTileInfo;

	//SDL_Rect src, dest;

	//SDL_Texture* dirt;
	//SDL_Texture* grass;
	//SDL_Texture* water;
	//
	//int map[20][25];

};


#endif