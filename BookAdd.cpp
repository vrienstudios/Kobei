#include "BookAddForm.h"
#include "Preferences.h"
#include "Chapter.h"
#include "Volume.h"
#include <algorithm>
#include <regex>


Book^ BookAddForm::GetBook(bool showForm)
{
	if (!showForm)
		return BookAddForm::bk;

	Initform();
	Form->ShowDialog();

	return BookAddForm::bk;
}

void BookAddForm::Initform()
{
	Form->Width = 320;
	Form->Height = 80;
	Form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;

	Form->MinimizeBox = false;
	Form->MaximizeBox = false;

	checkBox = gcnew System::Windows::Forms::CheckBox;
	checkBox->Text = "Check values";
	checkBox->Location::set(System::Drawing::Point(210, 0));

	textBox = gcnew System::Windows::Forms::TextBox;
	textBox->Text = "URL";
	textBox->Width = 200;
	textBox->Location::set(System::Drawing::Point(0, 0));
	textBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

	submitBtn = gcnew System::Windows::Forms::Button;
	submitBtn->Text = "Submit!";
	submitBtn->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
	submitBtn->Dock = System::Windows::Forms::DockStyle::Bottom;
	submitBtn->Click += gcnew System::EventHandler(&BookAddForm::submitBtnOnMouseClick);

	System::Windows::Forms::ToolTip^ tTip = gcnew System::Windows::Forms::ToolTip;
	tTip->AutoPopDelay = 5000;
	tTip->InitialDelay = 1000;
	tTip->ReshowDelay = 450;
	tTip->ShowAlways = true;
	tTip->SetToolTip(checkBox, "If you want to make sure that I got everything right and/or check/change the title, author, etc, check this.");
	tTip->SetToolTip(textBox, "Put the url to the novel here (currently only supports wuxiaworld novels.)");

	Form->Controls->AddRange(gcnew cli::array<System::Windows::Forms::Control^>{checkBox, textBox, submitBtn });

	textBox->Text = "https://www.boxnovel.com/novel/i-am-a-prodigy/";
}

void BookAddForm::submitBtnOnMouseClick(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox->Text->ToCharArray()->Length < 4)
		MessageBox(NULL, "Hmmm? Looks like you failed to provide me with an actual url! Please feed this hungry wolf an url.", "Kobei: Book Addition", MB_ICONERROR | MB_OK);

	Uri = gcnew System::String(textBox->Text);
	LoadBookFromUri();
}

bool BookAddForm::IsNumericRef(System::String^ obj) {
	short res = 0;
	return System::Int16::TryParse(obj, res);
}

std::string BookAddForm::StripAZ(std::string t)
{
	std::string tem;
	for (int i = 0; i < t.size(); ++i) {
		if ((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z') || t[i] == ' ') {
			tem = tem + t[i];
		}
	}
	return tem;
}

void BookAddForm::ExportVolumeFull(Volume^ volume)
{
	std::cout << "\n{80}:Exporting Volume *FULL* function entered -> extremely experimental (warning)" << "\n";
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(volume->attachedBook->Title->ToString()).c_str(), msclr::interop::marshal_as<std::string>(volume->Name->ToString()).c_str());
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	stdPath = std::regex_replace(stdPath, std::regex("^ +| +$|( ) +"), "$1");
	std::cout << "{80} I sure hope that this path is correct and free of everything except a-z/A-Z 1-100 :: " << stdPath << "\n";
	std::string bookp;
	sprintf_s(buffer, "%s\\Books\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(volume->attachedBook->Title->ToString()).c_str());
	bookp = std::string(buffer);
	CreateDirectory(bookp.c_str(), NULL);
	if (CreateDirectory(stdPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		std::cout << "{80}:Path reached and created; you can breathe a sigh of relief now." << "\n";
		std::string VolumePath;
		sprintf_s(buffer, "%s\\Chapters", stdPath.c_str());
		VolumePath = std::string(buffer);
		VolumePath = std::regex_replace(VolumePath, std::regex("^ +| +$|( ) +"), "$1");
		if (CreateDirectory(VolumePath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			std::cout << "Entered Chapter Export" << "\n";
			for (int idx = 0; idx < volume->ChapterList->Length(); idx++) {
				Chapter^ Chp = safe_cast<Chapter^>(volume->ChapterList(idx, true));
				std::string chapterPath;
				sprintf_s(buffer, "%s\\%s.%s", VolumePath.c_str(), msclr::interop::marshal_as<std::string>(Chp->Name->ToString()).c_str(), "ktf");
				chapterPath = buffer;
				std::ofstream CharlesTheFirstStream(chapterPath.c_str());
				CharlesTheFirstStream << "_HEAD_CHAPTER_" << "\n";
				CharlesTheFirstStream << msclr::interop::marshal_as<std::string>(Chp->Name->ToString()) << "::" << std::to_string(Chp->Number) << "\n";
				CharlesTheFirstStream << "_TEXT_" << "\n";
				if (Chp->Text == nullptr)
					CharlesTheFirstStream << "_TEXT__NULL_";
				else
					CharlesTheFirstStream << msclr::interop::marshal_as<std::string>(Chp->Text->ToString()) << "\n";
				CharlesTheFirstStream << "_CHAPTER_END_" << "\n";
				CharlesTheFirstStream.close();
			}
		}
		else
		{
			wchar_t buf[256];
			FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
			std::wstring ws(buf);
			MessageBox(NULL, std::string(ws.begin(), ws.end()).c_str(), "Kobei: Preferences", MB_ICONERROR | MB_OK);
		}
	}
	else {
		wchar_t buf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
		std::wstring ws(buf);
		MessageBox(NULL, std::string(ws.begin(), ws.end()).c_str(), "Kobei: Preferences", MB_ICONERROR | MB_OK);
	}
}

void BookAddForm::ExportVolumeExChapter(Volume^ volume)
{
	//https://www.wuxiaworld.co/Lord-of-the-Mysteries/
	std::cout << "\n{80}:Exporting Volume function entered -> experimental (warning)" << "\n";
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(volume->attachedBook->Title->ToString()).c_str(), msclr::interop::marshal_as<std::string>(volume->Name->ToString()).c_str());
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	std::cout << "{80} I sure hope that this path is correct and free of everything except a-z/A-Z 1-100 :: " << stdPath << "\n";
	if (CreateDirectory(stdPath.c_str(), NULL)) {
		std::cout << "{80}:Path reached and created; you can breathe a sigh of relief now." << "\n";
		std::string VolumePath;
		sprintf_s(buffer, "%s\\Volumes\\%s", stdPath.c_str(), msclr::interop::marshal_as<std::string>(volume->Name->ToString()).c_str());
		VolumePath = std::string(buffer);
		CreateDirectory(VolumePath.c_str(), NULL);
		
		//delete buffer;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError()) {
		std::cout << "{80} No need to worry now! The path already exists! Ahaha, that means we went through the last of the risky stuff.";
		std::string VolumePath;
		sprintf_s(buffer, "%s\\Volumes\\%s", stdPath.c_str(), msclr::interop::marshal_as<std::string>(volume->Name->ToString()).c_str());
	}
	else {
		wchar_t buf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
		std::wstring ws(buf);
		MessageBox(NULL, std::string(ws.begin(), ws.end()).c_str(), "Kobei: Preferences", MB_ICONERROR | MB_OK);
	}
}

void BookAddForm::ExportChapterSingular(Chapter^ chapter)
{
	if (chapter->attachedVolume == nullptr)
		std::exception("Wrong method called! This novel does not contain a volume object; did you mean ExportVolumeMass()?");

	Volume^ VolObject = chapter->attachedVolume;
	char buffer[10000];
	std::string path;
	path = sprintf_s(buffer, "%s\\Books\\%s", Preferences::GetBookDirectory(), VolObject->Name);
	if (CreateDirectory(path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		std::string chapterPath;
		chapterPath = sprintf_s(buffer, "%s\\%s.%s", path, chapter->Name, "ktf");
		std::ofstream CharlesTheFirstStream(chapterPath.c_str());
		CharlesTheFirstStream << msclr::interop::marshal_as<std::string>(chapter->Text->ToString());
		delete buffer;
	}
}

void BookAddForm::ChapterWrap(Chapter^& chap, Volume^& _attachedVolume, System::String^ _uri, BOOLEAN _downloadContent, unsigned int flg) {
	chap->attachedVolume = _attachedVolume;
	chap->Uri = _uri;
	if(_downloadContent)
		switch (flg) {
		case 0:
			chap->Text = WWDownloadChapterContent(chap);
			break;
		}
}

void BookAddForm::EnumerateWeb(System::Collections::IEnumerator^ enumerable, BOOL downloadChapter, unsigned int length)
{
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(BookAddForm::bk->Title->ToString()).c_str(), "000_b_Data.ktf");
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	stdPath = std::regex_replace(stdPath, std::regex("^ +| +$|( ) +"), "$1");
	std::ofstream L(stdPath.c_str());
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Title->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Author->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->CurrentChapter.ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->CurrentChapter.ToString()).c_str();
	if (BookAddForm::BookAddForm::bk->Summary != nullptr) {
		L << "_SUMMARY_";
		L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Summary->ToString()).c_str();
		L << "_END_";	
	}
	L.close();

	// Setup buffer for chapterlist
	Volume^ VolumeBuffer;
	VTable^ volumes = gcnew VTable(Volume::typeid);
	VTable^ ChapterList = gcnew VTable(cli::array<System::String^>::typeid);
	VTable^ ChapBuffer = gcnew VTable(Chapter::typeid);
	Chapter^ ChapBf;

	enumerable->Reset();
	
	std::string ihtml;
	std::regex reg("href=\"(.*)\">");
	std::smatch rm;
	mshtml::IHTMLElement^ element;
	int VolumeExports = 0;
	int x = 0;
	for (unsigned int idx = 0; idx < length; idx++) //enumerate the enumerable.
	{
		enumerable->MoveNext();
			// Declare handle for element and grab current element;
			element = safe_cast<mshtml::IHTMLElement^>(enumerable->Current);
			if (element != nullptr) { // nullcheck
				if (IsNumericRef(element->innerText->ToCharArray()[0].ToString()) == true) { // check if the element has a chapter number
					if (VolumeBuffer != nullptr && !ChapterList->ContainsAccessor(VolumeBuffer)) { // Make sure that the volume is not a copy and t hat VolumeBuffer exists.
						element = safe_cast<mshtml::IHTMLElement^>(enumerable->Current); // set element to current element.
						Chapter^ Chp = gcnew Chapter; // Create a new handle for Chapter
						Chp->Name = element->innerText; // Set the chapter name to the elements text which should be {number} {name};
						ihtml = msclr::interop::marshal_as<std::string>(element->innerHTML); // Get element href data
						std::regex_search(ihtml, rm, reg); // Match said html to regex expression to find the ID url.
						sprintf_s(buffer, "%s/%s", msclr::interop::marshal_as<std::string>(Uri->ToString()).c_str(), rm[1].str().c_str()); // Parse the ID URL
						if (System::String(buffer).ToString() != "https://www.wuxiaworld.co/Lord-of-the-Mysteries//") { // check if it's an actual chapter object.
							ChapterWrap(Chp, VolumeBuffer, System::String(buffer).ToString(), downloadChapter, 0); // Wrap all contents to the Chapter
							VolumeBuffer->ChapterList->Add(x, Chp); // Add chapter to the volume buffer
							x++;
							ChapBf = Chp;
						}
						delete Chp;
					}
					else { // if for some reason volume buffer doesn't exist error.
						std::exception("ERROR 114");
					}
				}
				else { // Override and export old volume.
					if (VolumeBuffer != nullptr) {
						ExportVolumeFull(VolumeBuffer);
						BookAddForm::bk->Volumes->Add(VolumeExports, VolumeBuffer);
						VolumeExports++;
					}
					if (idx != 0) {
						Volume^ Vol = gcnew Volume; // Create a new handle for Volume
						Vol->Name = element->innerText; // Set volume name to html element text.
						Vol->attachedBook = BookAddForm::bk;
						VolumeBuffer = Vol; // Set VolumeBuffer
						//MessageBox(NULL, msclr::interop::marshal_as<std::string>("IF135: " + Vol->Name->ToString()).c_str(), "Kobei: AddBook", MB_ICONERROR | MB_YESNO);
						//ExportVolumeFull(Vol);
						x = 0;
						delete Vol; // Delete handle
						//break; // No need to continue loop.
					}
				}
			}
	}

	VolumeExports++;
	ExportVolumeFull(VolumeBuffer); // Export last volume;
	BookAddForm::bk->Volumes->Add(VolumeExports, VolumeBuffer);
	x = 0;
	delete element;

}

void BookAddForm::EnumerateWebBoxNovel(VTable^& table, BOOL downloadChapter, unsigned int length)
{
	char buffer[1024];
	std::string stdPath;
	sprintf_s(buffer, "%s\\Books\\%s\\%s", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(BookAddForm::bk->Title->ToString()).c_str(), "000_b_Data.ktf");
	stdPath = std::string(buffer);
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '\r'), stdPath.end());
	stdPath.erase(std::remove(stdPath.begin(), stdPath.end(), '?'), stdPath.end());
	stdPath = std::regex_replace(stdPath, std::regex("^ +| +$|( ) +"), "$1");
	std::ofstream L(stdPath.c_str());
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Title->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Author->ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->CurrentChapter.ToString()).c_str();
	L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->CurrentChapter.ToString()).c_str();
	if (BookAddForm::BookAddForm::bk->Summary != nullptr) {
		L << "_SUMMARY_";
		L << msclr::interop::marshal_as<std::string>(BookAddForm::bk->Summary->ToString()).c_str();
		L << "_END_";
	}
	L.close();

	std::string ihtml;
	std::regex reg("href=\"(.*)\">");
	std::smatch rm;
	mshtml::IHTMLElement^ element;

	for (int idx = 0; idx < table->Length(); idx++) {
		element = safe_cast<mshtml::IHTMLElement^>(table(idx));

	}
}

// Multi threading for this will come much further down the road. It would require me to rewrite this.
// I plan on splitting each Volume between a pool of threads. E.x one volume ~129 chapters would get one thread while another ~200 chapters would also get one.
// This will do away with sequential downloads.
BOOL BookAddForm::DownloadFromWuxiaWorld() {
	System::Net::WebClient^ wc = gcnew System::Net::WebClient;

	char sprintBuffer[1024];

	System::String^ wwHtml;
	//Point us to where the cover should be stored.
	System::String^ ex;
	System::String^ e;

	mshtml::HTMLDocument^ WuxiaWorld;
	mshtml::IHTMLDocument2^ WuxiaWorld2;
	mshtml::IHTMLElement^ node;

	cli::array<System::String^>^ mainArgs;

	Book^ B;

	// Init
	wwHtml = wc->DownloadString(Uri);
	//Copy html document to htmlDocument
	WuxiaWorld = gcnew mshtml::HTMLDocumentClass();
	WuxiaWorld2 = (mshtml::IHTMLDocument2^)WuxiaWorld;
	WuxiaWorld2->write(wwHtml);
	//Get info node to gather information
	node = WuxiaWorld->getElementById("info");
	mainArgs = node->innerText->Split(gcnew cli::array<System::String^>{"\n"}, System::StringSplitOptions::None);

	//Initialize book with that information
	std::string btitle = msclr::interop::marshal_as<std::string>(mainArgs[1]->Substring(7));
	B = gcnew Book(nullptr, mainArgs[0], msclr::interop::marshal_as<System::String^>(btitle.substr(0, btitle.length() - (Functions::CountFollowingWhiteSpace(btitle, 0)))), mainArgs[3]->Substring(11));
	btitle.clear();
	B->Summary = node->innerHTML;
	//Honestly, fuck windows and backslash.
	sprintf_s(sprintBuffer, "%s\\Books\\%s\\%s.jpg", Preferences::GetBookDirectory().c_str(), msclr::interop::marshal_as<std::string>(B->Title->ToString()).c_str(), msclr::interop::marshal_as<std::string>(B->Title->ToString()).c_str());
	ex = msclr::interop::marshal_as<System::String^>(std::string(sprintBuffer));

	ex = ex->Replace("\r", System::String::Empty);

	//e = "http://" + "wuxiaworld.co" + "/BookFiles/BookImages/" + B->Title->Replace(' ', '-') + ".jpg";
	System::String^ fckintellisenseandplusoperators = B->Title->ToString()->Replace(' ', '-');
	sprintf_s(sprintBuffer, "https://www.wuxiaworld.co/BookFiles/BookImages/%s.jpg", msclr::interop::marshal_as<std::string>(fckintellisenseandplusoperators).c_str());
	e = msclr::interop::marshal_as<System::String^>(std::string(sprintBuffer));
	e = e->Replace("\r", System::String::Empty);

	System::IO::Directory::CreateDirectory(System::String::Format("{0}\\Books\\{1}", msclr::interop::marshal_as<System::String^>(Preferences::GetBookDirectory()), B->Title->ToString()));
	wc->DownloadFile(e, ex);
	B->Cover = gcnew System::Drawing::Bitmap(ex);
	BookAddForm::bk = B;
	node = WuxiaWorld->getElementById("list");
	//Port it to an enumerable object.
	mshtml::IHTMLElementCollection^ HTMLElements = (mshtml::IHTMLElementCollection^)node->all;

	//Get Enumerator
	System::Collections::IEnumerator^ enumerable = HTMLElements->GetEnumerator();
	sprintf_s(sprintBuffer, "Would you like for me to download all the available chapters? There are %i available. \n{Disclaimer!} Chapters take on average ~2s to download and parse depending on the internet connection. So beware, this could take a long time.\nI plan on adding a background download function later on and provide multi-threaded support. Please note, I will always be trying to optimize this, so please hold on.", HTMLElements->length);
	switch (MessageBox(NULL, sprintBuffer, "Kobei: AddBook", MB_ICONERROR | MB_YESNO)) {
	case 6:
		//Call EnumerateWeb function
		EnumerateWeb(enumerable, TRUE, HTMLElements->length);
		break;
	case 7:
		EnumerateWeb(enumerable, FALSE, HTMLElements->length);
		break;
	}

	delete wwHtml;
	delete ex;
	delete e;
	delete WuxiaWorld;
	delete WuxiaWorld2;
	delete node;
	delete mainArgs;
	delete B;

	return true;
}

BOOL BookAddForm::DownloadFromBoxNovel()
{
	System::Net::WebClient^ wc = gcnew System::Net::WebClient;

	char sprintBuffer[1024];

	mshtml::HTMLDocument^ BoxNovel;
	mshtml::IHTMLDocument2^ BoxNovel2;
	mshtml::IHTMLElement^ node;

	//Copy html document to htmlDocument
	BoxNovel = gcnew mshtml::HTMLDocumentClass();
	BoxNovel2 = (mshtml::IHTMLDocument2^)BoxNovel;
	BoxNovel2->write(wc->DownloadString(Uri));

	cli::array<System::String^>^ mainArgs;

	Book^ B;
	mshtml::IHTMLElementCollection^ collection = BoxNovel->all;
	mshtml::IHTMLElement^ title = Functions::GetFirstElementByClassName(collection->GetEnumerator(), "post-title", collection->length); //TODO: start a thread for both of these.
	mshtml::IHTMLElement^ author = Functions::GetFirstElementByClassName(collection->GetEnumerator(), "author-content", collection->length);
	node = BoxNovel->getElementById("editdescription");
	B = gcnew Book(nullptr, title->innerText, author->innerText, nullptr);
	B->Summary = node->innerText;
	bk = B;
	mshtml::HTMLDivElement^ a = safe_cast<mshtml::HTMLDivElement^>(Functions::GetFirstElementByClassName(collection->GetEnumerator(), "c-page", collection->length));
	System::Object^ obj = a->innerHTML;
	BoxNovel = gcnew mshtml::HTMLDocumentClass();
	BoxNovel2 = (mshtml::IHTMLDocument2^)BoxNovel;
	BoxNovel2->write(a->innerHTML);
	collection = BoxNovel->all;

	VTable^ chapters = Functions::GetAllElementsByClassName(collection->GetEnumerator(), "wp-manga-chapter", collection->length);
	delete BoxNovel, BoxNovel2, title, author, node;
	//sprintf_s(sprintBuffer, "Would you like for me to download all the available chapters? There are %i available. \n{Disclaimer!} Chapters take on average ~2s to download and parse depending on the internet connection. So beware, this could take a long time.\nI plan on adding a background download function later on and provide multi-threaded support. Please note, I will always be trying to optimize this, so please hold on.", chapters->Length());
	switch (MessageBox(NULL, sprintBuffer, "Kobei: AddBook", MB_ICONERROR | MB_YESNO)) {
	case 6:
		//Call EnumerateWeb function
		//EnumerateWebBoxNovel(chapters, TRUE, chapters->Length());
		break;
	case 7:
		//EnumerateWebBoxNovel(chapters, FALSE, chapters->Length());
		break;
	}
	delete collection;
	return 0;
}

void BookAddForm::LoadBookFromUri() {
	System::String^ Host = Uri;

	std::regex reg("www.(.*)(.com|.co|.net)");
	std::smatch rm;

	if (Uri->Contains("https://"))
		Host = Uri->Remove(0, 8);
	else if (Uri->Contains("http://"))
		Host = Uri->Remove(0, 7);
	else
		throw std::exception("URL must have HTTP or HTTPS");

	std::string regSearchString = msclr::interop::marshal_as<std::string>(Host);

	std::regex_search(regSearchString, rm, reg);

	//MessageBox(NULL, rm[1].str().c_str(), "kbm", MB_ICONASTERISK);

	if (rm.size() <= 0)
		throw std::exception("Your URL is not currently supported! ec: 271");

	AraHost = Host;
	
	switch (Functions::SwitchString(rm[1].str().c_str())) {
	default:
		throw std::exception("unrecogonized host ec: 349");
	case Functions::SwitchString("wuxiaworld"):
		DownloadFromWuxiaWorld();
		break;
	case Functions::SwitchString("boxnovel"):
		DownloadFromBoxNovel();
		break;
	}
}

System::String^ BookAddForm::WWDownloadChapterContent(Chapter^ Chp)
{
	System::Net::WebClient^ wc = gcnew System::Net::WebClient;
	mshtml::HTMLDocument^ WuxiaWorld;
	mshtml::IHTMLDocument2^ WuxiaWorld2;
	mshtml::IHTMLElement^ node;
	
	System::String^ Data = wc->DownloadString(Chp->Uri);	
	WuxiaWorld = gcnew mshtml::HTMLDocumentClass();
	WuxiaWorld2 = (mshtml::IHTMLDocument2^)WuxiaWorld;
	WuxiaWorld2->write(Data);

	node = WuxiaWorld->getElementById("content");
	//MessageBox(NULL, msclr::interop::marshal_as<std::string>(node->innerHTML->ToString()).c_str(), "", MB_ICONWARNING);

	delete wc, node, WuxiaWorld, WuxiaWorld2, Data;

	System::Console::WriteLine("Getting Content");
	if (node != nullptr) {
		return node->innerText;
	}
	else {
		System::Console::WriteLine("Node was null, URL: {0}", Chp->Uri);
		return nullptr;
	}
}

System::String^ BookAddForm::BNDownloadChapterContent(Chapter^ Chp)
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}