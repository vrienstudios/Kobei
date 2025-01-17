#pragma once
#include "Chapter.h"
#include "Volume.h"

ref class ChapterView : System::Windows::Forms::Panel {
public:
	VTable^ chapterBuffer; // index 1 is always the current, 0 is the past chapter, 2 is the future chapter.
	Volume^ selectedVolume;
	System::Windows::Forms::RichTextBox^ rtb;
	System::Windows::Forms::RichTextBox^ rtb0;
	System::Windows::Forms::RichTextBox^ rtb1;
	int inde = 0;

	ChapterView(Chapter^ chp);
	~ChapterView() {
		delete chapterBuffer;
	}

	delegate void EventHandler(ChapterView^& sender, System::EventArgs^ e);
	virtual void ExecuteEvent(ChapterView^ sender, System::EventArgs^ e, unsigned int i);
	event EventHandler^ OnOpen;

	property bool openFlag {
		void set(bool value) {
			ExecuteEvent(this, System::EventArgs::Empty, 0);
		}
	};
	void OnScroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e);
	void OnVScroll(System::Object^ sender, System::EventArgs^ e);
};