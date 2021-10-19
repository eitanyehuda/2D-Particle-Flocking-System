#include "mathLib2D.h"

#include <math.h>


// Point 2D
Point2D::Point2D()
{
}

Point2D::Point2D(float inX, float inY)
{
    this->mX=inX;
    this->mY=inY;
}

float Point2D::distanceTo(Point2D other)
{
    return sqrt(pow(this->mX - other.mX,2) + pow(this->mY - other.mY,2));
}

float Point2D::fastDistanceTo(Point2D other)
{
    return pow(this->mX - other.mX,2) + pow(this->mY - other.mY,2);
}


// Vector 2D
Vec2D::Vec2D()
{
}

Vec2D::Vec2D(float inX, float inY)
{
    this->mX=inX;
    this->mY=inY;
}

float Vec2D::length()
{
    return sqrt(pow(this->mX,2) + pow(this->mY,2));
}

Vec2D Vec2D::normalize()
{
    float x = this->mX/this->length();
    float y = this->mY/this->length();

    return Vec2D(x,y);
}

Vec2D Vec2D::multiply(float scalar)
{
    float x = this->mX*scalar;
    float y = this->mY*scalar;

    return Vec2D(x,y);
}

Point2D Vec2D::movePoint(Point2D source)
{
    float newX = source.mX + this->mX;
    float newY = source.mY + this->mY;
    return Point2D(newX,newY);
}

Vec2D Vec2D::createVector(Point2D p1, Point2D p2)
{
    float x = p2.mX - p1.mX;
    float y =p2.mY - p1.mY;
    return Vec2D(x,y);
}