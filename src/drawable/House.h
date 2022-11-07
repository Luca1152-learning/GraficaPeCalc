//
// Created by User on 01.11.2022.
//

#ifndef GC_HOUSE_H
#define GC_HOUSE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/render/ShadersUtils.h"
#include "../utils/color/Color.h"
#include "../utils/Constants.h"
#include "Drawable.h"
#include <vector>
#include "../utils/math/Vector.h"
#include "../utils/math/Matrix.h"

using namespace std;

class House : public Drawable {
private:
    Color sideWallColor = Color::fromHex("#DEDCDA");
    Color wallColor = Color::fromHex("#E9E7E8");
    Color roofGutterColor = Color::fromHex("#7C292E");
    Color roofColor = Color::fromHex("#BA4C40");
    Color windowColor = Color::fromHex("#458592");
    Color doorColor = Color::fromHex("#C5A671");
    Color doorFrameColor = Color::fromHex("#966D44");
    Color doorKnobColor = Color::fromHex("#EFCF9D");

    void setupTriangles() final override;

public:
    House(
            float centerX, float centerY, float scale, bool flip,
            Color sideWallColor, Color wallColor, Color roofGutterColor, Color roofColor,
            Color windowColor, Color doorColor, Color doorFrameColor, Color doorKnobColor
    );
};


#endif //GC_HOUSE_H
