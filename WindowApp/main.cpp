#include "Window.h"

int main(int argc, char** argv)
{
	CWindow win(200, 200, 1280, 720, L"My window");

	if (win.IsInitialized())
	{
		win.Run();
	}

	return 0;
}
