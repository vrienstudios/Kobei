#pragma once
#include "VTable.h"
#include "Book.h"

ref class Volume {
public:
	Volume();

	Book^ attachedBook;
	System::String^ Name;
	VTable^ ChapterList;

	void ParseVolume(System::String^ directory);
};