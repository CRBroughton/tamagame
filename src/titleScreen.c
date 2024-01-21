#include "include/raylib.h"
#include "include/utils.h"
#include "include/constants.h"
#include "include/world.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


WorldObject initTitleScreen(Texture2D texture)
{
    WorldObject title = initWorldObj(texture);
    title.x = -256 + (texture.width / 2);
    title.y = -256 + (texture.height / 2);

    return title;
}

WorldObject initStartText(Texture2D texture)
{
    WorldObject start = initWorldObj(texture);
    start.x = -256 + (texture.width / 2);

    return start;
}

void initTitleScreenPosition(WorldObject *titleScreen)
{
    titleScreen->position = (Vector2){
        gameScreenWidth / 2 - (titleScreen->texture.width * getScaleForTexture(titleScreen->texture)) / 2 + titleScreen->x,
        gameScreenHeight / 2 - (titleScreen->texture.height * getScaleForTexture(titleScreen->texture)) / 2 + titleScreen->y,
    };
}

void renderTitleScreen(WorldObject titleScreen)
{
    // 4 seems to be a 'magic number' for this
    DrawTextureEx(titleScreen.texture, titleScreen.position, 0.0f, getScaleForTexture(titleScreen.texture) * 4, WHITE);
}