
#pragma once

#ifndef CODE_ANIMATIONS_HELPER_H
#define CODE_ANIMATIONS_HELPER_H

#include <cstdint>

typedef struct uint8_Vec2 {
    uint8_t x;
    uint8_t y;

    uint8_Vec2() : x(0), y(0) {}
    uint8_Vec2(const uint8_t x, const uint8_t y) : x(x), y(y) {}

    uint8_Vec2 operator+(const uint8_Vec2& rhs) const {
        return uint8_Vec2(x + rhs.x, y + rhs.y);
    }
    uint8_Vec2 operator-(const uint8_Vec2& rhs) const {
        return uint8_Vec2(x - rhs.x, y - rhs.y);
    }
    uint8_Vec2 operator*(const uint8_t f) const {
        return uint8_Vec2(x * f, y * f);
    }
} intVec2;

#endif //CODE_ANIMATIONS_HELPER_H
