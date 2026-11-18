#ifndef INC_MAIN_H
#define INC_MAIN_H
#include "raylib.h"

#define W 1600
#define H 900

#define STARTING_FPS 60

#define GET_GRAY(x, a) (Color){x, x, x, a}

#define TEXT_SIZE 40

typedef struct {
	Vector2 center;
	Vector2 cursor;
	MouseCursor mouseCursor;
	Color BG_COLOR;
	int FPS;
	float deltaTime;
	float previousDeltaTime;
} GlobalState;

extern GlobalState globalState;

#endif
