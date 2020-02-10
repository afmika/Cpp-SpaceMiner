#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include <Vector>

#include "Entity.h"
#include "SpriteManager.h"

class Orbusoid : public Entity {
    public:
        SpriteManager *explosion_sprite;
        SpriteManager *autoexplosion_sprite;
        SpriteManager *main_sprite;
        double life;
        bool is_killed;
        bool is_exploding;
        Orbusoid(double x, double y);

        bool endedExploding() const;
        void destroy();
        void setKilled(bool is_killed);
        void drawInside(sf::RenderWindow &window);
        void explode(sf::RenderWindow &window);
        virtual ~Orbusoid();
};

#endif