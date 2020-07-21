#include "VolumeCollapsible.h"
#include "Vpanel.h"

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
		indexCount++;
		header->Location = System::Drawing::Point(hbufferW, hbufferH);
		hbufferH += header->Height + 5;

		list = gcnew System::Windows::Forms::Panel;
		list->Width = this->Width;
		list->Height = 300;
		list->Location = System::Drawing::Point(0, header->Location.Y + 10);
		indexCount++;
		list->AutoScroll = FALSE;
		list->HorizontalScroll->Maximum = 0;
		list->BackColor = System::Drawing::Color::Red;
		list->HorizontalScroll->Visible = FALSE;
		//this->AutoScrollMinSize = System::Drawing::Size(0, 1000);
		list->AutoScroll = TRUE;
		list->Visible = FALSE;
		cbufferY = list->Location.Y;
		for (unsigned int i = 0; i < Vol->ChapterList->Length(); i++) {
			VPanel^ chpCard = gcnew VPanel;
			chpCard->VolChp = TRUE;
			Chapter^ Chp = safe_cast<Chapter^>(Vol->ChapterList(i, TRUE));
			std::cout << msclr::interop::marshal_as<std::string>(Chp->Text->ToString());

			chpCard->Width = this->Width;
			chpCard->BackColor = System::Drawing::Color::Orange;
			chpCard->Height = 100;
			chpCard->Width = list->Width;
			chpCard->VolChp = TRUE;
			chpCard->Chp = Chp;
			//chpCard->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &VolumeCollapsible::OnPaint);

			chpCard->Location::set(System::Drawing::Point(0, cbufferY));
			cbufferY += chpCard->Height + 5;

			list->Controls->Add(chpCard);
		}
		this->Controls->Add(header);
		this->Controls->Add(list);
	}
	//this->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{header, list});
}

void VolumeCollapsible::AnimateClose()
{
	throw gcnew System::NotImplementedException();
}

void VolumeCollapsible::AnimateOpen(VPanel^& panel)
{
	System::Windows::Forms::Panel^ chapterList = safe_cast<System::Windows::Forms::Panel^>(this->Controls[panel->Index + 1]);
	//this->Controls[panel->Index + 2]->Visible = FALSE;
	chapterList->Visible = TRUE;
}

void VolumeCollapsible::OnPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
{
	VPanel^ Vpan = safe_cast<VPanel^>(sender);
	switch (Vpan->VolChp) {
	case 0: {
		System::Windows::Forms::Label^ headerTitle;
		headerTitle = gcnew System::Windows::Forms::Label;
		headerTitle->Visible = TRUE;
		headerTitle->Text = Vpan->Vol->Name;
		headerTitle->Width = Vpan->Width;
		headerTitle->Height = Vpan->Height;
		System::Drawing::Graphics^ graphics = headerTitle->CreateGraphics();
		System::Drawing::Font^ tFont;
		System::Drawing::SizeF Size;

		int tw, th;
		tw = headerTitle->DisplayRectangle.Width - 3;
		th = headerTitle->DisplayRectangle.Height - 3;

		for (int idx = 1; idx <= 100; idx++) {
			tFont = gcnew System::Drawing::Font("Arial", (idx));
			Size = graphics->MeasureString(Vpan->Vol->Name, tFont);
			if ((Size.Width > tw) || (Size.Height > th)) {
				headerTitle->Font = gcnew System::Drawing::Font("Arial", idx - 1);
				break;
			}
		}

		delete graphics;
		System::Drawing::RectangleF rect = System::Drawing::RectangleF(0, 20, Vpan->Width, Vpan->Height);
		graphics = e->Graphics;
		System::Drawing::StringFormat^ strfm = gcnew System::Drawing::StringFormat();
		graphics->DrawString(headerTitle->Text, headerTitle->Font, gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), rect, strfm);
		//delete Vpan;
		delete headerTitle;
		break;
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
	AnimateOpen(vp);
}
