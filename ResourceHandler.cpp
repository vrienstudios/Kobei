#include "ResourceHandler.h"

void Resources::LoadResourceSystem() {
	assembly = System::Reflection::Assembly::GetExecutingAssembly();
	return;
}

void Resources::DisposeResourceSystem() {
	delete assembly;
	delete stream;
	return;
}

System::IO::Stream^ Resources::GetObject(System::String^ resourceName)
{
	stream = assembly->GetManifestResourceStream(resourceName);
	return stream;
}