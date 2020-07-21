#include "ResourceHandler.h"

Resources::Resources() {
	throw gcnew System::NotImplementedException();
}

Resources::~Resources() {
	delete assembly;
	delete stream;
}

System::Object^ Resources::GetObject(System::String^ resourceName)
{
	throw gcnew System::NotImplementedException();
	// TODO: insert return statement here
}