#include "UserResponse.h"

UserResponse::UserResponse() {
	window = gcnew System::Windows::Forms::Form;
	window->Height = 150;
	window->Width = 150;
	
	TextBox = gcnew System::Windows::Forms::TextBox;
	TextBox->Dock = System::Windows::Forms::DockStyle::Top;

	System::Windows::Forms::DialogResult DiagR = FileDialog->ShowDialog();
	if (DiagR == System::Windows::Forms::DialogResult::OK && !System::String::IsNullOrWhiteSpace(FileDialog->SelectedPath)) {
		TextBox->Text = FileDialog->SelectedPath;
	}
	window->Controls->Add(TextBox);
}

System::String^ UserResponse::GetResponse() {
	return TextBox->Text;
}

void UserResponse::Show() {
	window->Show();
}

void UserResponse::Hide() {
	window->Hide();
}