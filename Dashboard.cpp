#include "Dashboard.h"

Dashboard::Dashboard(cli::array<MediaPage^>^ pages)
{
	MediaPages = pages;
	IndexPagePair = gcnew VTable(MediaPage::typeid);
	for (int idx = 0; idx < pages->Length; idx++) {
		IndexPagePair->Add(idx, pages[idx]);
	}
}

Dashboard::~Dashboard()
{
	delete IndexPagePair;
}

void Dashboard::Add(MediaPage^ page)
{
	throw gcnew System::NotImplementedException();
}

void Dashboard::Select(int idx)
{
	selectedPage = safe_cast<MediaPage^>(IndexPagePair(idx, true));
	this->Controls->Clear();
	selectedPage->Dock = System::Windows::Forms::DockStyle::Fill;
	this->Controls->Add(selectedPage);
}