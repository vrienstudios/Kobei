#include "Volume.h"
#include "Chapter.h"

Volume::Volume()
{
	this->ChapterList = gcnew VTable(Chapter::typeid);
}

void Volume::ParseVolume(System::String^ directory) {
	cli::array<System::String^>^ split = directory->Split('\\');
	this->Name = split[split->Length - 1];
	split = System::IO::Directory::GetFiles(directory + "\\" + "Chapters");
	ChapterList = gcnew VTable(Chapter::typeid);
	for (unsigned int idx = 0; idx < split->Length - 1; idx++) {
		cli::array<System::String^>^ ssplit = split[idx]->Split('\\');
		
		Chapter^ Chp = gcnew Chapter;

		Chp->Name = ssplit[ssplit->Length - 1];
		Chp->attachedVolume = this;
		Chp->Number = idx;
		Chp->Text = System::IO::File::ReadAllText(split[idx]);
		
		ChapterList->Add(idx, Chp);
		delete Chp;
	}
}