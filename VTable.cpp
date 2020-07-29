#include "VTable.h"
#include "Includes.h"
#include "Preferences.h"

VTable::VTable(System::Object ^tableType) {
	TableType = tableType->GetType();
	accessors = gcnew cli::array<System::Object^>(0);
	objects = gcnew cli::array<System::Object^>(0);
}

VTable::VTable(System::Type^ tableType) {
	TableType = tableType;
	accessors = gcnew cli::array<System::Object^>(0);
	objects = gcnew cli::array<System::Object^>(0);
}

VTable::~VTable() {
	accessors->Clear;
	objects->Clear;
}

VTable::VTable(System::Type^ keyType, System::Type^ valueType)
{
	throw gcnew System::NotImplementedException();
}

int VTable::Length() {
	if (accessors->Length != objects->Length)
		std::exception("Integrity check failed on VTable length check");
	return accessors->Length;
}

// unsigned int does not work with this.
System::Object^ VTable::operator()(int index, bool key) {
	if (key) {
		std::cout << "E1: " << msclr::interop::marshal_as<std::string>(objects[0]->ToString()) << std::endl;
		int as = System::Array::IndexOf(accessors, index);
		return objects[index];
	}
	else
		return accessors[System::Array::IndexOf(objects, index)];
}

System::Object^ VTable::operator()(System::Object^ item, bool key) {
	if (key) {
		//MessageBox(NULL, std::string(msclr::interop::marshal_as<std::string>(System::Array::IndexOf(accessors, index).ToString())).c_str(), "Kobei: Preferences", MB_ICONERROR | MB_OK);
		return objects[System::Array::IndexOf(accessors, item)];
	}
	else
		return accessors[System::Array::IndexOf(objects, item)];
}

// Default functionality is to return value paired with key.
System::Object^ VTable::operator()(System::Object^ item) {
		return objects[System::Array::IndexOf(accessors, item)];
}

// If there are not any objects populating the array, create the arrays and populate them.
void VTable::CreateKeyValuePairs(System::Object^ key, System::Object^ item) {
	accessors = gcnew cli::array<System::Object^>(1);
	accessors[0] = key;

	objects = gcnew cli::array<System::Object^>(1);
	objects[0] = item;
}

// Add objects to the array.
void VTable::AddKeyValuePairs(System::Object^ key, System::Object^ item) {
	cli::array<System::Object^>^ tempArray = gcnew cli::array<System::Object^>(objects->Length + 1);
	
	int tLength = objects->Length;

	for (int idx = 0; idx < tLength; idx++) {
		tempArray[idx] = objects[idx];
	}
	
	tempArray[tempArray->Length - 1] = item;
	
	objects = tempArray;

	tempArray = gcnew cli::array<System::Object^>(accessors->Length + 1);

	for (int idx = 0; idx < tLength; idx++) {
		tempArray[idx] = accessors[idx];
	}

	tempArray[tempArray->Length - 1] = key;

	accessors = tempArray;

	delete tempArray;
}

// Add object to array.
void VTable::Add(System::Object^ key, System::Object^ item) {
	if (TableType != item->GetType()) {
		std::exception("Types not the same, and multi-type support is not enabled.");
	}
	if (accessors != nullptr) {
		System::Collections::Generic::List<System::Object^> acs = gcnew System::Collections::Generic::List<System::Object^>(accessors);
		if (acs.Contains(item)) {
			std::exception("Key already exists in VTable!");
		}
		acs.Clear();
		AddKeyValuePairs(key, item);
	}
	else
		CreateKeyValuePairs(key, item);
}

inline bool VTable::ContainsValue(System::Object^ value)
{
	return System::Array::IndexOf(objects, value) != -1;
}

inline bool VTable::ContainsAccessor(System::Object^ value)
{
	return System::Array::IndexOf(accessors, value) != -1;
}

cli::array<System::Object^>^ VTable::GetArray() {
	return objects;
}