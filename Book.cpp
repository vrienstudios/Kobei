#include "Book.h"
#include "Chapter.h"
#include "Includes.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Preferences.h"

void Book::VolumeUpdate() {
	delete Volumes;
	Volumes = gcnew VTable(Volume::typeid);
	cli::array<System::String^>^ dirs = System::IO::Directory::GetDirectories(Directory);
	for (unsigned int idx = 0; idx < dirs->Length; idx++) {
		Volume^ Vol = gcnew Volume();
		Vol->ParseVolume(dirs[idx]);
		this->Volumes->Add(idx, Vol);
		delete Vol;
	}
}

bool Book::Update()
{
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(this->Title->ToString()).c_str(), "000_b_Data.ktf");
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	stdPath = std::regex_replace(stdPath, std::regex("^ +| +$|( ) +"), "$1");
	std::ofstream L(stdPath.c_str());
	L << msclr::interop::marshal_as<std::string>(this->Title->ToString()).c_str() << "\n";
	L << msclr::interop::marshal_as<std::string>(this->Author->ToString()).c_str() << "\n";
	L << msclr::interop::marshal_as<std::string>(this->numChapters.ToString()).c_str() << "\n";
	L << msclr::interop::marshal_as<std::string>(this->CurrentChapter.ToString()).c_str() << "\n";
	if (this->Summary != nullptr) {
		L << "_SUMMARY_" << "\n";
		L << msclr::interop::marshal_as<std::string>(this->Summary->ToString()).c_str() << "\n";
		L << "_END_" << "\n";
	}
	L.close();
	
	return false;
}

inline Book^ Book::Update(Book^ book)
{
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(book->Title->ToString()).c_str(), "000_b_Data.ktf");
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	stdPath = std::regex_replace(stdPath, std::regex("^ +| +$|( ) +"), "$1");
	std::ofstream L(stdPath.c_str());
	L << msclr::interop::marshal_as<std::string>(book->Title->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(book->Author->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(book->numChapters.ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(book->CurrentChapter.ToString()).c_str();
	if (book->Summary != nullptr) {
		L << "_SUMMARY_";
		L << msclr::interop::marshal_as<std::string>(book->Summary->ToString()).c_str();
		L << "_END_";
	}
	L.close();
	return book;
}

Book^ Book::ParseBook(System::String^ bookfolder)
{
	std::cout << msclr::interop::marshal_as<std::string>(bookfolder->ToString());
	System::String^ Path = System::IO::Directory::GetFiles(bookfolder)[1];
	System::Drawing::Bitmap^ cover = gcnew System::Drawing::Bitmap(System::Drawing::Bitmap::FromFile(Path));
	//System::String^ title;
	std::ifstream istream(msclr::interop::marshal_as<std::string>(System::IO::Directory::GetFiles(bookfolder)[0]->ToString()));
	std::fstream fstream;
	fstream.open(msclr::interop::marshal_as<std::string>(System::IO::Directory::GetFiles(bookfolder)[0]->ToString()), std::ios::in);
	std::string a;
	std::string aa;
	int idx = 0;
	std::stringstream buffer;
	buffer << istream.rdbuf();
	Book^ book = gcnew Book(nullptr, nullptr, nullptr, nullptr);

	book->Directory = bookfolder;

	while (std::getline(buffer, aa, '\r'))
	{
		switch (idx) {
		case 0:
			book->Title = msclr::interop::marshal_as<System::String^>(aa);
			break;
		case 1:
			book->Author = msclr::interop::marshal_as<System::String^>(aa);
			break;
		case 2:
			book->numChapters = std::atoi(aa.c_str());
			break;
		case 3:
			book->CurrentChapter = std::atoi(aa.c_str());
			break;
		default:
			break;
		}
		idx++;
	}

	book->Cover = cover;

	return book;
}

Book::Book(System::Drawing::Bitmap^ cover, System::String^ title, System::String^ author, System::String^ lastUpdated)
{
	Cover = cover;
	Title = title;
	Author = author;
	UpdateTime = lastUpdated;
	Chapters = gcnew VTable(Chapter::typeid);
	Volumes = gcnew VTable(Volume::typeid);
}

Book::Book(const Book% book) {
	Cover = book.Cover;
	Title = book.Title;

	Ranking = book.Ranking;
	CurrentChapter = book.CurrentChapter;
	Chapters = book.Chapters;
}

Book::~Book()
{
	std::cout << "Deleting Book Object" << std::endl;
	delete Cover;
	delete Title;
	delete Author;
	delete Volumes;
	delete UpdateTime;
	ReadingTime = 0;
	Ranking = 0;
	CurrentChapter = 0;
	delete Chapters;
}