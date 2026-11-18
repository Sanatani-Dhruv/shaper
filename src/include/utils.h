#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdlib.h>

#define null(x) (x == NULL)
#define notnull(x) (x != NULL)

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

#define GETVECTOR2(x, y) (Vector2){x, y}

#define GETRECTANGLE(x, y, width, height) (Rectangle){x, y, width, height}

#define STRINGIFY(x) #x

#define STRINGMACRO(x) STRINGIFY(x)

#define passedTime(variable, timeInSec) (variable >= timeInSec)

#define PRINT_RECTANGLE(rect, i)   \
	printf(                    \
		"%d = (Rectangle){\n"  \
			".x = %.2f,\n"       \
			".y = %.2f,\n"       \
			".width = %.2f,\n"   \
			".height = %.2f,\n"  \
		"}\n\n"                \
		,                      \
		i + 1,                 \
		rect.x,                \
		rect.y,                \
		rect.width,            \
		rect.height            \
  );                           \

#define PRINT_CAR(car, i)   \
	printf(                    \
		"%d = (Car){\n"  \
			".posX = %.2f,\n"       \
			".posY = %.2f,\n"       \
			".width = %.2f,\n"   \
			".height = %.2f,\n"  \
		"}\n\n"                \
		,                      \
		i + 1,                 \
		(car).posX,                \
		(car).posY,                \
		(car).width,            \
		(car).height            \
  );                           \

#define PRINT_SIZEOF(x) printf("sizeof(" STRINGMACRO(x) ") = %zu\n", sizeof(x))

int getrandom(int start, int end);

#endif
