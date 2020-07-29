#pragma once

ref class Resources {
private:
	static System::Reflection::Assembly^ assembly;
	static System::IO::Stream^ stream;
	//Resources();
	//~Resources();
public:
	static void LoadResourceSystem();
	static void DisposeResourceSystem();
	static System::IO::Stream^ GetObject(System::String^ resourceName);
};