#pragma once
#include "Includes.h"
#include "Book.h"
#include "Chapter.h"
#include "Volume.h"
#include "Functions.h"

static ref class BookAddForm {
private:

	static System::Windows::Forms::Form^ Form = gcnew System::Windows::Forms::Form;
	static Book^ bk;

	static System::String^ Uri;
	static System::String^ AraHost;

	static System::Windows::Forms::CheckBox^ checkBox;
	static System::Windows::Forms::TextBox^ textBox;
	static System::Windows::Forms::Button^ submitBtn;
public:

	static void ShowForm() {
		if (Form != nullptr)
			Form->ShowDialog();
		else
			std::exception("Error: ShowForm BookAddForm null check failed?");
	}

	static bool IsNumericRef(System::String^ obj);

	static void Initform();

	static Book^ GetBook(bool showForm);

	static void ChapterWrap(Chapter^& chap, Volume^& _attachedVolume, System::String^ _uri, BOOLEAN _downloadContent, unsigned int flg);

	static void submitBtnOnMouseClick(System::Object^ sender, System::EventArgs^ e);

	static void LoadBookFromUri();

	static void ExportVolumeExChapter(Volume^ volume);
	static void ExportChapterSingular(Chapter^ chapter);
	static void ExportVolumeFull(Volume^ volume);

	static std::string StripAZ(std::string s);

	static BOOL DownloadFromWuxiaWorld();
	static void EnumerateWeb(System::Collections::IEnumerator^ enumerable, BOOL downloadChapter, unsigned int length);
	static System::String^ WWDownloadChapterContent(Chapter^ Chp);

	static BOOL DownloadFromBoxNovel();
	static void EnumerateWebBoxNovel(VTable^ table, BOOL downloadChapter, unsigned int length);
	static System::String^ BNDownloadChapterContent(Chapter^ Chp, System::Net::WebClient^ wc);
};