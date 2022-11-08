#ifndef GC_TREE_H
#define GC_TREE_H


#include "Drawable.h"
#include "../utils/color/Color.h"

class Tree : public Drawable {
private:
    Color trunkColor = Color::fromHex("#AE7961");
    Color darkGreenColor = Color::fromHex("#56AF82");
    Color lightGreenColor = Color::fromHex("#5FC08C");

    void setupShape() final override;

public:
    Tree(vec2 center, float scale = 1.0f);
};


#endif //GC_TREE_H
