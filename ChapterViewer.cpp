#include "ChapterViewer.h"

ChapterView::ChapterView(Chapter^ chp)
{
	chapterBuffer = gcnew VTable(Chapter::typeid);
	chapterBuffer->Add(0, chp);
	chapterBuffer->Add(1, chp);
	chapterBuffer->Add(2, chp);
	rtb = gcnew System::Windows::Forms::RichTextBox;
	rtb->Font = gcnew System::Drawing::Font("Arial", 12);
	rtb->Multiline = true;
	//rtb->Dock = System::Windows::Forms::DockStyle::Fill;
	rtb->WordWrap = true;
	rtb->Text += "\n\n";
	rtb->Text += safe_cast<Chapter^>(chapterBuffer(0))->Name + "\n\n";
	rtb->Text += (safe_cast<Chapter^>(chapterBuffer(0))->Text->ToString()->Replace('\r', ' '));
	rtb->AppendText(safe_cast<Chapter^>(chapterBuffer(1))->Text->ToString()->Replace('\r', ' '));
	rtb->Height = 570;
	rtb->Width = 800;
	rtb->ReadOnly = true;
	this->Controls->Add(rtb);
	rtb->VScroll += gcnew System::EventHandler(this, &ChapterView::OnVScroll);
	//this->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &ChapterView::OnScroll);
}

void ChapterView::ExecuteEvent(ChapterView^ sender, System::EventArgs^ e, unsigned int i)
{
	switch (i) {
	case 0:
		OnOpen(sender, e);
		break;
	}
}

void ChapterView::OnScroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
{
	if (e->NewValue > rtb->Height - 5) {
		rtb->AppendText(safe_cast<Chapter^>(chapterBuffer(2))->Text->ToString()->Replace('\r', ' '));
		rtb->Height = rtb->TextLength;
	}
}


void ChapterView::OnVScroll(System::Object^ sender, System::EventArgs^ e)
{
	rtb->DeselectAll();
	this->Select();
	if ((rtb->GetPositionFromCharIndex(0).Y * -1) > rtb->TextLength / 4) {
		ExecuteEvent(this, nullptr, 0);
		rtb->AppendText(safe_cast<Chapter^>(chapterBuffer(2))->Text->ToString()->Replace('\r', ' '));
	}
}
