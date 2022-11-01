#include "Color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}

float Color::getR() const {
    return (float) r / 255;
}

float Color::getG() const {
    return (float) g / 255;
}

float Color::getB() const {
    return (float) b / 255;
}
