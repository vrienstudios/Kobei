#pragma once
ref class CreditsForm : System::Windows::Forms::Form {
private:
	 System::Windows::Forms::Label^ label2;
	 System::Windows::Forms::Label^ label3;
	 System::Windows::Forms::Label^ label1;
	 System::Windows::Forms::Label^ label4;
	 System::Windows::Forms::LinkLabel^ linkLabel1;
	 System::Windows::Forms::LinkLabel^ linkLabel2;
	 ~CreditsForm();
	 void TurboYoutubeClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	 void TurboTwitterClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
public:
	CreditsForm();
};