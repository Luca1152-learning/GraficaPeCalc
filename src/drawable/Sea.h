#ifndef GC_SEA_H
#define GC_SEA_H


#include "Drawable.h"
#include "../utils/color/Color.h"

class Sea : public Drawable {
private:
    Color lightBlue = Color::fromHex("#70CDCF");
    Color darkBlue = Color::fromHex("#4FAFCA");

    bool increaseHeight = true;

    void setupShape() final override;

public:
    Sea();

    void stepAnimation() override;
};


#endif //GC_SEA_H
