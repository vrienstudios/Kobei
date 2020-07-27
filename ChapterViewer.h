#pragma once
#include "Chapter.h"

ref class ChapterView : System::Windows::Forms::Panel {
public:
	VTable^ chapterBuffer; // index 1 is always the current, 0 is the past chapter, 2 is the future chapter.
	System::Windows::Forms::RichTextBox^ rtb;


	ChapterView();
	~ChapterView() {
		delete chapterBuffer;
	}
};