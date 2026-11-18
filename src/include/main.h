#ifndef INC_MAIN_H
#define INC_MAIN_H
#include "raylib.h"

#define W 1600
#define H 900

#define STARTING_FPS 60

#define GET_GRAY(x, a) (Color){x, x, x, a}

#define GET_COLOR(r, g, b, a) (Color){r, g, b, a}

#define GET_RED_SHADE(r, a) (Color){r, 0, 0, a}
#define GET_GREEN_SHADE(g, a) (Color){0, g, 0, a}
#define GET_BLUE_SHADE(b, a) (Color){0, 0, b, a}

#define TEXT_SIZE 40

typedef struct {
	Vector2 center;
	Vector2 cursor;
	Vector2 screenSize;
	MouseCursor mouseCursor;
	Color BG_COLOR;
	int FPS;
	float deltaTime;
	float previousDeltaTime;
} GlobalState;

extern GlobalState globalState;

#endif
