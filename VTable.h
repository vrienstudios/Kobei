#pragma once
#include <iostream>
#include <vector>

ref class VTable {
private:
	// Table type.
	System::Type^ TableType;
	System::Type^ AccessorType;
	System::Type^ ValueType;


	//Keys and value arrays.
	cli::array<System::Object^>^ accessors;
	cli::array<System::Object^>^ objects;

	//Create/Add KeyValue Pair
	void CreateKeyValuePairs(System::Object^ key, System::Object^ item);
	void AddKeyValuePairs(System::Object^ key, System::Object^ item);

public:
	//Constructors and destructor.
	VTable(System::Object ^tableType);
	VTable(System::Type ^tableTyoe);
	VTable(System::Type^ keyType, System::Type^ valueType);

	virtual ~VTable();

	System::Object^ operator()(int index, bool key);
	System::Object^ operator()(System::Object^ item, bool key);
	System::Object^ operator()(System::Object^ item);
	System::Object^ operator()(int location, System::Object^ newobj);

	bool ContainsAccessor(System::Object^ value);
	bool ContainsValue(System::Object^ value);

	int Length();

	void Add(System::Object^ key, System::Object^ item);

	cli::array<System::Object^>^ GetArray();

};