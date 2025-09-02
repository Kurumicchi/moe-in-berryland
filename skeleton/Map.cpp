#include "Map.h"
#include "BackgroundTile.h"
#include "Collectible.h"
#include "Door.h"
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

// Size of each tile in pixels
constexpr int TILE_SIZE = 50;
constexpr int SPRITE_SIZE = 16;

// Global vectors
std::vector<Collectible> collectibles;
std::vector<BackgroundTile> backgroundTiles;
std::vector<Door> doors;

std::vector<Platform> generate_platforms_from_map() {
    std::vector<Platform> platforms;
    std::vector<std::vector<int>> tileMap;

    // Load Map.txt
    std::ifstream file("Map.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int tileCode;

        while (ss >> tileCode) {
            row.push_back(tileCode);
        }

        tileMap.push_back(row);
    }

    // Tile info
    struct TileInfo {
        const sf::Texture* texture;
        sf::IntRect textureRect;
        bool solid = false;
        bool harmful = false;
        bool collectible = false;
    };


    // Load Textures
    static sf::Texture tileset;
    if (!tileset.loadFromFile("assets/Dirt-&-Grass-2D-Platform-Tileset_ver.2_by_AxulArt/grass tileset ver.2.png")) {
        std::cout << "Failed to load tileset!" << std::endl;
        return platforms;
    }
    static sf::Texture strawberryTexture;
    if (!strawberryTexture.loadFromFile("assets/Strawberry/strawberry (1).png")) {
        std::cout << "Failed to load strawberry texture!\n";
    }

    std::map<int, TileInfo> tileTypes;
    // Dirt
    tileTypes[1] = { &tileset, sf::IntRect(0, 0, 16, 16), true, false, false };   // Top grass (left)
    tileTypes[2] = { &tileset, sf::IntRect(16, 0, 16, 16), true, false, false };  // Top grass (middle)
    tileTypes[3] = { &tileset, sf::IntRect(32, 0, 16, 16), true, false, false };  // Top grass (right)
    tileTypes[4] = { &tileset, sf::IntRect(0, 16, 16, 16), true, false, false };  // Dirt left
    tileTypes[5] = { &tileset, sf::IntRect(16, 16, 16, 16), true, false, false }; // Dirt mid
    tileTypes[6] = { &tileset, sf::IntRect(32, 16, 16, 16), true, false, false }; // Dirt right
    tileTypes[7] = { &tileset, sf::IntRect(0, 32, 16, 16), true, false, false };  // Grass bottom left
    tileTypes[8] = { &tileset, sf::IntRect(16, 32, 16, 16), true, false, false }; // Grass bottom mid
    tileTypes[9] = { &tileset, sf::IntRect(32, 32, 16, 16), true, false, false }; // Grass bottom right

    // Dirt Pillars
    tileTypes[10] = { &tileset, sf::IntRect(48, 0, 16, 16), true, false, false };   // Dirt pillar (top)
    tileTypes[11] = { &tileset, sf::IntRect(48, 16, 16, 16), true, false, false };  // Dirt pillar (middle)
    tileTypes[12] = { &tileset, sf::IntRect(48, 32, 16, 16), true, false, false };  // Dirt pillar (bottom)

    // Dirt sideaways pillars
    tileTypes[13] = { &tileset, sf::IntRect(0, 48, 16, 16), true, false, false };   // Grass sideaways pillar (left)
    tileTypes[14] = { &tileset, sf::IntRect(16, 48, 16, 16), true, false, false };  // Grass sideaways pillar (middle)
    tileTypes[15] = { &tileset, sf::IntRect(32, 48, 16, 16), true, false, false };  // Grass sideaways pillar (right)

    // Collectibles
    tileTypes[16] = { &tileset, sf::IntRect(80, 112, 16, 16), false, false, true };  // Key
    tileTypes[17] = { &strawberryTexture, sf::IntRect(0, 0, 16, 16), false, false, true }; // Strawberry

    // Non-solid tiles
    tileTypes[18] = { &tileset, sf::IntRect(112, 32, 16, 16), false, false, false};   // Tree (top)
    tileTypes[19] = { &tileset, sf::IntRect(112, 48, 16, 16), false, false, false}; // Tree (middle)
    tileTypes[20] = { &tileset, sf::IntRect(112, 64, 16, 16), false, false, false}; // Tree (bottom)
    tileTypes[21] = { &tileset, sf::IntRect(112, 0, 16, 16), false, false, false}; // Flower (top)
    tileTypes[22] = { &tileset, sf::IntRect(112, 16, 16, 16), false, false, false}; // Flower (bottom)

    // Doors
    tileTypes[23] = { &tileset, sf::IntRect(80, 80, 16, 16), true, false, false }; // Door (top part)
    tileTypes[24] = { &tileset, sf::IntRect(80, 96, 16, 16), true, false, false }; // Door (Bottom part)
    tileTypes[25] = { &tileset, sf::IntRect(64, 112, 16, 16), false, false, false };


    // Convert tileMap to platforms
    for (int row = 0; row < tileMap.size(); ++row) {
        for (int col = 0; col < tileMap[row].size(); ++col) {
            int tileType = tileMap[row][col];
            float x = col * TILE_SIZE;
            float y = row * TILE_SIZE;

            auto it = tileTypes.find(tileType);
            if (it != tileTypes.end()) {
                const TileInfo& info = it->second;

                if (info.solid) {
                    platforms.emplace_back(x, y, TILE_SIZE, TILE_SIZE, info.texture, info.textureRect);
                }    

                if (info.collectible) {
                    std::string type = (tileType == 16) ? "key" : 
                                    (tileType == 17) ? "strawberry" : "unknown";

                    collectibles.emplace_back(x, y, TILE_SIZE, info.texture, info.textureRect, type);
                }

                if (tileType == 23) {
                    doors.emplace_back(x, y, TILE_SIZE, info.texture, info.textureRect);
                }

                else if (!info.solid && !info.collectible) {
                    backgroundTiles.emplace_back(x, y, TILE_SIZE, info.texture, info.textureRect);
                }
            }
        }
    }
    return platforms;
}