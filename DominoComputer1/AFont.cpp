#include "AFont.h"

AFont::AFont(std::string path, int size)
{
	font = TTF_OpenFont(path.c_str(), size);
}


AFont::~AFont()
{
//	TTF_CloseFont(font);
	font = NULL;
}
