#pragma once
#include "Includes.h"
#include "Page.h"
#include "VTable.h"

ref class Dashboard : System::Windows::Forms::Panel {
	
private:
	VTable^ IndexPagePair;
	cli::array<MediaPage^>^ MediaPages;

	MediaPage^ selectedPage;

public:
	Dashboard(cli::array<MediaPage^>^ pages);
	~Dashboard();

	void Add(MediaPage^ page);
	void Select(int idx);
};