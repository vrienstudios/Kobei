#include "Window.h"
#include "Preferences.h"
#include "BookCard.h"
#include "Page.h"
#include "Dashboard.h"
#include "panel.h"
#include "BookAddForm.h"
#include "CreditsForm.h"
#include "VolumeCollapsible.h"
#include <thread>
#include "ResourceHandler.h"

Window::Window(unsigned int w, unsigned int h) : Form(gcnew System::Windows::Forms::Form) {
	windowDimension->operator()(w, h);
	Create();
}

Window::Window(void) : Form(gcnew System::Windows::Forms::Form) {
	windowDimension->operator()(500, 500);
	Create();
}

Window::~Window() {
	delete Form;

	// Pages
	delete addBookPage;
	delete bookListPage;
	delete bookViewPage;
	delete homePage;
	delete emailSupportPage;
	delete aboutPage;

	//Pointers
	delete windowDimension;
}

// Initialize everything and general setup. Main Window
int Window::PageGeneration() {
	Form->SuspendLayout();
	
	Resources::LoadResourceSystem();

	toolStripDropDownButton1 = gcnew System::Windows::Forms::ToolStripDropDownButton();
	importKTFBookToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	exportAsKTFBookToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	exportAsEBookToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	toolStripProgressBar1 = gcnew System::Windows::Forms::ToolStripProgressBar();
	toolStripLabel1 = gcnew System::Windows::Forms::ToolStripLabel();
	toolStrip1 = gcnew System::Windows::Forms::ToolStrip();
	toolStripDropDownButton2 = gcnew System::Windows::Forms::ToolStripDropDownButton();
	addBookToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	fromUriToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	fromFolderToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	autoExportAsEbookToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	toolStripDropDownButton3 = gcnew System::Windows::Forms::ToolStripDropDownButton();
	audioToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	accessibilityToolStripMenuItem = gcnew System::Windows::Forms::ToolStripMenuItem();
	toolStripButton1 = gcnew System::Windows::Forms::ToolStripButton();
	toolStrip1->SuspendLayout();
	toolStripDropDownButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
	toolStripDropDownButton1->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
	importKTFBookToolStripMenuItem,
	exportAsKTFBookToolStripMenuItem,
	exportAsEBookToolStripMenuItem });
	//toolStripDropDownButton1->Image = ((System::Drawing::Image^)(resources::GetObject("toolStripDropDownButton1::Image")));
	toolStripDropDownButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
	toolStripDropDownButton1->Name = "toolStripDropDownButton1";
	toolStripDropDownButton1->Size = System::Drawing::Size(38, 22);
	toolStripDropDownButton1->Text = "File";
	toolStripDropDownButton1->ToolTipText = "File";
	importKTFBookToolStripMenuItem->Name = "importKTFBookToolStripMenuItem";
	importKTFBookToolStripMenuItem->Size::set(System::Drawing::Size(180, 22));
	importKTFBookToolStripMenuItem->Text = "Import KTF Book";
	exportAsKTFBookToolStripMenuItem->Name = "exportAsKTFBookToolStripMenuItem";
	exportAsKTFBookToolStripMenuItem->Size::set(System::Drawing::Size(180, 22));
	exportAsKTFBookToolStripMenuItem->Text = "Export as KTF Book";
	exportAsEBookToolStripMenuItem->Name = "exportAsEBookToolStripMenuItem";
	exportAsEBookToolStripMenuItem->Size::set(System::Drawing::Size(180, 22));
	exportAsEBookToolStripMenuItem->Text = "Export as eBook";
	toolStripProgressBar1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
	toolStripProgressBar1->Name = "toolStripProgressBar1";
	toolStripProgressBar1->Size = System::Drawing::Size(150, 22);
	toolStripLabel1->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
	toolStripLabel1->Name = "toolStripLabel1";
	toolStripLabel1->Size = System::Drawing::Size(56, 22);
	toolStripLabel1->Text = "Standby :";
	toolStrip1->Items->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
	toolStripDropDownButton1,
	toolStripDropDownButton2,
	toolStripProgressBar1,
	toolStripLabel1,
	toolStripDropDownButton3,
	toolStripButton1});
	toolStrip1->Location = System::Drawing::Point(0, 0);
	toolStrip1->Name = "toolStrip1";
	toolStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::Professional;
	toolStrip1->Size = System::Drawing::Size(784, 25);
	toolStrip1->TabIndex = 0;
	toolStrip1->Text = "toolStrip1";
	toolStripDropDownButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
	toolStripDropDownButton2->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
	addBookToolStripMenuItem,
	autoExportAsEbookToolStripMenuItem });
	//toolStripDropDownButton2->Image = ((System::Drawing::Image^)(resources::GetObject("toolStripDropDownButton2::Image")));
	toolStripDropDownButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
	toolStripDropDownButton2->Name = "toolStripDropDownButton2";
	toolStripDropDownButton2->Size = System::Drawing::Size(47, 22);
	toolStripDropDownButton2->Text = "Book";
	addBookToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
	fromUriToolStripMenuItem,
	fromFolderToolStripMenuItem });
	addBookToolStripMenuItem->Name = "addBookToolStripMenuItem";
	addBookToolStripMenuItem->Size = System::Drawing::Size(186, 22);
	addBookToolStripMenuItem->Text = "Add Book";
	fromUriToolStripMenuItem->Name = "fromUriToolStripMenuItem";
	fromUriToolStripMenuItem->Size = System::Drawing::Size(180, 22);
	fromUriToolStripMenuItem->Text = "From Uri";
	fromUriToolStripMenuItem->Click += gcnew System::EventHandler(this, &Window::FromUriClick);
	fromFolderToolStripMenuItem->Name = "fromFolderToolStripMenuItem";
	fromFolderToolStripMenuItem->Size = System::Drawing::Size(180, 22);
	fromFolderToolStripMenuItem->Text = "From Folder";
	autoExportAsEbookToolStripMenuItem->Name = "autoExportAsEbookToolStripMenuItem";
	autoExportAsEbookToolStripMenuItem->Size = System::Drawing::Size(186, 22);
	autoExportAsEbookToolStripMenuItem->Text = "Auto Export as Ebook";
	toolStripDropDownButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
	toolStripDropDownButton3->DropDownItems->AddRange(gcnew cli::array<System::Windows::Forms::ToolStripItem^>{
	audioToolStripMenuItem,
	accessibilityToolStripMenuItem });
	//toolStripDropDownButton3->Image = ((System::Drawing::Image)(resources::GetObject("toolStripDropDownButton3::Image")));
	toolStripDropDownButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
	toolStripDropDownButton3->Name = "toolStripDropDownButton3";
	toolStripDropDownButton3->Size = System::Drawing::Size(62, 22);
	toolStripDropDownButton3->Text = "Settings";
	toolStripDropDownButton3->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
	audioToolStripMenuItem->Name = "audioToolStripMenuItem";
	audioToolStripMenuItem->Size = System::Drawing::Size(180, 22);
	audioToolStripMenuItem->Text = "Audio";
	accessibilityToolStripMenuItem->Name = "accessibilityToolStripMenuItem";
	accessibilityToolStripMenuItem->Size = System::Drawing::Size(180, 22);
	accessibilityToolStripMenuItem->Text = "Accessibility";
	toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
	//toolStripButton1->Image = ((System::Drawing::Image)(resources::GetObject("toolStripButton1::Image")));
	toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
	toolStripButton1->Name = "toolStripButton1";
	toolStripButton1->Size = System::Drawing::Size(48, 22);
	toolStripButton1->Text = "Credits";
	toolStrip1->ResumeLayout(false);
	toolStrip1->PerformLayout();

	tabControl = gcnew System::Windows::Forms::TabControl;
	tabControl->Width = windowDimension->Width;
	tabControl->Height = windowDimension->Height;
	tabControl->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
	tabControl->ItemSize = System::Drawing::Size(0, 1);
	tabControl->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
	//tabControl->BackColor = System::Drawing::Color::Red;
	tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &Window::OnSelectedIndexChanged);
	tabControl->BackColor = System::Drawing::Color::Red;
	tabControl->Dock = System::Windows::Forms::DockStyle::Fill;

	Main = gcnew System::Windows::Forms::Panel;
	Main->Dock = System::Windows::Forms::DockStyle::Fill;
	Main->Width = windowDimension->Width;
	Main->Height = windowDimension->Height;

	ShowSideBar = gcnew tPanel;
	ShowSideBar->Anchor = System::Windows::Forms::AnchorStyles::Left;
	ShowSideBar->Width = 50;
	//ShowSideBar->BackColor = System::Drawing::Color::FromArgb(20, 88, 44, 55);
	ShowSideBar->Height = windowDimension->Height;
	ShowSideBar->MouseEnter += gcnew System::EventHandler(this, &Window::ShowSideBarMouseEnter);

	SideBar = gcnew System::Windows::Forms::Panel;
	SideBar->Anchor = System::Windows::Forms::AnchorStyles::Left;
	SideBar->Width = 80;
	SideBar->Height = windowDimension->Height;
	SideBar->Visible = false;
	SideBar->MouseLeave += gcnew System::EventHandler(this, &Window::SideBarLeave);

	toolStripButton1->Click += gcnew System::EventHandler(this, &Window::ShowCredits);
	HomePageGeneration();
	tabControl->TabPages->Add(homePage);
	AddPageGeneration();
	tabControl->TabPages->Add(addBookPage);
	BookListPageGeneration();
	tabControl->TabPages->Add(bookListPage);
	BookViewPageGeneration();
	tabControl->TabPages->Add(bookViewPage);
	EmailSupportPageGeneration();
	tabControl->TabPages->Add(emailSupportPage);
	AboutPageGeneration();
	tabControl->TabPages->Add(aboutPage);
	ChaperPageGeneration();
	tabControl->TabPages->Add(chapterDetailView);

	Form->Controls->Add(toolStrip1);
	Form->Controls->Add(SideBar);
	Form->Controls->Add(ShowSideBar);
	Form->Controls->Add(tabControl);
	tabControl->SelectedIndex = 0;

	Form->ResumeLayout(false);
	return 0;
}

int Window::HomePageGeneration() {
	bool lastreadTrue = false;
	if (homePage == nullptr)
		homePage = gcnew System::Windows::Forms::TabPage;
	else if (homePage->InvokeRequired) {
		ClearControls^ delCon = gcnew ClearControls(this, &Window::ClearHomePageControls);
		homePage->Invoke(delCon);
		delete delCon;
	}
	else {
		homePage->Controls->Clear();
	}
	if (homePage->InvokeRequired) {
		SetSelectedIndex^ selInd = gcnew SetSelectedIndex(this, &Window::SetHomePageTabPageIndex);
		homePage->Invoke(selInd, 0);
		delete selInd;
		SetDock^ setDock = gcnew SetDock(this, &Window::SetHomePageDockStyle);
		homePage->Invoke(setDock, System::Windows::Forms::DockStyle::Fill);
		delete setDock;

		//TODO: Finsh invocation usage.
		int tLength = 80;
		int tYSET = 20; // initial offset
		System::Windows::Forms::PictureBox^ err;
		switch (BookTable->Length() > 0) {
		case 0: {
			err = gcnew System::Windows::Forms::PictureBox;
			err->Dock = System::Windows::Forms::DockStyle::Fill;
			err->Image = System::Drawing::Bitmap::FromStream(Resources::GetObject("error_NoNovels.png"));
			err->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			err->Click += gcnew System::EventHandler(this, &Window::BookAddOnClick);
			homePage->Controls->Add(err);
			System::Windows::Forms::Button^ AddBtn = gcnew System::Windows::Forms::Button;
			AddBtn->Click += gcnew System::EventHandler(this, &Window::BookAddOnClick);
			AddBtn->Text = "Add Book";
			AddBtn->Width = windowDimension->Width;
			AddBtn->Height = 100;
			AddBtn->Location = System::Drawing::Point(((windowDimension->Width - AddBtn->Width) / 2) - 10, ((windowDimension->Height - AddBtn->Height) / 2));
			AddBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;

			System::Windows::Forms::Panel^ UpdateBox = gcnew System::Windows::Forms::Panel;
			System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox;
			pic->Image = System::Drawing::Bitmap::FromStream(Resources::GetObject("SupportedSites.png"));
			pic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			pic->Dock = System::Windows::Forms::DockStyle::Fill;
			UpdateBox->Controls->Add(pic);
			UpdateBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			UpdateBox->Height = 150;
			homePage->Controls->Add(UpdateBox);
			break;
		}
		case 1: {
			for (unsigned int idx = 0; idx < BookTable->Length(); idx++)
			{
				BookCard^ bc = gcnew BookCard(safe_cast<Book^>(BookTable(idx, true)), false);
				bc->bookIndex = idx;

				if (idx == 0) {
					bc->Location = System::Drawing::Point(tLength, tYSET);
				}
				else {
					tLength += bc->Width + 5;

					if (tLength > Form->Width - bc->Width) {
						tLength = 80;
						tYSET += bc->Height + 5;
					}

					bc->Location = System::Drawing::Point(tLength, tYSET);
				}

				bc->OnOpen += gcnew BookCard::OpenHandler(this, &Window::OnOpen);
				bc->OnUpdateCLClick += gcnew BookCard::OpenHandler(this, &Window::OnUpdateCLClick);
				bc->OnCardClick += gcnew BookCard::CardHandler(this, &Window::CardClick);
				homePage->Controls->Add(bc);
			}
			break;
		}
		}
	}
	else {
		int tLength = 80;
		int tYSET = 20; // initial offset
		System::Windows::Forms::PictureBox^ err;
		switch (BookTable->Length() > 0) {
		case 0: {
			err = gcnew System::Windows::Forms::PictureBox;
			err->Dock = System::Windows::Forms::DockStyle::Fill;
			err->Image = System::Drawing::Bitmap::FromStream(Resources::GetObject("error_NoNovels.png"));
			err->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			err->Click += gcnew System::EventHandler(this, &Window::BookAddOnClick);
			homePage->Controls->Add(err);
			System::Windows::Forms::Button^ AddBtn = gcnew System::Windows::Forms::Button;
			AddBtn->Click += gcnew System::EventHandler(this, &Window::BookAddOnClick);
			AddBtn->Text = "Add Book";
			AddBtn->Width = windowDimension->Width;
			AddBtn->Height = 100;
			AddBtn->Location = System::Drawing::Point(((windowDimension->Width - AddBtn->Width) / 2) - 10, ((windowDimension->Height - AddBtn->Height) / 2));
			AddBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;

			System::Windows::Forms::Panel^ UpdateBox = gcnew System::Windows::Forms::Panel;
			System::Windows::Forms::PictureBox^ pic = gcnew System::Windows::Forms::PictureBox;
			pic->Image = System::Drawing::Bitmap::FromStream(Resources::GetObject("SupportedSites.png"));
			pic->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			pic->Dock = System::Windows::Forms::DockStyle::Fill;
			UpdateBox->Controls->Add(pic);
			UpdateBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			UpdateBox->Height = 150;
			homePage->Controls->Add(UpdateBox);
			break;
		}
		case 1: {
			for (unsigned int idx = 0; idx < BookTable->Length(); idx++)
			{
				BookCard^ bc = gcnew BookCard(safe_cast<Book^>(BookTable(idx, true)), false);
				bc->bookIndex = idx;

				if (idx == 0) {
					bc->Location = System::Drawing::Point(tLength, tYSET);
				}
				else {
					tLength += bc->Width + 5;

					if (tLength > Form->Width - bc->Width) {
						tLength = 80;
						tYSET += bc->Height + 5;
					}

					bc->Location = System::Drawing::Point(tLength, tYSET);
				}

				bc->OnOpen += gcnew BookCard::OpenHandler(this, &Window::OnOpen);
				bc->OnUpdateCLClick += gcnew BookCard::OpenHandler(this, &Window::OnUpdateCLClick);
				bc->OnCardClick += gcnew BookCard::CardHandler(this, &Window::CardClick);
				homePage->Controls->Add(bc);
			}
			break;
		}
		}
	}
	//homePage->BackColor = System::Drawing::Color::Red;
	homePage->TabIndex = 0;
	/*try {
		Book^ LastRead = safe_cast<Book^>(BookTable(0, true));
		BookCard^ BkCard = gcnew BookCard(LastRead, false);
		BkCard->Location::set(System::Drawing::Point(0, 0));
		homePage->Controls->Add(BkCard);

		lastreadTrue = true;
	}
	catch (...) {

	}*/
	return 0;
}

int Window::AddPageGeneration() {
	addBookPage = gcnew System::Windows::Forms::TabPage;
	addBookPage->TabIndex = 1;

	return -1;
}

int Window::BookListPageGeneration() {
	bookListPage = gcnew System::Windows::Forms::TabPage;
	bookListPage->TabIndex = 2;

	return -1;
}

int Window::BookViewPageGeneration() {
	bookViewPage = gcnew System::Windows::Forms::TabPage;
	bookViewPage->TabIndex = 3;
	bookViewPage->Dock = System::Windows::Forms::DockStyle::Fill;
	bookViewPage->BackColor = System::Drawing::Color::Red;
	//System::Windows::Forms::PictureBox^ pcb = gcnew System::Windows::Forms::PictureBox;
	
	//System::Windows::Forms::RichTextBox^ rtb = gcnew System::Windows::Forms::RichTextBox;
	//rtb->Dock = System::Windows::Forms::DockStyle::Fill;

	//bookViewPage->Controls->Add(rtb);
	

	return -1;
}

int Window::EmailSupportPageGeneration() {
	emailSupportPage = gcnew System::Windows::Forms::TabPage;
	emailSupportPage->TabIndex = 4;

	return -1;
}

int Window::AboutPageGeneration() {
	aboutPage = gcnew System::Windows::Forms::TabPage;
	aboutPage->TabIndex = 5;

	return -1;
}

int Window::ChaperPageGeneration()
{
	if (currentChapter == nullptr) {
		chapterDetailView = gcnew System::Windows::Forms::TabPage;
		chapterDetailView->TabIndex = 6;
		return -1;
	}
	else
		chapterDetailView->Controls->Clear();

	chapterDetailView->BackColor = System::Drawing::Color::Red;
	chapterDetailView->Dock = System::Windows::Forms::DockStyle::Fill;
	ChapterView^ chapviewer = gcnew ChapterView(currentChapter);
	chapviewer->Dock = System::Windows::Forms::DockStyle::Fill;
	chapterDetailView->Controls->Add(chapviewer);
	return 0;
}

int Window::Create() {
	BookTable = gcnew VTable(Book::typeid);

	//Form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	Form->Width = windowDimension->Width;
	Form->Height = windowDimension->Height;

	LoadBooks();
	PageGeneration();

	return 0;
}

int Window::LoadBooks() {
	System::String^ BookDirectory = GetBookDirectory();

	//Can't load books without a book directory.
	if (BookDirectory == "NULL")
		return -1;

	cli::array<System::String^>^ Books = System::IO::Directory::GetDirectories(BookDirectory);
	for (int idx = 0; idx < Books->Length; idx++) {
		Book^ Bk;
		Bk = Book::ParseBook(Books[idx]);

		BookTable->Add(idx, Bk);
	}

	return 0;
}

System::String^ Window::GetBookDirectory() {

	//Check whether preferenced exist or not.
	System::String^ s1 = gcnew System::String(std::string("C:\\Program Files (x86)\\Kobei\\settings.txt").c_str());
	if (!System::IO::File::Exists(s1))
	{
		switch (MessageBox(NULL, "Preferences file not found!\nWould you allow me to create one for you?", "Kobei: Preferences", MB_ICONERROR | MB_YESNO)) {
		case 6:
			MessageBox(NULL, "Thank you!\nIf wou would, please direct me to the directory where you want me to store your books.\n\nPlease remember that this directory can be changed at your will.", "Kobei: Preferences", MB_ICONINFORMATION | MB_OK);
			Preferences::CreatePreferences();
			break;
		case 7:
			if (MessageBox(NULL, "Many features will be unavailable if you continue;\ndo you really wish to continue without a preferences file?", "Kobei: Preferences", MB_ICONQUESTION | MB_YESNO) == 7)
				Preferences::CreatePreferences();
			else
				return "NULL";
			break;
		}
	}
	return gcnew System::String(std::string(Preferences::GetBookDirectory() + "\\Books").c_str());
}

int Window::Hide() {
	Form->Hide();
	return 1;
}

int Window::Show() {
	Form->ShowDialog();
	return 1;
}


void Window::OnSelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	//throw gcnew System::NotImplementedException();
}

void Window::ShowSideBarMouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	SideBar->Visible = true;
	//ShowSideBar->Visible = false;
}

void Window::SideBarLeave(System::Object^ sender, System::EventArgs^ e)
{
	SideBar->Visible = false;
}


void Window::ShowCredits(System::Object^ sender, System::EventArgs^ e)
{
	if (Credits == nullptr) {
		Credits = gcnew CreditsForm();
	}
	Credits->ShowDialog();
}


void Window::CardClick(BookCard^ sender)
{
	currentBook = safe_cast<BookCard^>(sender);
	System::Threading::Thread^ thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &Window::LoadNovelAsync));
	thread->Start();
}


void Window::OnOpen(System::Object^ sender, System::EventArgs^ e)
{
	if (sender != nullptr) {
		System::Console::WriteLine("\n\n------------------\n\n");
		System::Console::WriteLine("Title: {0}", safe_cast<BookCard^>(sender)->AttachedBook->Title);
		System::Console::WriteLine("Author: {0}", safe_cast<BookCard^>(sender)->AttachedBook->Author);
		System::Console::WriteLine("Chapters: {0}", safe_cast<BookCard^>(sender)->AttachedBook->numChapters);
		System::Console::WriteLine("Current Chapter: {0}", safe_cast<BookCard^>(sender)->AttachedBook->CurrentChapter);
		System::Console::WriteLine("\n\n------------------\n\n");
		System::Console::WriteLine("Summary:\n{0}", safe_cast<BookCard^>(sender)->AttachedBook->Summary);
		System::Console::WriteLine("\n\n------------------\n\n");
	}
	else {
		std::cout << "Error! Null check failed!" << std::endl;
	}
	MessageBox(NULL, TEXT("Book details have been printed to console!"), TEXT("Kobei: BC 45t"), MB_ICONINFORMATION | MB_OK);
}


void Window::OnUpdateCLClick(System::Object^ sender, System::EventArgs^ e)
{
	std::cout << "Beginning Read of Data" << std::endl;
	std::cout << Preferences::GetBookDirectory() << std::endl;
	
	System::String^ dir = System::IO::Directory::GetDirectories(msclr::interop::marshal_as<System::String^>(Preferences::GetBookDirectory()))[0];
	cli::array<System::String^>^ di = System::IO::Directory::GetDirectories(dir);
	
	int chapters = 0;

	for (unsigned int idx = 0; idx < di->Length; idx++) {
		System::String^ ko = (dir + "\\" + safe_cast<BookCard^>(sender)->AttachedBook->Title);
		if (di[idx] == ko) {
			cli::array<System::String^>^ dis = System::IO::Directory::GetDirectories(di[idx]);
			for (unsigned int idx = 0; idx < dis->Length; idx++) {
				chapters = chapters + System::IO::Directory::GetFiles(dis[idx] + "\\Chapters")->Length;
			}
			std::cout << std::to_string(chapters) << std::endl;
		}
	}

	safe_cast<BookCard^>(sender)->AttachedBook->numChapters = chapters;
	safe_cast<BookCard^>(sender)->AttachedBook->Update();
}

void Window::LoadNovelAsync()
{
		Book^ b = currentBook->AttachedBook;
		b->VolumeUpdate();
		VolumeCollapsible^ volCol = gcnew VolumeCollapsible(b->Volumes);
		volCol->AutoScroll = FALSE;
		//volCol->Controls->Clear();
		volCol->Dock = System::Windows::Forms::DockStyle::Fill;
		volCol->Width = bookViewPage->Width;
		volCol->Height = bookViewPage->Height;
		volCol->Controls->Clear();
		volCol->GenerateControls();
		volCol->TriggerChapterOpen += gcnew VolumeCollapsible::EventHandler(this, &Window::OnTriggerChapterOpen);
		bookViewPage->Controls->Add(volCol);
		volCol->BackColor = System::Drawing::Color::Blue;
		SetSelectedIndex^ d = gcnew SetSelectedIndex(this, &Window::SetTabControlSelectedIndex);
		tabControl->Invoke(d, gcnew cli::array<System::Object^> {3});
		delete d;
		delete b;
		return;
}

void Window::OnTriggerChapterOpen(VolumeCollapsible^ sender, System::EventArgs^ e, unsigned int i, Chapter^ chapter)
{
	currentChapter = chapter;
	ChaperPageGeneration();
	tabControl->SelectedIndex = 6;
}

void Window::FromUriClick(System::Object^ sender, System::EventArgs^ e)
{
	// Pass progress bar and label to GetBook function.
	toolStripLabel1->Text = "BookFormLoaded : ";
	toolStripProgressBar1->Increment(5);
	System::Threading::Thread^ t2 = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &Window::DownloadBookPrompt));
	t2->Start();
	return;
}

System::Void Window::DownloadBookPrompt()
{
	HomePageGeneration();
	Book^ b = BookAddForm::GetBook(TRUE);
	HomePageGeneration();
	return System::Void();
}

void Window::BookAddOnClick(System::Object^ sender, System::EventArgs^ e)
{
	Book^ b = BookAddForm::GetBook(TRUE);
	delete homePage;
	HomePageGeneration();
	//throw gcnew System::NotImplementedException();
}