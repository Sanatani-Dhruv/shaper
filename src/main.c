#include "include/main.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/text.h"
#include "include/utils.h"

GlobalState globalState = {
	.center = {
		(float)W/2,
		(float)H/2,
	},
	.cursor = {0},
	.mouseCursor = MOUSE_CURSOR_ARROW,
	.FPS = STARTING_FPS,
	.deltaTime = 0,
	.BG_COLOR = GET_GRAY(200, 255),
	.previousDeltaTime = 0,
};

#define CHANGE_FACTOR 100
#define MAX_PER_SHAPE_ITEMS 100

enum Shapes {
	SHAPE_RECT = (int)0,
	SHAPE_TRI,
	SHAPE_CIRCLE,
};

typedef struct {
	Rectangle rect;
	Color color;
} Rectangle_W;

typedef struct {
	Vector2 pos;
	Vector2 a;
	Vector2 b;
	Vector2 c;
	Color color;
} Triangle;

typedef struct {
	Vector2 pos;
	float r;
	Color color;
} Circle;

Rectangle_W rectangles[MAX_PER_SHAPE_ITEMS] = {0};
int rect_i = 0;

Triangle triangles[MAX_PER_SHAPE_ITEMS] = {0};
int tri_i = 0;

Circle circles[MAX_PER_SHAPE_ITEMS] = {0};
int circle_i = 0;

enum Shapes current_shape = SHAPE_RECT;

void initRectangles();
void initTriangles();
void initCircles();

void handleRect();
void handleTri();
void handleCircle();

void drawRect(Rectangle_W *rect);
void drawTri(Triangle *tri);
void drawCircle(Circle *circle);

void resetRect(Rectangle_W *rect);
void resetTri(Triangle *tri);
void resetCircle(Circle *circle);

void handleColor(Color *color);

MouseCursor newMouseCursor = MOUSE_CURSOR_ARROW;

int main() {
	srand(time(NULL));

	initRectangles();
	initTriangles();
	initCircles();

	InitWindow(W, H, "Welcome to Platformer");
	SetTargetFPS(globalState.FPS);


	SetExitKey(KEY_Q);

	while (!WindowShouldClose()) {
		globalState.cursor = GetMousePosition();
		globalState.previousDeltaTime = globalState.deltaTime;
		globalState.deltaTime = GetFrameTime();

		if (IsKeyPressed(KEY_I)) {
			current_shape = SHAPE_TRI;
		}

		if (IsKeyPressed(KEY_O)) {
			current_shape = SHAPE_RECT;
		}

		if (IsKeyPressed(KEY_P)) {
			current_shape = SHAPE_CIRCLE;
		}

		switch (current_shape) {
			case SHAPE_RECT:
				handleRect();
				break;
			case SHAPE_TRI:
				handleTri();
				break;
			case SHAPE_CIRCLE:
				handleCircle();
				break;
		}

		BeginDrawing();
		ClearBackground(globalState.BG_COLOR);

		int gap_i = 1;

		switch (current_shape) {
			case SHAPE_RECT:
				DrawTextCenter("RECT", W - 200, H - 100, TEXT_SIZE, BLACK);
				DrawText(
					TextFormat(
						".x: %.2f",
						rectangles[rect_i].rect.x
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".y: %.2f",
						rectangles[rect_i].rect.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".width: %.2f",
						rectangles[rect_i].rect.width
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".height: %.2f",
						rectangles[rect_i].rect.height
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".r: %3d | .g: %3d | .b: %3d",
						rectangles[rect_i].color.r,
						rectangles[rect_i].color.g,
						rectangles[rect_i].color.b
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						"index: %d",
						rect_i
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				break;
			case SHAPE_TRI:
				DrawTextCenter("TRI", W - 200, H - 100, TEXT_SIZE, BLACK);
				DrawText(
					TextFormat(
						".pos.x: %.2f | .pos.y: %.2f",
						triangles[tri_i].pos.x,
						triangles[tri_i].pos.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".a.x: %.2f | .a.y: %.2f",
						triangles[tri_i].a.x,
						triangles[tri_i].a.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".b.x: %.2f | .b.y: %.2f",
						triangles[tri_i].b.x,
						triangles[tri_i].b.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".c.x: %.2f | .c.y: %.2f",
						triangles[tri_i].c.x,
						triangles[tri_i].c.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".r: %3d | .g: %3d | .b: %3d",
						triangles[tri_i].color.r,
						triangles[tri_i].color.g,
						triangles[tri_i].color.b
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						"index: %d",
						tri_i
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);
				break;
			case SHAPE_CIRCLE:
				DrawTextCenter("CIRCLE", W - 200, H - 100, TEXT_SIZE, BLACK);

				DrawText(
					TextFormat(
						".pos.x: %.2f",
						circles[circle_i].pos.x
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".pos.y: %.2f",
						circles[circle_i].pos.y
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".r: %.2f",
						circles[circle_i].r
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						".r: %3d | .g: %3d | .b: %3d",
						circles[circle_i].color.r,
						circles[circle_i].color.g,
						circles[circle_i].color.b
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				DrawText(
					TextFormat(
						"index: %d",
						circle_i
					),
					100,
					TEXT_SIZE * gap_i++,
					TEXT_SIZE,
					BLACK
				);

				break;
		}

		for (int i = 0; i < MAX_PER_SHAPE_ITEMS; i++){
			drawRect(
				&rectangles[i]
			);
			if (rect_i == i) {
				int offset = 10;

				DrawRectangleLines(
					rectangles[i].rect.x + offset,
					rectangles[i].rect.y + offset,
					rectangles[i].rect.width - (2 * offset),
					rectangles[i].rect.height - (2 * offset),
					GOLD
				);
			}
		}

		for (int i = 0; i < MAX_PER_SHAPE_ITEMS; i++){
			drawTri(
				&triangles[i]
			);

			if (tri_i == i) {
				int offset = 10;
				Vector2 a = triangles[i].a;
				Vector2 b = triangles[i].b;
				Vector2 c = triangles[i].c;

				a.x += triangles[i].pos.x;
				a.y += triangles[i].pos.y + offset;

				b.x += triangles[i].pos.x + ( 2 * offset);
				b.y += triangles[i].pos.y - ( 1 * offset);

				c.x += triangles[i].pos.x - ( 2 * offset);
				c.y += triangles[i].pos.y - ( 1 * offset);

				DrawTriangleLines(
					a,
					b,
					c,
					GOLD
				);
			}
		}

		for (int i = 0; i < MAX_PER_SHAPE_ITEMS; i++){
			drawCircle(
				&circles[i]
			);
		}

		if (globalState.mouseCursor != newMouseCursor) {
			SetMouseCursor(newMouseCursor);
			globalState.mouseCursor = newMouseCursor;
		}

		/* sleep(1); */
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

void initRectangles() {
	for (int i = 0 ; i < MAX_PER_SHAPE_ITEMS; i++) {
		rectangles[i].color.a = 255;
	}
}

void drawRect(Rectangle_W *rect) {
	DrawRectangleRec(
		rect->rect,
		rect->color
	);
}

void handleRect() {

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		SetMousePosition(rectangles[rect_i].rect.x + rectangles[rect_i].rect.width, rectangles[rect_i].rect.y + rectangles[rect_i].rect.height);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		rectangles[rect_i].rect.width = globalState.cursor.x - rectangles[rect_i].rect.x;
		rectangles[rect_i].rect.height = globalState.cursor.y - rectangles[rect_i].rect.y;
		newMouseCursor = MOUSE_CURSOR_RESIZE_ALL;
		return;
	} else {
		newMouseCursor = MOUSE_CURSOR_ARROW;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		rectangles[rect_i].rect.x = globalState.cursor.x;
		rectangles[rect_i].rect.y = globalState.cursor.y;
		newMouseCursor = MOUSE_CURSOR_RESIZE_ALL;
	} else {
		newMouseCursor = MOUSE_CURSOR_ARROW;
	}

	if (IsKeyPressed(KEY_N)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			rect_i--;

			if (rect_i < 0) {
				rect_i = 0;
			}
		} else {
			rect_i++;

			if (rect_i > MAX_PER_SHAPE_ITEMS) {
				rect_i = MAX_PER_SHAPE_ITEMS;
			}
		}
	}

	if (IsKeyDown(KEY_D)) {
		rectangles[rect_i].rect.x += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_A)) {
		rectangles[rect_i].rect.x -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_W)) {
		rectangles[rect_i].rect.y -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_S)) {
		rectangles[rect_i].rect.y += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_K)) {
		rectangles[rect_i].rect.height -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_J)) {
		rectangles[rect_i].rect.height += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_L)) {
		rectangles[rect_i].rect.width += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_H)) {
		rectangles[rect_i].rect.width -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyPressed(KEY_ZERO)) {
		resetRect(&rectangles[rect_i]);
	}

	handleColor(&rectangles[rect_i].color);
}

void resetRect(Rectangle_W *rect) {
	rect->color = GET_GRAY(0, 255);

	rect->rect = GETRECTANGLE(0, 0, 0, 0);
}

void initTriangles() {
	for (int i = 0 ; i < MAX_PER_SHAPE_ITEMS; i++) {
		triangles[i].color.a = 255;
	}
}

void drawTri(Triangle *tri) {
	Vector2 a = tri->a;
	Vector2 b = tri->b;
	Vector2 c = tri->c;

	a.x += tri->pos.x;
	a.y += tri->pos.y;

	b.x += tri->pos.x;
	b.y += tri->pos.y;

	c.x += tri->pos.x;
	c.y += tri->pos.y;

	DrawTriangle(
		a,
		b,
		c,
		tri->color
	);
}

void handleTri() {

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		triangles[tri_i].pos.x = globalState.cursor.x;
		triangles[tri_i].pos.y = globalState.cursor.y;
		newMouseCursor = (MOUSE_CURSOR_RESIZE_ALL);
		return;
	} else {
		newMouseCursor = (MOUSE_CURSOR_ARROW);
	}

	/* Handle 1st(a) Point */
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_ONE)) {
		SetMousePosition(triangles[tri_i].a.x + triangles[tri_i].pos.x, triangles[tri_i].a.y + triangles[tri_i].pos.y);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_ONE)) {
		triangles[tri_i].a.x = globalState.cursor.x - triangles[tri_i].pos.x;
		triangles[tri_i].a.y  = globalState.cursor.y - triangles[tri_i].pos.y;
		newMouseCursor = (MOUSE_CURSOR_RESIZE_ALL);
		return;
	} else {
		newMouseCursor = (MOUSE_CURSOR_ARROW);
	}

	/* Handle 2nd(b) Point */
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_TWO)) {
		SetMousePosition(triangles[tri_i].b.x + triangles[tri_i].pos.x, triangles[tri_i].b.y + triangles[tri_i].pos.y);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_TWO)) {
		triangles[tri_i].b.x = globalState.cursor.x - triangles[tri_i].pos.x;
		triangles[tri_i].b.y  = globalState.cursor.y - triangles[tri_i].pos.y;
		newMouseCursor = (MOUSE_CURSOR_RESIZE_ALL);
		return;
	} else {
		newMouseCursor = (MOUSE_CURSOR_ARROW);
	}

	/* Handle 3rd(c) Point */
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_THREE)) {
		SetMousePosition(triangles[tri_i].c.x + triangles[tri_i].pos.x, triangles[tri_i].c.y + triangles[tri_i].pos.y);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_THREE)) {
		triangles[tri_i].c.x = globalState.cursor.x - triangles[tri_i].pos.x;
		triangles[tri_i].c.y  = globalState.cursor.y - triangles[tri_i].pos.y;
		newMouseCursor = (MOUSE_CURSOR_RESIZE_ALL);
		return;
	} else {
		newMouseCursor = (MOUSE_CURSOR_ARROW);
	}

	if (IsKeyPressed(KEY_N)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			tri_i--;

			if (tri_i < 0) {
				tri_i = 0;
			}
		} else {
			tri_i++;

			if (tri_i > MAX_PER_SHAPE_ITEMS) {
				tri_i = MAX_PER_SHAPE_ITEMS;
			}
		}
	}

	if (IsKeyDown(KEY_ONE)) {
		if (IsKeyDown(KEY_X)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].a.x -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].a.x += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
		if (IsKeyDown(KEY_Y)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].a.y -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].a.y += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
	}

	if (IsKeyDown(KEY_TWO)) {
		if (IsKeyDown(KEY_X)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].b.x -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].b.x += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
		if (IsKeyDown(KEY_Y)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].b.y -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].b.y += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
	}

	if (IsKeyDown(KEY_THREE)) {
		if (IsKeyDown(KEY_X)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].c.x -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].c.x += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
		if (IsKeyDown(KEY_Y)) {
			if (IsKeyDown(KEY_LEFT_SHIFT)) {
				triangles[tri_i].c.y -= globalState.deltaTime * CHANGE_FACTOR;
			} else {
				triangles[tri_i].c.y += globalState.deltaTime * CHANGE_FACTOR;
			}
		}
	}

	if (IsKeyPressed(KEY_ZERO)) {
		resetTri(&triangles[tri_i]);
	}

	handleColor(&triangles[tri_i].color);
}

void resetTri(Triangle *tri) {
	tri->color = GET_GRAY(0, 255);

	tri->pos = GETVECTOR2(0, 0);

	tri->a = GETVECTOR2(0, 0);
	tri->b = GETVECTOR2(0, 0);
	tri->c = GETVECTOR2(0, 0);
}

void initCircles() {
	for (int i = 0 ; i < MAX_PER_SHAPE_ITEMS; i++) {
		circles[i].color.a = 255;
	}
}

void drawCircle(Circle *circle) {
	DrawCircleV(
		circle->pos,
		circle->r,
		circle->color
	);
}

void handleCircle() {

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		circles[circle_i].pos.x = globalState.cursor.x;
		circles[circle_i].pos.y = globalState.cursor.y;
		newMouseCursor = (MOUSE_CURSOR_RESIZE_ALL);
	} else {
		newMouseCursor = (MOUSE_CURSOR_ARROW);
	}

	if (IsKeyPressed(KEY_N)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			circle_i--;

			if (circle_i < 0) {
				circle_i = 0;
			}
		} else {
			circle_i++;

			if (circle_i > MAX_PER_SHAPE_ITEMS) {
				circle_i = MAX_PER_SHAPE_ITEMS;
			}
		}
	}

	if (IsKeyDown(KEY_D)) {
		circles[circle_i].pos.x += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_A)) {
		circles[circle_i].pos.x -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_W)) {
		circles[circle_i].pos.y -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_S)) {
		circles[circle_i].pos.y += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_K)) {
		circles[circle_i].r -= globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyDown(KEY_J)) {
		circles[circle_i].r += globalState.deltaTime * CHANGE_FACTOR;
	}

	if (IsKeyPressed(KEY_ZERO)) {
		resetCircle(&circles[circle_i]);
	}

	handleColor(&circles[circle_i].color);
}

void resetCircle(Circle *circle) {
	circle->color = GET_GRAY(0, 255);

	circle->pos = GETVECTOR2(0, 0);

	circle->r = 0;
}

void handleColor(Color *color) {
	if (IsKeyDown(KEY_R)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			if (color->r != 0) {
				color->r--;
			}
		} else {
			if (color->r != 255) {
				color->r++;
			}
		}
	}

	if (IsKeyDown(KEY_G)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			if (color->g != 0) {
				color->g--;
			}
		} else {
			if (color->g != 255) {
				color->g++;
			}
		}
	}

	if (IsKeyDown(KEY_B)) {
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			if (color->b != 0) {
				color->b--;
			}
		} else {
			if (color->b != 255) {
				color->b++;
			}
		}
	}
}
