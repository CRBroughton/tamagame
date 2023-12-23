#include <stdbool.h> 

typedef struct moon {
    int x;
    int y;
} moon;

typedef struct sun {
    int x;
    int y;
} sun;

typedef struct world {
    moon moon;
    sun sun;
    bool night;
    bool day;
    int warmth;
} world;
