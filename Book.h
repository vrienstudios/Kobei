#pragma once

#include "VTable.h"
ref struct Book {
public:
	Book(System::Drawing::Bitmap^ cover, System::String^ title, System::String^ Author, System::String^ lastUpdated);
	Book(const Book% book);
	~Book();

	System::Drawing::Bitmap^ Cover;
	System::String^ Title;
	System::String^ Author;
	System::String^ UpdateTime;
	System::String^ Summary;
	System::String^ Directory;


	int Ranking;
	int CurrentChapter;
	int numChapters;
	bool HasVolume;
	VTable^ Volumes;
	VTable^ Chapters;
	float ReadPercentage;
	long ReadingTime;

	static Book^ ParseBook(System::String^ bookfolder);

	bool Update();

	static Book^ Update(Book^ book);

	void VolumeUpdate();
	void FreeVolumeMem() {

	}
};