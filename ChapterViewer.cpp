#include "ChapterViewer.h"

ChapterView::ChapterView()
{
	chapterBuffer = gcnew VTable(Chapter::typeid);
}