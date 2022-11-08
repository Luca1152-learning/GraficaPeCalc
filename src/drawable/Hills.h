#ifndef GC_HILLS_H
#define GC_HILLS_H

#include "Drawable.h"
#include "../utils/color/Color.h"

class Hills : public Drawable {
private:
    Color lightGreen = Color::fromHex("#9DCE58");
    Color darkGreen = Color::fromHex("#92BF48");

    void setupShape() final override;

public:
    Hills();
};


#endif //GC_HILLS_H
