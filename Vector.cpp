#include "stdafx.h"

Vector::Vector(float x, float y){
    this -> x = x;
    this -> y = y;
}

void Vector::add(Vector b){
    x += b.x;
    y += b.y;
}

void Vector::add(float x, float y){
    this -> x += x;
    this -> y += y;
}

Vector Vector::add(Vector a, Vector b){
    return Vector(a.x + b.x, a.y + b.y);
}

Vector Vector::add(float x, float y, float X, float Y){
    return Vector(x + X, y + Y);
}

void Vector::sub(Vector b){
    x -= b.x;
    y -= b.y;
}

void Vector::sub(float x, float y){
    this -> x -= x;
    this -> y -= y;
}

Vector Vector::sub(Vector a, Vector b){
    return Vector(a.x - b.x, a.y - b.y);
}

Vector Vector::sub(float x, float y, float X, float Y){
    return Vector(x - X, y - Y);
}

void Vector::mult(Vector b){
    x *= b.x;
    y *= b.y;
}

void Vector::mult(float x, float y){
    this -> x *= x;
    this -> y *= y;
}

void Vector::mult(float factor){
    this -> x *= factor;
    this -> y *= factor;
}

Vector Vector::mult(Vector a, Vector b){
    return Vector(a.x * b.x, a.y * b.y);
}

Vector Vector::mult(float x, float y, float X, float Y){
    return Vector(x * X, y * Y);
}

Vector Vector::mult(Vector a, float factor){
    return Vector(a.x * factor, a.y * factor);
}

Vector Vector::mult(float x, float y, float factor){
    return Vector(x * factor, y * factor);
}

void Vector::div(Vector b){
    x /= b.x;
    y /= b.y;
}

void Vector::div(float x, float y){
    this -> x /= x;
    this -> y /= y;
}

void Vector::div(float factor){
    this -> x /= factor;
    this -> y /= factor;
}

Vector Vector::div(Vector a, Vector b){
    return Vector(a.x / b.x, a.y / b.y);
}

Vector Vector::div(float x, float y, float X, float Y){
    return Vector(x / X, y / Y);
}

Vector Vector::div(Vector a, float factor){
    return Vector(a.x / factor, a.y / factor);
}

Vector Vector::div(float x, float y, float factor){
    return Vector(x / factor, y / factor);
}

void Vector::normalize(){
    x /= mag();
    x /= mag();
}

void Vector::scaleTo(float size){
    normalize();
    mult(size);
}

float Vector::mag(){
    return sqrt(pow(x,2) + pow(y,2));
}

float Vector::dir(){
    if(x > 0 && y >= 0){
        return atan(y/x);
    } else if (x <= 0 && y > 0){
        return atan((y/x) + 90);
    } else if (x < 0 && y <= 0){
        return atan((y/x) + 180);
    } else {
        return atan((y/x) + 270);
    }
}

float Vector::dirRad(){
    return dir() * M_PI /180;
}

float Vector::dot(Vector b){
    return (x * b.x) + (y * b.y);
}

float Vector::dot(float x, float y){
    return (this -> x * x) + (this -> y * y);
}

float Vector::dot(Vector a, Vector b){
    return (a.x * b.x) + (a.y * b.y);
}

float Vector::dot(float x, float y, float X, float Y){
    return (x * X) + (y * Y);
}