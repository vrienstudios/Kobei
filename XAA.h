#pragma once

#include "Functions.h"
#include "Includes.h"
#include <regex>
#include <algorithm>

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

	//https://www.youtube.com/watch?v=42iqg_UFORA
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
			case Functions::SwitchString("System.Collections.Generic.List`1[System.String]"): {
				std::regex r("[(.*?)]");
				std::smatch ma;
				std::string atemp = msclr::interop::marshal_as<std::string>(tokenSplit[1]->ToString());
				System::Collections::Generic::List<System::String^>^ tmp = gcnew System::Collections::Generic::List<System::String^>();
				while(std::regex_search(atemp, ma, r)){ // Why regex will no longer take a "temporary" string as a parameter, I will not know.
					tmp->Add(msclr::interop::marshal_as<System::String^>(ma.str(0)));
				}
				clss->GetField(tokenSplit[0])->SetValue(m, tmp);
				delete tmp;
				break;
			}
			case Functions::SwitchString("System.Collections.Generic.List`1[System.Int32]"): {
				std::regex r("[(.*?)]");
				std::smatch ma;
				std::string atemp = msclr::interop::marshal_as<std::string>(tokenSplit[1]->ToString());
				System::Collections::Generic::List<System::Int32>^ tmp = gcnew System::Collections::Generic::List<System::Int32>();
				while (std::regex_search(atemp, ma, r)) { // Why regex will no longer take a "temporary" string as a parameter, I will not know.
					tmp->Add(System::Int32::Parse(msclr::interop::marshal_as<System::String^>(ma.str(0))));
				}
				clss->GetField(tokenSplit[0])->SetValue(m, tmp);
				delete tmp;
				break;
			}
			}
			delete tokenSplit;
		}
		return m;
	}
};