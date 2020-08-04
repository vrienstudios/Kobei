#pragma once

#include "Functions.h"
#include "Includes.h"
struct XAA {
	System::String^ DeSerialize(System::Object^ clss) {
		System::Type^ t = clss->GetType();
		cli::array<System::Reflection::FieldInfo^>^ pi = t->GetFields();
		System::Text::StringBuilder^ sBuilder = gcnew System::Text::StringBuilder();
		sBuilder->AppendLine(("<" + t->Name + ">"));
		for (int idx = 0; idx < pi->Length; idx++)
			sBuilder->AppendLine(pi[idx]->Name + ":" + pi[idx]->GetValue(clss)->ToString());
		sBuilder->AppendLine(("</" + t->Name + ">"));
		return sBuilder->ToString();
	}

	System::Object^ Serialize(cli::array<System::String^>^ xaa, System::Type^ clss) {
		System::Object^ m = System::Activator::CreateInstance(clss);
		for (int idx = 1; idx < xaa->Length - 2; idx++) {
			cli::array<System::String^>^ tokenSplit = xaa[idx]->Split(':');
			switch (Functions::SwitchString(msclr::interop::marshal_as<std::string>(clss->GetField(tokenSplit[0])->FieldType->ToString()).c_str())) {
			case Functions::SwitchString("System.Int32"): {
				clss->GetField(tokenSplit[0])->SetValue(m, System::Int32::Parse(tokenSplit[1]));
				break;
			}
			case Functions::SwitchString("System.String"): {
				clss->GetField(tokenSplit[0])->SetValue(m, tokenSplit[1]);
				break;
			}
			}

		}
	}
};