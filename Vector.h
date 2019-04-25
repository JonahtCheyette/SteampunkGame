#pragma once
#include "stdafx.h"

class Vector {
public:
    Vector(float x, float y);
    //methods for math.
    void add(Vector b);
    void add(float x, float y);
    static Vector add(Vector a, Vector b);
    static Vector add(float x, float y, float X, float Y);
    void sub(Vector b);
    void sub(float x, float y);
    static Vector sub(Vector a, Vector b);
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
    //make it into a unit vector
    void normalize();
    //turns it into a vecor of size magnitude
    void scaleTo(float size);
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
    //actual x, y coords of vector
    float x, y;
};
