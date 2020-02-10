#include <cmath>
#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity(float x, float y) {
    this->setX(x);
    this->setY(y);
}

void Entity::setX(float x) {
    this->x = x;
}
void Entity::setY(float y) {
    this->y = y;
}
float Entity::distSquared(Entity &other) const {
    return pow(this->getX() - other.getX(), 2) + pow(this->getX() - other.getX(), 2);
}
float Entity::dist(Entity &other) const {
    return sqrt( this->distSquared(other) );
}
float Entity::getX() const {
    return this->x;
}
float Entity::getY() const {
    return this->y;
}

Entity::~Entity() {
    // destructor
}