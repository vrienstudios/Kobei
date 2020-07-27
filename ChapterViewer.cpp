#include "ChapterViewer.h"

ChapterView::ChapterView()
{
	chapterBuffer = gcnew VTable(Chapter::typeid);
	rtb = gcnew System::Windows::Forms::RichTextBox;
	rtb->Dock = System::Windows::Forms::DockStyle::Fill;
}