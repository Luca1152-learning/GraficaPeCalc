#ifndef GC_SEA_H
#define GC_SEA_H


#include "Drawable.h"
#include "../utils/color/Color.h"

class Sea : public Drawable {
private:
    Color darkBlue = Color::fromHex("#68ADC3");
    Color lightBlue = Color::fromHex("#85C9CC");

    bool increaseHeight = true;

    void setupShape() final override;

public:
    Sea();

    void stepAnimation() override;
};


#endif //GC_SEA_H
