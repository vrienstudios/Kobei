#include <iostream>

#include "VTable.h"
#include "Window.h"
#include "Book.h"
#include "BookAddForm.h"
#include "Preferences.h"
// Entry Point
[System::STAThreadAttribute]
int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::cout << "Found Arguments... Reading.";
	}
	else {
		//std::cout << "Loading!";
		//Book^ b = BookAddForm::GetBook(TRUE);
		//Book^ b = gcnew Book(nullptr, "kev", "Chay", "2020");
		/*Volume^ Vol = gcnew Volume();
		Vol->Name = "Kevo";
		Vol->attachedBook = b;
		Chapter^ chp = gcnew Chapter();
		chp->Name = "1 Ckao";
		chp->Text = "LERO";
		Vol->ChapterList->Add(0, chp);
		BookAddForm::ExportVolumeFull(Vol);*/
		Window^ win = gcnew Window(800, 600);
		win->Show();
	}
	
	std::cin.get();
	return 0;
}