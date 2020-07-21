#include "Preferences.h"
#include <filesystem>
#include <sstream>


std::string Preferences::GetBookDirectory()
{
	if (std::strlen(bookDir) == 0) {
		std::cout << "Bk_Dir not global, creating global." << std::endl;
		std::ifstream settingsFile;
		settingsFile.open("C:\\Program Files (x86)\\Kobei\\settings.txt");
		std::string a;
		std::getline(settingsFile, a);
		settingsFile.close();
		std::strncpy(bookDir, a.c_str(), sizeof(bookDir));
		bookDir[sizeof(bookDir) - 1] = 0;
		return a;
	}
	else
		return bookDir;
}

void Preferences::CreatePreferences() {
A:
	System::Windows::Forms::FolderBrowserDialog^ FileDialog = gcnew System::Windows::Forms::FolderBrowserDialog;
	System::Windows::Forms::DialogResult DiagR = FileDialog->ShowDialog();
	msclr::interop::marshal_context context;

	//Show dialog and get dialog result.
	if (DiagR == System::Windows::Forms::DialogResult::OK && !System::String::IsNullOrWhiteSpace(FileDialog->SelectedPath)) {
		//Check whether the directory exists or not. Then proceed.
		if (CreateDirectory("C:\\Program Files (x86)\\Kobei", NULL) || ERROR_ALREADY_EXISTS == GetLastError()) { 

			//Path to settings file
			std::ofstream setingsFile("C:\\Program Files (x86)\\Kobei\\settings.txt");

			//Path to selected directory in managed format.
			std::string filePath = context.marshal_as<std::string>(FileDialog->SelectedPath);
			
			setingsFile << filePath << std::endl;

			//Finish up.
			std::string s1 = std::string(filePath + "\\Books");
			CreateDirectory(s1.c_str(), NULL);
			setingsFile.close();

			std::string s2 = filePath + "\\LastRead.txt";
			System::IO::File::Create(gcnew System::String(s2.c_str()))->Close();
		}
		else {
			if (GetLastError() == 5) {
				char buffer[1024];
				sprintf_s(buffer, "Error %i: Access denied\nPlease rerun the program as administrator.", GetLastError());
				MessageBox(NULL, buffer, "Kobei: Preferences", MB_ICONERROR | MB_OK);
			}

			wchar_t buf[256];
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
			std::wstring ws(buf);
			MessageBox(NULL, std::string(ws.begin(), ws.end()).c_str(), "Kobei: Preferences", MB_ICONERROR | MB_OK);
		}
	}
	else
	{
		MessageBox(NULL, "Failed to read path, retry.", "Kobei: Preferences", MB_ICONERROR | MB_OK);
		goto A;
	}

	delete FileDialog;
}

std::string Preferences::GetFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string Preferences::GetDirectory()
{
	if (std::strlen(regDir) == 0) {
		std::cout << "Ex_DIR not global, creating global." << std::endl;
		std::string f = GetFileName();
		f = f.substr(0, f.find_last_of("\\/"));
		std::strncpy(regDir, f.c_str(), sizeof(regDir));
		regDir[sizeof(regDir) - 1] = 0;
		return f;
	}
	else
		return std::string(regDir);
}