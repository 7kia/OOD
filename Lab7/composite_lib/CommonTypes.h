#pragma once
#include <stdint.h>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;

	Rect(
		T left,
		T top,
		T width,
		T height
	);
};

template <typename T>
Rect<T>::Rect(
	T left,
	T top,
	T width,
	T height
)
	: left(left)
	, top(top)
	, width(width)
	, height(height)
{
}

typedef Rect<float> RectF;
typedef uint32_t RGBAColor;