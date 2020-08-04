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
		Window^ win = gcnew Window(800, 600);
		win->Show();
	}
	
	std::cin.get();
	return 0;
}