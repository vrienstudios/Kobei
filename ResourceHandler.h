#pragma once

ref class Resources {
private:
	System::Reflection::Assembly^ assembly;
	System::IO::Stream^ stream;

	Resources();
	~Resources();
public:
	System::Object^ GetObject(System::String^ resourceName);
};