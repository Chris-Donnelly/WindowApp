
#include "Window.h"

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#include <Windows.h>

void mainLogic(float delta)
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CWindow win(200, 200, 1280, 720, L"My window", mainLogic);

	if (win.IsInitialized())
	{
		win.Run();
	}
	return 0;
}
