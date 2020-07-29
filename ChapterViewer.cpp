#include "ChapterViewer.h"

ChapterView::ChapterView(Chapter^ chp)
{
	chapterBuffer = gcnew VTable(Chapter::typeid);
	chapterBuffer->Add(0, chp);
	chapterBuffer->Add(1, chp);
	chapterBuffer->Add(2, chp);
	rtb = gcnew System::Windows::Forms::RichTextBox;
	rtb->Multiline = true;
	rtb->Dock = System::Windows::Forms::DockStyle::Fill;
	rtb->Text += "\n\n";
	rtb->Text += safe_cast<Chapter^>(chapterBuffer(1))->Name + "\n\n";
	rtb->AppendText(safe_cast<Chapter^>(chapterBuffer(1))->Text);
	this->Controls->Add(rtb);
}

void ChapterView::ExecuteEvent(ChapterView^ sender, System::EventArgs^ e, unsigned int i)
{
	switch (i) {
	case 0:
		OnOpen(sender, e);
		break;
	}
}