#include<Windows.h>

#include "client/client.hpp"

// Definição, meu pau na sua mão
bool __stdcall DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);
		
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Client::Init), instance, 0, nullptr);
	}

	return true;
}
