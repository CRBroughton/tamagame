#include "include/raylib.h"
#include "include/raymath.h"
#include "include/constants.h"

const int screenWidth = 128;
const int screenHeight = 128;

int gameScreenWidth = 512;
int gameScreenHeight = 512;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

float getScale()
{
    float scale = MIN((float)GetScreenWidth() / gameScreenWidth, (float)GetScreenHeight() / gameScreenHeight);

    return scale;
};

// Compute required framebuffer scaling
// The scalefactor is:
// 128x128 = actual sprite size for game (in aseperite)
// scale = the games current scale based on the window size
// scaleFactor = how much to scale 128x128 by, example: if we set gameWidth and height to 512, it would be 4
// if set to 1024x1024, we set to 8
int scaleFactor = 4;
float getTextureScaleFactor()
{
    float textureScaleFactor = (getScale() * scaleFactor);
    return textureScaleFactor;
};