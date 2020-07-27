#include "VolumeCollapsible.h"
#include "Vpanel.h"

// Generate a volumeCollapsible object via VTable Dict
VolumeCollapsible::VolumeCollapsible(VTable^ volumeList)
{
	if (volumeList->Length() == 0) {
		std::exception("Error occurred");
		std::cout << "ER" << std::endl;
	}
	Volumes = volumeList;
	CollapsibleControls = gcnew VTable(System::Windows::Forms::Panel::typeid);

	this->AutoScroll = TRUE;
	this->Visible = true;
	std::cout << "ER" << std::endl; std::cout << "ER" << std::endl;
	GenerateControls();
}

// Generate a volumeCollapsible object via standard .NET array.
VolumeCollapsible::VolumeCollapsible(cli::array<Volume^>^ volumeList)
{
	if (volumeList->Length == 0)
		std::exception("Error occurred");
	Volumes = gcnew VTable(Volume::typeid);
	CollapsibleControls = gcnew VTable(System::Windows::Forms::Panel::typeid);

	for (unsigned int idx = 0; idx < volumeList->Length; idx++) {
		Volumes->Add(idx, volumeList[idx]);
	}

	this->AutoScroll = TRUE;

	GenerateControls();
}

void VolumeCollapsible::GenerateControls()
{
	VPanel^ header;
	System::Windows::Forms::Label^ headerTitle;
	System::Windows::Forms::Panel^ list;
	//this->BackColor = System::Drawing::Color::Orange;
	this->DoubleBuffered = TRUE;
	System::Windows::Forms::ScrollBar^ vScroll = gcnew System::Windows::Forms::VScrollBar();
	//vScroll->Dock = System::Windows::Forms::DockStyle::Right;
	//vScroll->AutoScrollOffset = System::Drawing::Point(0, 1000);
	//vScroll->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &VolumeCollapsible::OnScroll);
	//this->Controls->Add(vScroll);
	this->AutoScroll = FALSE;
	this->HorizontalScroll->Maximum = 0;
	this->HorizontalScroll->Visible = FALSE;
	//this->AutoScrollMinSize = System::Drawing::Size(0, 1000);
	this->AutoScroll = TRUE;
	int hbufferH = 0, hbufferW = 0, hbufferY = 0, cbufferH = 0,	cbufferW = 0, cbufferY = 0;
	int indexCount = 0;
	for (unsigned int idx = Volumes->Length(); idx > 0; idx--) {
		Volume^ Vol = safe_cast<Volume^>(Volumes(idx - 1, TRUE));

		header = gcnew VPanel;
		header->Width = this->Width;
		header->BackColor = System::Drawing::Color::Teal;
		header->Height = 100;
		//header->AutoScroll = TRUE;
		header->Vol = Vol;
		header->VolChp = FALSE;
		header->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VolumeCollapsible::OnPaint);
		header->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &VolumeCollapsible::OnMouseClick);
		header->OpenClose = FALSE;
		header->Index = indexCount;
		indexCount += 2;
		header->GenerateGraphics();
		header->Location = System::Drawing::Point(hbufferW, hbufferH);
		hbufferH += header->Height + 5;
		list = gcnew System::Windows::Forms::Panel;
		list->Width = this->Width;
		list->Location = System::Drawing::Point(0, header->Location.Y + header->Height);
		list->Height = 100;
		/*list->AutoScroll = FALSE;
		list->HorizontalScroll->Maximum = 0;
		list->VerticalScroll->Maximum = 0;
		list->BackColor = System::Drawing::Color::Red;
		list->HorizontalScroll->Visible = FALSE;
		list->VerticalScroll->Visible = FALSE;
		//this->AutoScrollMinSize = System::Drawing::Size(0, 1000);
		list->AutoScroll = TRUE;*/
		list->Visible = FALSE;
		//ShowScrollBar((HWND)list->Handle.ToInt32(), 3, FALSE); - Doesn't work
		for (unsigned int i = 0; i < Vol->ChapterList->Length(); i++) {
			VPanel^ chpCard = gcnew VPanel;
			chpCard->VolChp = TRUE;
			Chapter^ Chp = safe_cast<Chapter^>(Vol->ChapterList(i, TRUE));

			chpCard->Width = this->Width;
			chpCard->BackColor = System::Drawing::Color::Orange;
			chpCard->Height = 100;
			chpCard->Width = list->Width;
			chpCard->VolChp = TRUE;
			chpCard->Chp = Chp;
			chpCard->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VolumeCollapsible::OnPaint);
			//chpCard->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VolumeCollapsible::OnPaint);
			chpCard->Location::set(System::Drawing::Point(0, cbufferY));
			cbufferY += chpCard->Height + 5;
			chpCard->GenerateGraphics();
			list->Controls->Add(chpCard);
		}
		list->Height = (cbufferY);
		cbufferY = 0;
		this->Controls->Add(header);
		this->Controls->Add(list);
	}
	//this->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{header, list});
}

void VolumeCollapsible::AnimateClose(VPanel^& panel)
{
	System::Windows::Forms::Panel^ chapterList = safe_cast<System::Windows::Forms::Panel^>(this->Controls[panel->Index + 1]);
	//this->Controls[panel->Index + 2]->Visible = FALSE;
	chapterList->Visible = FALSE;
	for (int idx = this->Controls->Count - 1; idx > panel->Index + 1; idx--)
		this->Controls[idx]->Location = System::Drawing::Point(0, this->Controls[idx]->Location.Y - chapterList->Height);
}

void VolumeCollapsible::AnimateOpen(VPanel^& panel)
{
	System::Windows::Forms::Panel^ chapterList = safe_cast<System::Windows::Forms::Panel^>(this->Controls[panel->Index + 1]);
	//this->Controls[panel->Index + 2]->Visible = FALSE;
	chapterList->Visible = TRUE;
	for (int idx = panel->Index + 2; idx < this->Controls->Count; idx++)
		this->Controls[idx]->Location = System::Drawing::Point(0, this->Controls[idx]->Location.Y + chapterList->Height);
}

void VolumeCollapsible::OnPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	VPanel^ Vpan = safe_cast<VPanel^>(sender);
	switch (Vpan->VolChp) {
	case 0: {
		System::Drawing::RectangleF rect = System::Drawing::RectangleF(0, 20, Vpan->Width, Vpan->Height);
		System::Drawing::Graphics^ graphics = e->Graphics;
		System::Drawing::StringFormat^ strfm = gcnew System::Drawing::StringFormat();
		strfm->Trimming = System::Drawing::StringTrimming::None;
		strfm->LineAlignment = System::Drawing::StringAlignment::Center;
		strfm->FormatFlags = System::Drawing::StringFormatFlags::NoWrap | System::Drawing::StringFormatFlags::NoClip;
		System::Console::WriteLine(Vpan->Vol->Name);
		graphics->DrawString(Vpan->Vol->Name, Vpan->PFont, gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rect, strfm);
		delete graphics;
		delete strfm;
		break;
	}
	case 1: {
		System::Drawing::RectangleF rect = System::Drawing::RectangleF(0, 20, Vpan->Width, Vpan->Height);
		System::Drawing::Graphics^ graphics = e->Graphics;
		System::Drawing::StringFormat^ strfm = gcnew System::Drawing::StringFormat();
		strfm->Trimming = System::Drawing::StringTrimming::None;
		strfm->LineAlignment = System::Drawing::StringAlignment::Center;
		strfm->FormatFlags = System::Drawing::StringFormatFlags::NoWrap | System::Drawing::StringFormatFlags::NoClip;
		graphics->DrawString(Vpan->Chp->Name, Vpan->PFont, gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rect, strfm);
		delete graphics;
		delete strfm;
	}
	}
}


void VolumeCollapsible::OnScroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
{
	this->VerticalScroll->Value = safe_cast<System::Windows::Forms::VScrollBar^>(sender)->Value;
}


void VolumeCollapsible::OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	VPanel^ vp = safe_cast<VPanel^>(sender);
	switch (vp->OpenClose) {
	case 0:
		AnimateOpen(vp);
		vp->OpenClose = TRUE;
		break;
	case 1:
		vp->OpenClose = FALSE;
		AnimateClose(vp);
		break;
	}
}
