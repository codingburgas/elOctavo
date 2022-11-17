#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h";
#include "../Header files/Menu.h";
#include "../Header files/Additional Functions.h";

#define _WIN32_WINNT 0x0500
#include <windows.h>

void hideConsole()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
}

int main()
{
	hideConsole();

	RenderWindow window(VideoMode(1280, 720), "The legend of Kurabirov", Style::Titlebar | Style::Close);

	setupMenu(window);
}

