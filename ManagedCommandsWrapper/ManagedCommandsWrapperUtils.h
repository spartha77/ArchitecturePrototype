#pragma once
#include <string>
using namespace System;

namespace ManagedCommandsWrapper {

	void MarshalString(System::String^ s, std::string& os);
	void MarshalString(System::String^ s, std::wstring& os);
}
