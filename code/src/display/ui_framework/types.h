
#pragma once

#ifndef CODE_TYPES_H
#define CODE_TYPES_H

#include <cstdint>

typedef struct double_Vec2 {
    double x;
    double y;

    double_Vec2() : x(0), y(0) {}
    double_Vec2(const double x, const double y) : x(x), y(y) {}

    double_Vec2 operator+(const double_Vec2& rhs) const {
        return double_Vec2(x + rhs.x, y + rhs.y);
    }
    double_Vec2 operator-(const double_Vec2& rhs) const {
        return double_Vec2(x - rhs.x, y - rhs.y);
    }
    double_Vec2 operator*(const double f) const {
        return double_Vec2(x * f, y * f);
    }
} uint8_Vec2;

#endif
