#pragma once
#include <iostream>

struct Dimensions {
	int Width, Height;
	
	Dimensions();
	virtual ~Dimensions();

	int operator()(unsigned int w, unsigned int h);
	std::array<int, 2> Get();
};