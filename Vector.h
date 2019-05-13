#pragma once
#include "stdafx.h"

class Vector {
public:
    Vector(float x, float y);
    void set(float nX, float nY);
    //methods for math.
    void add(Vector b);
    void add(float x, float y);
    static Vector add(Vector a, Vector b);
    static Vector add(Vector a, float x, float y);
    //only realized this was pointless until after I put it in. d'oh
    static Vector add(float x, float y, Vector a);
    static Vector add(float x, float y, float X, float Y);
    void sub(Vector b);
    void sub(float x, float y);
    static Vector sub(Vector a, Vector b);
    static Vector sub(Vector a, float x, float y);
    static Vector sub(float x, float y, Vector a);
    static Vector sub(float x, float y, float X, float Y);
    void mult(Vector b);
    void mult(float x, float y);
    void mult(float factor);
    static Vector mult(Vector a, Vector b);
    static Vector mult(float x, float y, float X, float Y);
    static Vector mult(Vector a, float factor);
    static Vector mult(float x, float y, float factor);
    void div(Vector b);
    void div(float x, float y);
    void div(float factor);
    static Vector div(Vector a, Vector b);
    static Vector div(float x, float y, float X, float Y);
    static Vector div(Vector a, float factor);
    static Vector div(float x, float y, float factor);
    //make it into a unit Vector
    void normalize();
    //turns it into a vecor of size magnitude
    void scaleTo(float size);
    //changing direction + for clockwise, - for countercloackwise
    void orient(float angle);
    //for angle given in radians
    void orientRad(float angle);
    //setting direction based on a measurement in degreees
    void setDir(float angle);
    //setting direction based on a measurement in radians
    void setDirRad(float angle);
    //magnitude
    float mag();
    //direction (degrees)
    float dir();
    //direction (radians)
    float dirRad();
    //dot product stuff
    float dot(Vector b);
    float dot(float x, float y);
    static float dot(Vector a, Vector b);
    static float dot(float x, float y, float X, float Y);
    //actual x, y coords of Vector
    float x, y;
private:
    float tempMag;
    float tempAngle;
};
