#pragma once
#include "Volume.h"
#include "Chapter.h"

ref struct VPanel : System::Windows::Forms::Panel {
public:
	Volume^ Vol;
	Chapter^ Chp;
	BOOLEAN VolChp = FALSE;
	BOOLEAN OpenClose;
	INT Index;

	System::Drawing::SizeF TextSize;
	System::Drawing::Font^ PFont;

	void GenerateGraphics() {
		switch (this->VolChp) {
		case 0: {
			System::Windows::Forms::Label^ headerTitle;
			headerTitle = gcnew System::Windows::Forms::Label;
			headerTitle->Visible = TRUE;
			headerTitle->Text = this->Vol->Name;
			headerTitle->Width = this->Width;
			headerTitle->Height = this->Height;
			System::Drawing::Graphics^ graphics = headerTitle->CreateGraphics();
			System::Drawing::Font^ tFont;
			System::Drawing::SizeF Size;

			int tw, th;
			tw = headerTitle->DisplayRectangle.Width - 3;
			th = headerTitle->DisplayRectangle.Height - 3;

			for (int idx = 1; idx <= 100; idx++) {
				tFont = gcnew System::Drawing::Font("Arial", (idx));
				Size = graphics->MeasureString(this->Vol->Name, tFont);
				if ((Size.Width > tw) || (Size.Height > th)) {
					headerTitle->Font = gcnew System::Drawing::Font("Arial", idx - 1);
					break;
				}
			}

			delete graphics;
			delete headerTitle;
			this->PFont = tFont;
			this->TextSize = Size;
			break;
		}
		case 1: {
			System::Windows::Forms::Label^ chapterTitle;
			chapterTitle = gcnew System::Windows::Forms::Label;
			chapterTitle->Visible = TRUE;
			chapterTitle->Text = this->Chp->Name;
			chapterTitle->Width = this->Width;
			chapterTitle->Height = this->Height;
			System::Drawing::Graphics^ graphics = chapterTitle->CreateGraphics();
			System::Drawing::Font^ cFont;
			System::Drawing::SizeF Size;

			for (int idx = 1; idx <= 100; idx++) {
				cFont = gcnew System::Drawing::Font("Arial", idx);
				Size = graphics->MeasureString(this->Chp->Name, cFont);
				if ((Size.Width > (chapterTitle->DisplayRectangle.Width - 3) || Size.Height > (chapterTitle->DisplayRectangle.Height - 3))) {
					chapterTitle->Font = gcnew System::Drawing::Font("Arial", idx--);
					break;
				}
			}

			delete graphics;
			delete chapterTitle;
			this->PFont = cFont;
			this->TextSize = Size;
		}
		}
	}
};