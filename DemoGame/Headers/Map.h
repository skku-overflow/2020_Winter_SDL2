#ifndef MAP
#define MAP
#include "Headers/Game.h"
#include <string>

using namespace std;

class Map {
public:
	Map(const char* mfp, int ms, int ts);
	~Map();	

	void LoadMap(string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	//void DrawMap();

	int getMapScale();

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;

	//SDL_Rect src, dest;

	//SDL_Texture* dirt;
	//SDL_Texture* grass;
	//SDL_Texture* water;
	//
	//int map[20][25];

};


#endif