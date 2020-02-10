#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Orbusoid.h"
using namespace std;

class Line {
    public:
        int life;
        vector<sf::Vector2f> points;
        sf::Color *color;
        Line();

        bool isClosed() const;
        bool captures(Orbusoid orbus) const;
        void add(sf::Vector2f point);

        void drawLineBetween(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow &window);
        void drawInside(sf::RenderWindow &window);
        virtual ~Line();
};

#endif