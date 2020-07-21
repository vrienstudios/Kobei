#pragma once
#include "VTable.h"
#include "Volume.h"

ref class Chapter {
public:
	System::String^ Name;
	System::String^ Text;
	System::String^ Uri;

	Volume^ attachedVolume;

	int Number;

	VTable^ TextAnnotation;
};