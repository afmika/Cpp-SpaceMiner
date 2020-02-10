#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;

namespace SpriteError {
    enum {INVALID_COL_ROW, INVALID_INDEX};
}

class SpriteManager {
    public:
        sf::Texture texture;
        unsigned int tile_width;
        unsigned int tile_height;
        int curr_sprite_index;

        
        unsigned int n_tiles;
        unsigned int n_cols;
        unsigned int n_rows;
        vector<unsigned int> sequence;
        
        bool is_loaded;

        SpriteManager(string texture_path);
        
        void setDimension(unsigned int _tile_width, unsigned int _tile_height);
        void setSpriteSequence(vector<unsigned int> sequence);

        sf::Sprite getSpriteAt(unsigned int col, unsigned int row) const;
        sf::Sprite getSpriteAt(unsigned int index) const;

        void initSequenceIndex();
        bool nextSprite();
        bool hasNextSprite();
        sf::Sprite currentSprite() const;
        virtual ~SpriteManager();
};

#endif