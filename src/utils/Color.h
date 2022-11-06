#ifndef GC_COLOR_H
#define GC_COLOR_H

#include "string"

using namespace std;

class Color {
private:
    float r, g, b, a;

    Color(int r, int g, int b, float a);

public:
    static Color fromHex(string hexCode, float alpha = 1.0f);

    float getR() const;

    float getG() const;

    float getB() const;

    float getA() const;
};


#endif //GC_COLOR_H
