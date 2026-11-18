#include "include/text.h"
#include "include/utils.h"
#ifdef DEBUG
#include <stdio.h>
#endif

void DrawTextCenterL(const char *text, int len, int posX, int posY, int fontSize, Color color) {
	DrawText(text, posX - (len) / 2, posY - (fontSize) / 2, fontSize, color);
}

void DrawTextCenter(const char *text, int posX, int posY, int fontSize, Color color) {
	int len = MeasureText(text, fontSize);
	DrawTextCenterL(text, len, posX, posY, fontSize, color);
}

void DrawTextCenterLEx(Font *LoadedFont, const char *text, int posX, int posY, Vector2 textMeasurement, float spacing, Color color) {
	DrawTextEx(*LoadedFont, text, (Vector2){posX - (textMeasurement.x) / 2, posY - (textMeasurement.y) / 2}, textMeasurement.y, spacing, color);

	/* printf("%f %f\n", posX - (textMeasurement.x) / 2,  posY - (textMeasurement.y) / 2); */
}

void DrawTextCenterEx(Font *LoadedFont, const char *text, int posX, int posY, float fontSize, float spacing, Color color) {
	Vector2 textMeasurement = MeasureTextEx(*LoadedFont, text, fontSize, spacing);
	DrawTextCenterLEx(LoadedFont, text, posX, posY, textMeasurement, spacing, color);
}

void DrawTextContainer(TextContainer *container, TextContainer_State *state, int posX, int posY) {
	DrawRectangleRounded(
		(Rectangle){
			posX - (((float)container->maxLen / 2) + container->padding.l),
			posY - (((float)container->fontSize + container->gap) / 2),
			container->maxLen + (container->padding.l + container->padding.r),
			container->count * (container->fontSize + container->gap),
		},
		((float)5 / 100),
		100,
		container->bgColor
	);

	for (int i = 0; i < container->count; i++) {
		Color color = container->colors[i];
		if (state->index == i) {
			if (state->event == TCEvent(HOVER)) {
				if (color.a >= 50) {
					color.a -= 50;
				} else {
					color.a = 0;
				}
			} else if (state->event == TCEvent(CLICKED)) {
				if (color.a >= 80) {
					color.a -= 80;
				} else {
					color.a = 0;
				}
			} else if (state->event == TCEvent(DOWN)) {
				if (color.a >= 100) {
					color.a -= 100;
				} else {
					color.a = 0;
				}
			}
			/* printf("%d %d %d %d\n", color.r, color.g, color.b, color.a); */
		}

		Color bgColor = {0};
		if (notnull(container->bgColors)) {
			bgColor = container->bgColors[i];
			if (state->index == i) {
				if (state->event == TCEvent(HOVER)) {
					if (bgColor.a >= 50) {
						bgColor.a -= 50;
					} else {
						bgColor.a = 0;
					}
				} else if (state->event == TCEvent(CLICKED)) {
					if (bgColor.a >= 80) {
						bgColor.a -= 80;
					} else {
						bgColor.a = 0;
					}
				} else if (state->event == TCEvent(DOWN)) {
					if (bgColor.a >= 100) {
						bgColor.a -= 100;
					} else {
						bgColor.a = 0;
					}
				}
				/* printf("%d %d %d %d\n", bgColor.r, bgColor.g, bgColor.b, bgColor.a); */
			}

			if (bgColor.a > 0){
				DrawRectangleRounded(
					(Rectangle){
						posX - ((float)container->lens[i] / 2) - (container->perElemPadding.l),
						posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i) - (container->perElemPadding.t),
						container->lens[i] + (container->perElemPadding.l + container->perElemPadding.r),
						container->fontSize + (container->perElemPadding.t + container->perElemPadding.b),
					},
					(float)container->borderRadius / 100,
					container->borderRadius,
					bgColor
				);
			}
		}

		DrawTextCenterL(
			container->texts[i],
			container->lens[i],
			posX,
			posY + (container->fontSize * (i)) + (container->gap * i),
			container->fontSize, color
		);

		/* DrawCircle( */
		/* 	posX - ((float)container->lens[i] / 2) - (container->perElemPadding.l), */
		/* 	posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i) - (container->perElemPadding.t), */
		/* 	3, */
		/* 	WHITE */
		/* ); */
	}

	return;
}

void GetTextContainerState(TextContainer *container, TextContainer_State *state, int posX, int posY, Vector2 *Cursor) {
	if (state->index != -1) {
		state->index = -1;
	}

	for (int i = 0; i < container->count; i++) {
		Rectangle rect = {
			posX - ((float)container->lens[i] / 2) - (container->perElemPadding.l),
			posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i) - (container->perElemPadding.t),
			container->lens[i] + (container->perElemPadding.l + container->perElemPadding.r),
			container->fontSize + (container->perElemPadding.t + container->perElemPadding.b)
		};

		/* printf( */
		/* 	"(Rectangle){\n" */
		/* 		"\tposX = %d,\n" */
		/* 		"\tposY + (container->fontSize * (i)), = %f,\n" */
		/* 		"\tcontainer->lens[i], = %d,\n" */
		/* 		"\tcontainer->fontSize = %d,\n" */
		/* 	"}\n", */
		/* 	(int)(posX - ((float)container->lens[i] / 2)), */
		/* 	posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i), */
		/* 	container->lens[i], */
		/* 	container->fontSize */
		/* ); */

		if (CheckCollisionPointRec(*Cursor, rect)) {
			state->index = i;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				state->event = TCEvent(CLICKED);
				break;
			}

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				state->event = TCEvent(DOWN);
				break;
			}

			state->event = TCEvent(HOVER);
			break;
		}

		state->event = TCEvent(NONE);
	}
}

void DrawTextContainerEx(TextContainerEx *container, TextContainer_State *state, int posX, int posY) {
	DrawRectangleRounded(
		(Rectangle){
			posX - (((float)container->maxLen / 2) + container->padding.l),
			posY - (((float)container->fontSize + container->gap) / 2),
			container->maxLen + (container->padding.l + container->padding.r),
			container->count * (container->fontSize + container->gap),
		},
		0.05,
		100,
		container->bgColor
	);

	for (int i = 0; i < container->count; i++) {
		Color color = container->colors[i];
		if (state->index == i) {
			if (state->event == TCEvent(HOVER)) {
				if (color.a >= 50) {
					color.a -= 50;
				} else {
					color.a = 0;
				}
			} else if (state->event == TCEvent(CLICKED)) {
				if (color.a >= 80) {
					color.a -= 80;
				} else {
					color.a = 0;
				}
			} else if (state->event == TCEvent(DOWN)) {
				if (color.a >= 100) {
					color.a -= 100;
				} else {
					color.a = 0;
				}
			}
			/* printf("%d %d %d %d\n", color.r, color.g, color.b, color.a); */
		}

		Color bgColor = {0};
		if (notnull(container->bgColors)) {
			bgColor = container->bgColors[i];

			if (state->index == i) {
				if (state->event == TCEvent(HOVER)) {
					if (bgColor.a >= 50) {
						bgColor.a -= 50;
					} else {
						bgColor.a = 0;
					}
				} else if (state->event == TCEvent(CLICKED)) {
					if (bgColor.a >= 80) {
						bgColor.a -= 80;
					} else {
						bgColor.a = 0;
					}
				} else if (state->event == TCEvent(DOWN)) {
					if (bgColor.a >= 100) {
						bgColor.a -= 100;
					} else {
						bgColor.a = 0;
					}
				}
				/* printf("%d %d %d %d\n", bgColor.r, bgColor.g, bgColor.b, bgColor.a); */
			}

			if (bgColor.a > 0){
				DrawRectangleRounded(
					(Rectangle){
						posX - ((float)container->lens_n_fontSize[i].x / 2) - (container->perElemPadding.l),
						posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i) - (container->perElemPadding.t),
						container->lens_n_fontSize[i].x + (container->perElemPadding.l + container->perElemPadding.r),
						container->fontSize + (container->perElemPadding.t + container->perElemPadding.b),
					},
					(float)container->borderRadius / 100,
					container->borderRadius,
					bgColor
				);
			}
		}
		/* DrawTextCenterL(container->texts[i], container->lens_n_fontSize[i].x, posX, posY + (container->fontSize * (i)) + (container->gap * i), container->fontSize, color); */

		DrawTextCenterLEx(
			&container->font,
			container->texts[i],
			posX,
			posY + (container->fontSize * (i)) + (container->gap * i),
			container->lens_n_fontSize[i],
			container->spacing,
			color
		);
	}

	return;
}

void GetTextContainerStateEx(TextContainerEx *container, TextContainer_State *state, int posX, int posY, Vector2 *Cursor) {
	if (state->index != -1) {
		state->index = -1;
	}

	for (int i = 0; i < container->count; i++) {
		Rectangle rect = {
			posX - ((float)container->lens_n_fontSize[i].x / 2) - (container->perElemPadding.l),
			posY + ((float)(2 * container->lens_n_fontSize[i].y * (i) - container->fontSize) / 2) + (container->gap) * (i) - (container->perElemPadding.t),
			container->lens_n_fontSize[i].x + (container->perElemPadding.l + container->perElemPadding.r),
			container->fontSize + (container->perElemPadding.t + container->perElemPadding.b)
		};

		/* printf( */
		/* 	"(Rectangle){\n" */
		/* 		"\tposX = %d,\n" */
		/* 		"\tposY + (container->fontSize * (i)), = %f,\n" */
		/* 		"\tcontainer->lens_n_fontSize[i].x, = %d,\n" */
		/* 		"\tcontainer->fontSize = %d,\n" */
		/* 	"}\n", */
		/* 	(int)(posX - ((float)container->lens_n_fontSize[i].x / 2)), */
		/* 	posY + ((float)(2 * container->fontSize * (i) - container->fontSize) / 2) + (container->gap) * (i), */
		/* 	container->lens_n_fontSize[i].x, */
		/* 	container->fontSize */
		/* ); */

		if (CheckCollisionPointRec(*Cursor, rect)) {
			state->index = i;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				state->event = TCEvent(CLICKED);
				break;
			}

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				state->event = TCEvent(DOWN);
				break;
			}

			state->event = TCEvent(HOVER);
			break;
		}

		state->event = TCEvent(NONE);
	}
}
