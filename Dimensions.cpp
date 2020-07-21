#include "Dimensions.h"
#include <array>

Dimensions::Dimensions() {
	this->Height = 500;
	this->Width = 500;
}

Dimensions::~Dimensions() {
}

std::array<int, 2> Dimensions::Get() {
	return std::array<int, 2> {Width, Height};
}

int Dimensions::operator()(unsigned int w, unsigned int h) {
	this->Height = h;
	this->Width = w;
	return 0;
}