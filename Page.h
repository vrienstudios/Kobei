#pragma once

ref struct MediaPage : System::Windows::Forms::PictureBox {
	int mediaIndex;
	MediaPage();

	virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ pevent) override {
		__super::OnPaint(pevent);
		
		System::Drawing::StringFormat^ format = gcnew System::Drawing::StringFormat;
		format->FormatFlags = System::Drawing::StringFormatFlags::NoFontFallback;

		pevent->Graphics->DrawString(this->Text, gcnew System::Drawing::Font("Arial", 16.0f, System::Drawing::FontStyle::Bold), gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black), 0, this->Height - 25, format);
	}
};