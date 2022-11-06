//
// Created by User on 01.11.2022.
//

#ifndef GC_COLOR_H
#define GC_COLOR_H

#include "string"

using namespace std;

class Color {
private:
    float r, g, b;

    Color(int r, int g, int b);;

public:
    static Color fromHex(string hexCode);

    float getR() const;

    float getG() const;

    float getB() const;
};


#endif //GC_COLOR_H
