#pragma once

#include "Dimensions.h"
#include "Button.h"
#include "Book.h"
#include "VTable.h"
#include "Includes.h"
#include "panel.h"
#include "CreditsForm.h"
#include "BookCard.h"
#include "Volume.h"
#include "VolumeCollapsible.h"
#include "ChapterViewer.h"

ref class Window {
private:
	int pl;
	int ph;
	VTable^ BookTable;

	// Window width and height.
	Dimensions* windowDimension = new Dimensions();

	// ~Controls~ //
	System::Windows::Forms::Form^ Form;
	CreditsForm^ Credits;

	//Tab Control
	System::Windows::Forms::TabControl^ tabControl;

	//Pages
	System::Windows::Forms::TabPage^ homePage;
	System::Windows::Forms::TabPage^ addBookPage;
	System::Windows::Forms::TabPage^ bookListPage;
	System::Windows::Forms::TabPage^ bookViewPage;
	System::Windows::Forms::TabPage^ emailSupportPage;
	System::Windows::Forms::TabPage^ aboutPage;
	System::Windows::Forms::TabPage^ chapterDetailView;

	// Buttons //
	//SideBar Buttons
	Button^ BtnHome;
	Button^ BtnAdd;
	Button^ BtnBookList;
	Button^ BtnSupport;
	Button^ BtnAbout;

	// TOOL STRIP //
	System::Windows::Forms::ToolStripDropDownButton^ toolStripDropDownButton1;
	System::Windows::Forms::ToolStripMenuItem^ importKTFBookToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ exportAsKTFBookToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ exportAsEBookToolStripMenuItem;
	System::Windows::Forms::ToolStripProgressBar^ toolStripProgressBar1;
	System::Windows::Forms::ToolStripLabel^ toolStripLabel1;
	System::Windows::Forms::ToolStrip^ toolStrip1;
	System::Windows::Forms::ToolStripDropDownButton^ toolStripDropDownButton2;
	System::Windows::Forms::ToolStripMenuItem^ addBookToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ fromUriToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ fromFolderToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ autoExportAsEbookToolStripMenuItem;
	System::Windows::Forms::ToolStripDropDownButton^ toolStripDropDownButton3;
	System::Windows::Forms::ToolStripMenuItem^ audioToolStripMenuItem;
	System::Windows::Forms::ToolStripMenuItem^ accessibilityToolStripMenuItem;
	System::Windows::Forms::ToolStripButton^ toolStripButton1;

	//Panels
	System::Windows::Forms::Panel^ Main;
	System::Windows::Forms::Panel^ SideBar;
	tPanel^ ShowSideBar;

	int HomePageGeneration();
	int AddPageGeneration();
	int BookListPageGeneration();
	int BookViewPageGeneration();
	int EmailSupportPageGeneration();
	int AboutPageGeneration();
	int ChaperPageGeneration(Volume^ selvolume);


	int LoadBooks();
	System::String^ GetBookDirectory();
	BookCard^ currentBook;
	Chapter^ currentChapter;

	System::Void DownloadBookPrompt();

public:
	// Constructor and destructor.
	Window(unsigned int w, unsigned int h);	
	Window();
	virtual ~Window();

	static Book^ bookCardAttachedNovel;

	int Create();
	int PageGeneration();
	int Show();
	int Hide();

	//Events
	void OnTriggerChapterOpen(VolumeCollapsible^ sender, System::EventArgs^ e, unsigned int i, Volume^ vol);
	void FromUriClick(System::Object^ sender, System::EventArgs^ e);
	void OnSelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	void ShowSideBarMouseEnter(System::Object^ sender, System::EventArgs^ e);
	void BookAddOnClick(System::Object^ sender, System::EventArgs^ e);
	void SideBarLeave(System::Object^ sender, System::EventArgs^ e);
	void ShowCredits(System::Object^ sender, System::EventArgs^ e);
	void CardClick(BookCard^ sender);
	void OnOpen(System::Object^ sender, System::EventArgs^ e);
	void OnUpdateCLClick(System::Object^ sender, System::EventArgs^ e);

	//Threading
	void LoadNovelAsync();

	//Threading Delagates
	delegate void SetSelectedIndex(int index);
	delegate void SetDock(System::Windows::Forms::DockStyle dockstyle);
	delegate void AddControls(System::Windows::Forms::Control^ control);
	delegate void CreateBookCard(Book^ b, unsigned int i);
	delegate void ClearControls();

	//TabControl
	void SetTabControlSelectedIndex(int index) {
		tabControl->SelectedIndex = index;
	}

	//Homepage
	void SetHomePageDockStyle(System::Windows::Forms::DockStyle dockstyle) {
		homePage->Dock::set(dockstyle);
	}
	void SetHomePageTabPageIndex(int index) {
		homePage->TabIndex = index;
	}
	void AddHomePageControl(System::Windows::Forms::Control^ control) {
		homePage->Controls->Add(control);
	}
	void AddBookCard(Book^ b, unsigned int i) {
		BookCard^ bc = gcnew BookCard(b, false);
		bc->bookIndex = i;

		if (i == 0) {
			bc->Location = System::Drawing::Point(pl, ph);
		}
		else {
			pl += bc->Width + 5;
			if (pl > Form->Width - bc->Width) {
				pl = 80;
				ph += bc->Height + 5;
			}
			bc->Location = System::Drawing::Point(pl, ph);
		}

		bc->OnOpen += gcnew BookCard::OpenHandler(this, &Window::OnOpen);
		bc->OnUpdateCLClick += gcnew BookCard::OpenHandler(this, &Window::OnUpdateCLClick);
		bc->OnCardClick += gcnew BookCard::CardHandler(this, &Window::CardClick);
		homePage->Controls->Add(bc);
	}
	void ClearHomePageControls() {
		homePage->Controls->Clear();
	}
	void OnOnOpen(ChapterView^& sender, System::EventArgs^ e);
};