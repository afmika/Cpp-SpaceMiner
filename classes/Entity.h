#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    public:
        float x, y;
        Entity(float x, float y);
        
        void setX(float x);
        void setY(float y);

        float distSquared(Entity &other) const;
        float dist(Entity &other) const;
        float getX() const;
        float getY() const;

        virtual ~Entity();
};

#endif