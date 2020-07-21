#pragma once

ref struct tPanel : System::Windows::Forms::Panel {

	property System::Windows::Forms::CreateParams^ CreateParams {
		System::Windows::Forms::CreateParams^ get() override {
			System::Windows::Forms::CreateParams^ cp = __super::CreateParams;
			cp->ExStyle |= 0x00000020; // WS_EX_TRANSPARENT

			return cp;
		}
	}

	//virtual void OnPaint(System::Windows::Forms::PaintEventArgs^ pevent) override {
	//	pevent->Graphics->FillRectangle(gcnew System::Drawing::SolidBrush(this->BackColor), this->ClientRectangle);
	//}
};