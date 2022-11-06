#include "Color.h"

Color::Color(int r, int g, int b, float a) : a(a) {
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
}

Color Color::fromHex(string hexCode, float alpha) {
    int r, g, b;
    sscanf(hexCode.c_str(), "#%02x%02x%02x", &r, &g, &b);

    return Color(r, g, b, alpha);
}

float Color::getR() const {
    return r;
}

float Color::getG() const {
    return g;
}

float Color::getB() const {
    return b;
}

float Color::getA() const {
    return a;
}

Color::operator Vector() const {
    return Vector(r, g, b, a);
}
