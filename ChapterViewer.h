#pragma once
#include "Chapter.h"

ref class ChapterView : System::Windows::Forms::Panel {
public:
	VTable^ chapterBuffer; // index 1 is always the current, 0 is the past chapter, 2 is the future chapter.
	System::Windows::Forms::RichTextBox^ rtb;


	ChapterView(Chapter^ chp);
	~ChapterView() {
		delete chapterBuffer;
	}

	delegate void EventHandler(System::Object^ sender, System::EventArgs^ e);
	virtual void ExecuteEvent(System::Object^ sender, System::EventArgs^ e, unsigned int i);
	event EventHandler^ OnOpen;

	property bool openFlag {
		void set(bool value) {
			ExecuteEvent(this, System::EventArgs::Empty, 0);
		}
	};
};