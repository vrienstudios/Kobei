#pragma once

ref class BookViewPage : System::Windows::Forms::TabPage {
private:
	System::Windows::Forms::PictureBox^ coverImage;
	System::Windows::Forms::Label^ titleLabel;
	System::Windows::Forms::Label^ authorLabel;
	System::Windows::Forms::Label^ lastUpdateLabel;
	System::Windows::Forms::Label^ summaryLabel;

public:
	BookViewPage();
};