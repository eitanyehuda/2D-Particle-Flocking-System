#include "particle.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>

const int MAXRANGE = 400;
const int MINRANGE = 20;
const int MAXSPEED = 20;
const int MINSPEED = 1;

// Colour
Colour::Colour()
{   
    this->r = (rand() % 101)*0.01 + 0.1; // +0.1 is just to make the colours generally brighter
    this->g = (rand() % 101)*0.01 + 0.1; 
    this->b = (rand() % 101)*0.01 + 0.1;
}

Colour::Colour(float r, float g, float b) 
{
    this->r = r;
    this->g = g;
    this->b = b;
}

// Particle
Particle::Particle(int posX, int posY)
{
    this->position = Point2D(posX, posY);

    this->colour = Colour(); // instantiate random colour

    this->size = (rand() % 5 + 1)*2; // *2 scale

    this->direction = Vec2D(0,0); 

    this->range = rand() % 100 + 50; // numbers between 50 and 150
    this->speed = rand() % 9 + 1; // numbers between 1 and 10

    this->velocity = Vec2D(0,0);

    this->hasTarget = false;
}

void Particle::moveTo(Point2D point)
{
    this->direction = Vec2D::createVector(this->position, point).Vec2D::normalize();  // unit vector representing direction towards mouse
    this->velocity = this->direction.Vec2D::multiply(this->speed);
    this->momentum();
}

void Particle::moveAway(Point2D point)
{
    this->direction = Vec2D::createVector(this->position, point).Vec2D::normalize();  // unit vector representing direction towards from mouse
    this->velocity = this->direction.Vec2D::multiply(-(this->speed));
    this->momentum();
}

void Particle::momentum()
{
    this->position = this->velocity.movePoint(this->position);
}

void Particle::slowDown()
{
    this->velocity = this->velocity.Vec2D::multiply(0.98);
}

void Particle::bounceX()
{
    float x = this->velocity.mX;
    this->velocity = Vec2D(0, this->velocity.mY);
    this->velocity = Vec2D(-x,this->velocity.mY);
}

void Particle::bounceY()
{
    float y = this->velocity.mY;
    this->velocity = Vec2D(this->velocity.mX, 0);
    this->velocity = Vec2D(this->velocity.mX, -y);
}

void Particle::incrementRange()
{
    if(this->range + 10 < MAXRANGE)
    {
        this->range+=10;
    }
}

void Particle::decrementRange()
{
    if(this->range -10 > MINRANGE)
    {
        this->range-=10;
    }
}

void Particle::incrementSpeed()
{
    if(this->speed < MAXSPEED)
    {
        this->speed+=1;
    }
}

void Particle::decrementSpeed()
{
    if(this->speed > MINSPEED)
    {
        this->speed-=1;
    }
}

void Particle::setTarget(Point2D point)
{
    this->target = point;
    this->hasTarget = true;
}

void Particle::evacuate()
{
    this->velocity = Vec2D(this->velocity.mX - this->speed, this->velocity.mY - this->speed);
}