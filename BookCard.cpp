#include "BookCard.h"
#include "Includes.h"
#include "Window.h"

BookCard::~BookCard() {
	
}

BookCard::BookCard(Book^ book, bool coveronly)
{
	cm = gcnew System::Windows::Forms::ContextMenu();
	cm->MenuItems->Add("Open Book Parameters", gcnew System::EventHandler(this, &BookCard::OpenBook));
	cm->MenuItems->Add("Update Novel from Net", gcnew System::EventHandler(this, &BookCard::UpdateFromNetBook));
	cm->MenuItems->Add("Update ChapterList", gcnew System::EventHandler(this, &BookCard::UpdateChapterListBook));
	cm->MenuItems->Add("Delete", gcnew System::EventHandler(this, &BookCard::DeleteBook));

	this->ContextMenu = cm;

	//INIT
	AttachedBook = book;
	CoverOnly = coveronly;

	Cover = gcnew System::Windows::Forms::PictureBox;

	Cover->Image = book->Cover;
	Cover->BackColor = System::Drawing::Color::Red;
	Cover->Height = 200;
	Cover->Width = 150;

	this->Height = 200;
	this->Width = 300;
	this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

	if (coveronly == false) {
		Title = gcnew System::Windows::Forms::Label;
		Author = gcnew System::Windows::Forms::Label;
		Chapters = gcnew System::Windows::Forms::Label;
		ChaptersRead = gcnew System::Windows::Forms::Label;
		PercentageRead = gcnew System::Windows::Forms::Label;

		Title->Click += gcnew System::EventHandler(this, &BookCard::OnClick);
		Author->Click += gcnew System::EventHandler(this, &BookCard::OnClick);
		Chapters->Click += gcnew System::EventHandler(this, &BookCard::OnClick);
		ChaptersRead->Click += gcnew System::EventHandler(this, &BookCard::OnClick);
		PercentageRead->Click += gcnew System::EventHandler(this, &BookCard::OnClick);
		Cover->Click += gcnew System::EventHandler(this, &BookCard::OnClick);

		Title->Text = "Title: " + book->Title;
		if (book->Author == nullptr)
			Author->Text = "Author: null";
		else
			Author->Text = "Author: " + book->Author;

		Chapters->Text = "Chapters: " + book->CurrentChapter.ToString() + "/" + book->numChapters.ToString();

		if (book->CurrentChapter != 0) {
			ChaptersRead->Text = (book->Chapters->Length() - book->CurrentChapter).ToString();
			PercentageRead->Text = (((float)book->CurrentChapter / (float)book->numChapters) * 100).ToString() + "% Complete";
		}
		else {
			ChaptersRead->Text = "0";
			PercentageRead->Text = "0%";
		}

		Cover->Dock = System::Windows::Forms::DockStyle::Left;
		
		Title->Width = this->Width - Cover->Width;
		Title->Height = 30;
		Title->Location::set(System::Drawing::Point(Cover->Width + 5, 20));

		int tw =  Title->DisplayRectangle.Width - 3;
		int th = Title->DisplayRectangle.Height - 3;

		System::Drawing::Graphics^ graphics = Title->CreateGraphics();
		System::Drawing::Font^ tFont;
		System::Drawing::SizeF Size;
		// 1 is minimum 30 is maximum size
		for (int idx = 1; idx <= 100; idx++) {
			tFont = gcnew System::Drawing::Font("Arial", (idx));
			Size = graphics->MeasureString(book->Title, tFont);
			if ((Size.Width > tw) || (Size.Height > th)) {
				Title->Font = gcnew System::Drawing::Font("Arial", idx - 1);
				break;
			}
		}

		Author->Height = 20;
		Author->Width = Title->Width;
		 
		tw = Author->DisplayRectangle.Width - 3;
		th = Author->DisplayRectangle.Height - 3;

		for (int idx = 1; idx <= 100; idx++) {
			tFont = gcnew System::Drawing::Font("Arial", (idx));
			Size = graphics->MeasureString(book->Author, tFont);
			if ((Size.Width > tw) || (Size.Height > th)) {
				Author->Font = gcnew System::Drawing::Font("Arial", idx - 1);
				break;
			}
		}
		Author->Location::set(System::Drawing::Point(Title->Location.X, Title->Location.Y + (Title->Height / 2 ) + Author->Height));

		Chapters->Height = 20;
		Chapters->Width = Title->Width;

		tw = Chapters->DisplayRectangle.Width - 3;
		th = Chapters->DisplayRectangle.Height - 3;

		for (int idx = 1; idx <= 100; idx++) {
			tFont = gcnew System::Drawing::Font("Arial", (idx));
			Size = graphics->MeasureString(book->Chapters->Length().ToString(), tFont);
			if ((Size.Width > tw) || (Size.Height > th)) {
				Chapters->Font = gcnew System::Drawing::Font("Arial", idx - 1);
				break;
			}
		}
		Chapters->Location::set(System::Drawing::Point(Title->Location.X, Author->Location.Y + Chapters->Height));
		//ChaptersRead->Location::set(System::Drawing::Point(170, 55));
		PercentageRead->Width = 150;

		PercentageRead->Height = 20;
		PercentageRead->Width = Title->Width;

		tw = PercentageRead->DisplayRectangle.Width - 3;
		th = PercentageRead->DisplayRectangle.Height - 3;

		for (int idx = 1; idx <= 100; idx++) {
			tFont = gcnew System::Drawing::Font("Arial", (idx));
			Size = graphics->MeasureString(book->ReadPercentage.ToString(), tFont);
			if ((Size.Width > tw) || (Size.Height > th)) {
				PercentageRead->Font = gcnew System::Drawing::Font("Arial", idx - 1);
				break;
			}
		}
		PercentageRead->Location::set(System::Drawing::Point(Title->Location.X, Chapters->Location.Y + PercentageRead->Height));

		this->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{Cover, Title, Author, Chapters, PercentageRead});
	}
	else {
		this->Width = Cover->Width;
		this->Height = Cover->Height;
	}
}

void BookCard::OpenBook(System::Object^ sender, System::EventArgs^ e)
{
	openFlag::set(FALSE);
}

void BookCard::DeleteBook(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox(NULL, "This method is not yet implemented! Please be patient.", "Kobei: Book", MB_ICONEXCLAMATION);
	deleteFlag::set(FALSE);
}

void BookCard::UpdateFromNetBook(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox(NULL, "This method is not yet implemented! Please be patient.", "Kobei: Book", MB_ICONEXCLAMATION);
	updateNFlag::set(FALSE);
}

void BookCard::UpdateChapterListBook(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox(NULL, "This method is not yet implemented! Please be patient.", "Kobei: Book", MB_ICONEXCLAMATION);
	updateCLFlag::set(FALSE);
}

void BookCard::openFire(System::Object^ sender, System::EventArgs^ e, unsigned int i)
{
	switch (i) {
	case 0:
		OnOpen(sender, e);
		break;
	case 1:
		OnUpdateNClick(sender, e);
		break;
	case 2:
		OnDelete(sender, e);
		break;
	case 3:
		OnUpdateCLClick(sender, e);
		break;
	}
}

void BookCard::OnClick(System::Object^ sender, System::EventArgs^ e)
{
	CardClick();
}
