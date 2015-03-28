#pragma once

class Color
{
public:
	int r, g, b;
	Color();
	Color(int _r, int _g, int _b);
};

Color operator+(const Color& color, const Color& color2);
Color operator-(const Color& color, const Color& color2);
Color operator*(const Color& color, int a);
Color operator*(int a, const Color& color);
Color operator/(const Color& color, int a);
bool operator==(const Color& color, const Color& color2);
bool operator!=(const Color& color, const Color& color2);

static const Color RGB_Black(0, 0, 0);
static const Color RGB_Red(255, 0, 0);
static const Color RGB_Green(0, 255, 0);
static const Color RGB_Blue(0, 0, 255);
static const Color RGB_Cyan(0, 255, 255);
static const Color RGB_Magenta(255, 0, 255);
static const Color RGB_Yellow(255, 255, 0);
static const Color RGB_White(255, 255, 255);
static const Color RGB_Gray(128, 128, 128);
static const Color RGB_Grey(192, 192, 192);
static const Color RGB_Maroon(128, 0, 0);
static const Color RGB_Darkgreen(0, 128, 0);
static const Color RGB_Navy(0, 0, 128);
static const Color RGB_Teal(0, 128, 128);
static const Color RGB_Purple(128, 0, 128);
static const Color RGB_Olive(128, 128, 0);
