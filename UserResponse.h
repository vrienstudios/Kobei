#pragma once
ref class UserResponse {
private:
	System::Windows::Forms::Form^ window;

	//Controls
	System::Windows::Forms::TextBox^ TextBox;
	System::Windows::Forms::FolderBrowserDialog^ FileDialog;
	System::Windows::Forms::Button^ Submit;

public:
	UserResponse();
	System::String^ GetResponse();

	void Hide();
	void Show();
};