
#include <tchar.h>
#include <Windows.h>
#include "CELLWinApp.hpp"


int CALLBACK _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInst);
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);
	CELL::CELLWinApp  app(hInstance);
	app.main(800, 600);
	return  0;
}