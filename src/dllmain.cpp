#include<thread>

#include<Windows.h>

#include "client/client.hpp"

// Definição, meu pau na sua mão
bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		std::thread{Client::Init, instance}.detach();
	}

	return true;
}
