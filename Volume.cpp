#include "Volume.h"
#include "Chapter.h"
#include "Functions.h"
#include "Includes.h"
Volume::Volume()
{
	this->ChapterList = gcnew VTable(Chapter::typeid);
}

void Volume::ParseVolume(System::String^ directory) {
	cli::array<System::String^>^ split = directory->Split('\\');
	this->Name = split[split->Length - 1];
	split = System::IO::Directory::GetFiles(directory + "\\" + "Chapters");
	ChapterList = gcnew VTable(Chapter::typeid);
	cli::array<Chapter^>^ allocate = gcnew cli::array<Chapter^>(split->Length - 1);

	for (unsigned int idx = 0; idx < split->Length - 1; idx++) {
		cli::array<System::String^>^ ssplit = split[idx]->Split('\\');
		
		Chapter^ Chp = gcnew Chapter;

		Chp->Name = ssplit[ssplit->Length - 1];
		Chp->attachedVolume = this;
		Chp->Number = std::atoi(msclr::interop::marshal_as<std::string>(Chp->Name->ToString()).substr(0, Functions::LeadingIntegralCount(msclr::interop::marshal_as<std::string>(Chp->Name->ToString()).c_str())).c_str());
		Chp->Text = System::IO::File::ReadAllText(split[idx]);
		
		allocate[idx] = Chp;
		delete Chp;
		delete ssplit;
	}

	for (unsigned int idx = 0; idx < split->Length - 2; idx++) {
		for (unsigned int i = idx + 1; i > 0; i--) {
			if (std::atoi(msclr::interop::marshal_as<std::string>(allocate[i - 1]->Name->ToString()).substr(0, Functions::LeadingIntegralCount(msclr::interop::marshal_as<std::string>(allocate[i - 1]->Name->ToString()).c_str())).c_str()) > std::atoi(msclr::interop::marshal_as<std::string>(allocate[i]->Name->ToString()).substr(0, Functions::LeadingIntegralCount(msclr::interop::marshal_as<std::string>(allocate[i]->Name->ToString()).c_str())).c_str())) {
				Chapter^ t = allocate[i - 1];
				allocate[i - 1] = allocate[i];
				allocate[i] = t;
				delete t;
			}
		}
	}

	for (unsigned int i = 0; i < allocate->Length; i++)
		this->ChapterList->Add(i, allocate[i]);

	delete allocate;
	delete split;
}