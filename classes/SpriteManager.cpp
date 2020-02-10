#include "SpriteManager.h"

SpriteManager::SpriteManager(string texture_path) {
    if(this->texture.loadFromFile(texture_path)) {
        this->is_loaded = true;
        this->initSequenceIndex();
    } 
}

void SpriteManager::setDimension(unsigned int _tile_width, unsigned int _tile_height) {
    this->tile_width = _tile_width;
    this->tile_height = _tile_height;
    sf::Vector2u size = this->texture.getSize();
    this->n_cols = size.x / this->tile_width;
    this->n_rows = size.y / this->tile_width;
    this->n_tiles = n_cols * n_rows;
}

sf::Sprite SpriteManager::getSpriteAt(unsigned int col, unsigned int row) const {
    if(col >= this->n_cols || row >= this->n_rows) {
        throw SpriteError::INVALID_COL_ROW;
    }
    sf::Sprite sprite(this->texture);
    sprite.setTextureRect(sf::IntRect(col * this->tile_width, row * this->tile_height, this->tile_width, this->tile_height));
    return sprite;
}

sf::Sprite SpriteManager::getSpriteAt(unsigned int index) const {
    if(index >= this->n_tiles) {
        throw SpriteError::INVALID_INDEX;
    }
    // index = col + row * width
    unsigned int r = index / this->n_rows;
    unsigned int c = index - r * this->n_cols;
    return this->getSpriteAt(c, r);
}

void SpriteManager::initSequenceIndex() {
    this->curr_sprite_index = -1;
}

void SpriteManager::setSpriteSequence(vector<unsigned int> sequence) {
    this->sequence = sequence;
}

bool SpriteManager::hasNextSprite() {
    bool more =  this->curr_sprite_index + 1 < (int) this->sequence.size();
    return more;
}

bool SpriteManager::nextSprite() {
    if( this->hasNextSprite() ) {
        this->curr_sprite_index++;
        return true;    
    }
    return false;
}

sf::Sprite SpriteManager::currentSprite() const {
    return this->getSpriteAt( this->curr_sprite_index );
}

SpriteManager::~SpriteManager() {

}