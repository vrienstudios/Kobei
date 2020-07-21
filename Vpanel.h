#pragma once
#include "Volume.h"
#include "Chapter.h"

ref struct VPanel : System::Windows::Forms::Panel {
public:
	Volume^ Vol;
	Chapter^ Chp;
	BOOLEAN VolChp = FALSE;
	BOOLEAN OpenClose;
	INT Index;
};