#include "mathLib2D.h"

#ifndef PARTICLE_H
#define PARDICLE_H

class Colour
{
    public:
        float r;
        float g;
        float b;

        Colour();
        Colour(float r, float g, float b);
};

class Particle
{   
    public:
        Point2D position;
        Colour colour;
        int size;
        Vec2D direction;
        int range;
        float speed;
        Vec2D velocity;
        Point2D target;
        bool hasTarget;

        Particle(int posX, int posY);

        void moveTo(Point2D point);
        void moveAway(Point2D point);
        void momentum();
        void slowDown();

        void bounceX();
        void bounceY();

        void incrementRange();
        void decrementRange();

        void incrementSpeed();
        void decrementSpeed();

        void setTarget(Point2D point);

        void evacuate();
};

#endif