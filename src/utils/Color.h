//
// Created by User on 01.11.2022.
//

#ifndef GC_COLOR_H
#define GC_COLOR_H


class Color {
private:
    int r;
    int g;
    int b;
public:
    Color(int r, int g, int b);

    float getR() const;

    float getG() const;

    float getB() const;
};


#endif //GC_COLOR_H
