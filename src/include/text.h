#ifndef MY_TEXT_H
#define MY_TEXT_H
#include "./raylib.h"

#define Padding1(all) (Padding){all, all, all, all}
#define Padding2(v, h) (Padding){v, h, v, h}
#define Padding3(t, h, b) (Padding){t, h, b, h}
#define Padding4(t, r, b, l) (Padding){t, r, b, l}

typedef struct {
	int t,l,b,r;
} Margin, Padding;

typedef enum {
	FONT_TYPE_DEFAULT = (int)0,
	FONT_TYPE_LOADED,
} FONT_TYPE;

typedef struct {
	char **texts;
	int *lens;
	Color *colors;
	Color *bgColors;
	Padding perElemPadding;
	Padding padding;
	int fontSize;
	int count;
	int maxLen;
	int minLen;
	int gap;
	Color bgColor;
	Color border;
	int borderRadius;
	Font font;
} TextContainer;

typedef struct {
	char **texts;
	Vector2 *lens_n_fontSize;
	Color *colors;
	Color *bgColors;
	Padding perElemPadding;
	Padding padding;
	int fontSize;
	float spacing;
	int count;
	int maxLen;
	int minLen;
	int gap;
	Color bgColor;
	Color border;
	int borderRadius;
	Font font;
} TextContainerEx;

#define TCEvent(x) TC_EVENT_##x

typedef enum {
	TCEvent(NONE) = (int)0,
	TCEvent(HOVER),
	TCEvent(DOWN),
	TCEvent(CLICKED),
} TCEvent;

typedef struct {
	int index;
	TCEvent event;
} TextContainer_State;

void DrawTextCenterLEx(Font *LoadedFont, const char *text, int posX, int posY, Vector2 textMeasurement, float spacing, Color color);

void DrawTextCenterEx(Font *LoadedFont, const char *text, int posX, int posY, float fontSize, float spacing, Color color);

void DrawTextCenter(const char *text, int posX, int posY, int fontSize, Color color);

void DrawTextCenterL(const char *text, int len, int posX, int posY, int fontSize, Color color);

void DrawTextContainer(TextContainer *container, TextContainer_State *state, int posX, int posY);

void GetTextContainerState(TextContainer *container, TextContainer_State *state, int posX, int posY, Vector2 *Cursor);

void DrawTextContainerEx(TextContainerEx *container, TextContainer_State *state, int posX, int posY);

void GetTextContainerStateEx(TextContainerEx *container, TextContainer_State *state, int posX, int posY, Vector2 *Cursor);

#endif
