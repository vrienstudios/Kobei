#pragma once
#include "Includes.h"
#include "Vpanel.h"
ref class VolumeCollapsible : System::Windows::Forms::Panel {
private:
	VTable^ Volumes;
	VTable^ CollapsibleControls;
	int selChapter;
	Volume^ selVolume;
public:
	void AnimateOpen(VPanel^& panel);
	void AnimateClose(VPanel^& panel);
	VolumeCollapsible(VTable^ volumeList);
	VolumeCollapsible(cli::array<Volume^>^ volumeList);
	void GenerateControls();
	void OnPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	void OnScroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e);
	void OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	void CardMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);


	delegate void EventHandler(VolumeCollapsible^ sender, System::EventArgs^ e, unsigned int i, Volume^ vol);
	virtual void ExecuteEvent(VolumeCollapsible^ sender, System::EventArgs^ e, unsigned int i, Volume^ vol);
	event EventHandler^ TriggerChapterOpen;

	property bool ChapterFlag {
		void set(bool value) {
			ExecuteEvent(this, System::EventArgs::Empty, selChapter, selVolume);
		}
	};
};