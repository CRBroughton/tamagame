#include "raylib.h"
#include "world.h"

#ifndef TITLE_H
#define TITLE_H

WorldObject initTitleScreen(Texture2D texture);
WorldObject initStartText(Texture2D texture);
void initTitleScreenPosition(WorldObject *titleScreen);
void renderTitleScreen(WorldObject titleScreen);
#endif // TITLE_H
