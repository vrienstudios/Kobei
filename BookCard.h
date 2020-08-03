#pragma once

#include "Book.h"

ref class BookCard : System::Windows::Forms::Panel {
private:
	System::Windows::Forms::ContextMenu^ cm;
	System::Windows::Forms::PictureBox^ Cover;
	System::Windows::Forms::Label^ Title;
	System::Windows::Forms::Label^ Author;
	System::Windows::Forms::Label^ Chapters;
	System::Windows::Forms::Label^ ChaptersRead;
	System::Windows::Forms::Label^ PercentageRead;

	property bool openFlag2;
public:

	property bool openFlag {
		void set(bool value) {
			openFire(this, System::EventArgs::Empty, 0);
		}
	};

	property bool updateNFlag {
		void set(bool value) {
			openFire(this, System::EventArgs::Empty, 1);
		}
	};

	property bool deleteFlag {
		void set(bool value) {
			openFire(this, System::EventArgs::Empty, 2);
		}
	};

	property bool updateCLFlag {
		void set(bool value) {
			openFire(this, System::EventArgs::Empty, 3);
		}
	};

	property bool SendCardClickEvent {
		void set(bool value) {
			CardClick();
		}
	};

	delegate void OpenHandler(System::Object^ sender, System::EventArgs^ e);
	Book^ AttachedBook;

	//Events
	event OpenHandler^ OnOpen;
	event OpenHandler^ OnDelete;
	event OpenHandler^ OnUpdateCLClick;
	event OpenHandler^ OnUpdateNClick;

	delegate void CardHandler(BookCard^ sender);
	event CardHandler^ OnCardClick;

	int bookIndex;
	bool CoverOnly;

	BookCard(Book^ book, bool coveronly);
	~BookCard();

	void OpenBook(System::Object^ sender, System::EventArgs^ e);
	void DeleteBook(System::Object^ sender, System::EventArgs^ e);
	void UpdateFromNetBook(System::Object^ sender, System::EventArgs^ e);
	void UpdateChapterListBook(System::Object^ sender, System::EventArgs^ e);

	virtual void openFire(System::Object^ sender, System::EventArgs^ e, unsigned int i);

	virtual void CardClick() {
		OnCardClick(this);
	}
	void OnClick(System::Object^ sender, System::EventArgs^ e);
	void OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
};