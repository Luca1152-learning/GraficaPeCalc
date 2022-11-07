#include "Circle.h"

void Circle::setupShape() {
    vector<Vector> triangleVerticesVec;
    vector<Vector> triangleVerticesColorsVec;

    for (int i = 1; i <= 360; i++) {
        float currentX = cos(radians((float) i)), currentY = sin(radians((float) i));
        float previousX = cos(radians((float) i - 1)), previousY = sin(radians((float) i - 1));

        // Add vertices
        triangleVerticesVec.push_back({0, 0});
        triangleVerticesVec.push_back({currentX, currentY});
        triangleVerticesVec.push_back({previousX, previousY});

        // Add colors
        triangleVerticesColorsVec.push_back(color);
        triangleVerticesColorsVec.push_back(color);
        triangleVerticesColorsVec.push_back(color);
    }


    triangleVertices = {4, triangleVerticesVec};
    triangleVerticesColors = {4, triangleVerticesColorsVec};
}

Circle::Circle(float centerX, float centerY, float radius, Color color) :
        Drawable(centerX, centerY, radius, radius), color(color) {
    setupShape();
    setupVao();
}
