#include "AwcColor.h"


Color::Color()
{
	r, g, b = 0;
	a = 255;
}

Color::Color(int _r, int _g, int _b, int _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

//Add two colors
Color operator+(const Color& color, const Color& color2)
{
	Color c;
	c.r = color.r + color2.r;
	c.g = color.g + color2.g;
	c.b = color.b + color2.b;
	return c;
}

//Subtract two colors
Color operator-(const Color& color, const Color& color2)
{
	Color c;
	c.r = color.r - color2.r;
	c.g = color.g - color2.g;
	c.b = color.b - color2.b;
	return c;
}

//Multiplies a color with an integer
Color operator*(const Color& color, int num)
{
	Color c;
	c.r = color.r * num;
	c.g = color.g * num;
	c.b = color.b * num;
	return c;
}

//Multiplies a color with an integer
Color operator*(int num, const Color& color)
{
	Color c;
	c.r = color.r * num;
	c.g = color.g * num;
	c.b = color.b * num;
	return c;
}

//Divides a color through an integer
Color operator/(const Color& color, int num)
{
	if (num == 0) return color;
	Color c;
	c.r = color.r / num;
	c.g = color.g / num;
	c.b = color.b / num;
	return c;
}

//Are both colors equal?
bool operator==(const Color& color, const Color& color2)
{
	return(color.r == color2.r && color.g == color2.g && color.b == color2.b);
}

//Are both colors not equal?
bool operator!=(const Color& color, const Color& color2)
{
	return(!(color.r == color2.r && color.g == color2.g && color.b == color2.b));
}
