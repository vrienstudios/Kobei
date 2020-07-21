#include "CreditsForm.h"
CreditsForm::CreditsForm() {
	label2 = gcnew System::Windows::Forms::Label();
	label3 = gcnew System::Windows::Forms::Label();
	label1 = gcnew System::Windows::Forms::Label();
	label4 = gcnew System::Windows::Forms::Label();
	linkLabel1 = gcnew System::Windows::Forms::LinkLabel();
	linkLabel2 = gcnew System::Windows::Forms::LinkLabel();
	SuspendLayout();
	label2->AutoSize = true;
	label2->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12.0f, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, ((System::Byte)(0)));
	label2->Location = System::Drawing::Point(1, 29);
	label2->Name = "label2";
	label2->Size = System::Drawing::Size(104, 40);
	label2->TabIndex = 1;
	label2->Text = "Chay(ShuJia)\r\nChay#3670";
	label3->AutoSize = true;
	label3->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, ((System::Byte)(0)));
	label3->Location = System::Drawing::Point(-2, 9);
	label3->Name = "label3";
	label3->Size = System::Drawing::Size(107, 20);
	label3->TabIndex = 0;
	label3->Text = "~Developers~";
	label1->AutoSize = true;
	label1->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, ((System::Byte)(0)));
	label1->Location = System::Drawing::Point(2, 102);
	label1->Name = "label1";
	label1->Size = System::Drawing::Size(130, 16);
	label1->TabIndex = 2;
	label1->Text = "~AUDIO CREDITS~";
	label4->AutoSize = true;
	label4->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 12.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, ((System::Byte)(0)));
	label4->Location = System::Drawing::Point(1, 118);
	label4->Name = "label4";
	label4->Size = System::Drawing::Size(128, 20);
	label4->TabIndex = 3;
	label4->Text = "Turbo(EuroBeat)";
	linkLabel1->AutoSize = true;
	linkLabel1->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
	linkLabel1->Location = System::Drawing::Point(2, 138);
	linkLabel1->Name = "linkLabel1";
	linkLabel1->Size = System::Drawing::Size(47, 13);
	linkLabel1->TabIndex = 4;
	linkLabel1->TabStop = true;
	linkLabel1->Text = "Youtube";
	linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CreditsForm::TurboYoutubeClicked);
	linkLabel2->AutoSize = true;
	linkLabel2->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
	linkLabel2->Location = System::Drawing::Point(82, 138);
	linkLabel2->Name = "linkLabel2";
	linkLabel2->Size = System::Drawing::Size(39, 13);
	linkLabel2->TabIndex = 5;
	linkLabel2->TabStop = true;
	linkLabel2->Text = "Twitter";
	linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CreditsForm::TurboTwitterClicked);
	AutoScaleDimensions = System::Drawing::SizeF(6.0f, 13.0f);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	ClientSize = System::Drawing::Size(147, 173);
	Controls->Add(linkLabel2);
	Controls->Add(linkLabel1);
	Controls->Add(label4);
	Controls->Add(label1);
	Controls->Add(label2);
	Controls->Add(label3);
	FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
	MaximizeBox = false;
	MinimizeBox = false;
	Name = "Credits";
	SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
	Text = "Credits";
	ResumeLayout(false);
	PerformLayout();
}

void CreditsForm::TurboYoutubeClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
{
	throw gcnew System::NotImplementedException();
}


void CreditsForm::TurboTwitterClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
{
	throw gcnew System::NotImplementedException();
}

CreditsForm::~CreditsForm()
{
	throw gcnew System::NotImplementedException();
}