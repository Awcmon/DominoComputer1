#include "AwcColor.h"


Color::Color()
{
	r, g, b = 0;
}

Color::Color(int _r, int _g, int _b)
{
	r = _r;
	g = _g;
	b = _b;
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
Color operator*(const Color& color, int a)
{
	Color c;
	c.r = color.r * a;
	c.g = color.g * a;
	c.b = color.b * a;
	return c;
}

//Multiplies a color with an integer
Color operator*(int a, const Color& color)
{
	Color c;
	c.r = color.r * a;
	c.g = color.g * a;
	c.b = color.b * a;
	return c;
}

//Divides a color through an integer
Color operator/(const Color& color, int a)
{
	if (a == 0) return color;
	Color c;
	c.r = color.r / a;
	c.g = color.g / a;
	c.b = color.b / a;
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
