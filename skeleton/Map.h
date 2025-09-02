#pragma once
#include <vector>
#include "Platform.h"
#include "Collectible.h"
#include "BackgroundTile.h"
#include "Door.h"

std::vector<Platform> generate_platforms_from_map();
extern std::vector<Collectible> collectibles;
extern std::vector<BackgroundTile> backgroundTiles;
extern std::vector<Door> doors;