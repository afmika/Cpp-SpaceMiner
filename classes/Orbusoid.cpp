#include <cmath>
#include "Orbusoid.h"
#include <iostream>

using namespace std;

Orbusoid::Orbusoid(double x, double y) : Entity(x, y) {
    this->life = 100;
    this->is_killed = false;

    // explosion sprite
    this->autoexplosion_sprite = new SpriteManager("images/tiles/explosion1.png");
    this->explosion_sprite = new SpriteManager("images/tiles/explosion2.png");
    this->autoexplosion_sprite->setDimension(512 / 4, 512 / 4);
    this->explosion_sprite->setDimension(512 / 4, 512 / 4);

    vector<unsigned int> frames;
    for(unsigned int i = 0; i < 16; i++) {
        frames.push_back(i);
    }

    this->autoexplosion_sprite->setSpriteSequence(frames);
    this->explosion_sprite->setSpriteSequence(frames);

    this->main_sprite = new SpriteManager("images/tiles/orbe.png");
    this->main_sprite->setDimension(60, 60);
}

bool Orbusoid::endedExploding() const {
    return  ! (this->explosion_sprite->hasNextSprite() && this->autoexplosion_sprite->hasNextSprite() );
}

void Orbusoid::destroy() {
    this->life = 0;
}

void Orbusoid::setKilled(bool is_killed) {
    this->is_killed = this->is_killed || is_killed;
}

void Orbusoid::explode(sf::RenderWindow &window) {
    this->is_exploding = true;
    SpriteManager *explosion_sp = this->is_killed ? this->explosion_sprite : this->autoexplosion_sprite;
    if( explosion_sp->nextSprite() ) {
        sf::Sprite sprite = explosion_sp->currentSprite();
        sprite.setOrigin(explosion_sp->tile_width / 2, explosion_sp->tile_height / 2);
        sprite.setPosition(this->x, this->y);
        window.draw(sprite);
    }
}

void Orbusoid::drawInside(sf::RenderWindow &window) {
    if(life > 0) {
        sf::Sprite sprite = this->main_sprite->getSpriteAt(0);
        sprite.setOrigin(this->main_sprite->tile_width / 2, this->main_sprite->tile_height / 2);
        sprite.setPosition(this->getX(), this->getY());
        window.draw(sprite);
    } else {
        this->explode(window);
    }
}

Orbusoid::~Orbusoid() {
    // destructor
}