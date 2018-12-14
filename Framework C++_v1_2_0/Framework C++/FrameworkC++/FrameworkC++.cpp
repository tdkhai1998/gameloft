// FrameworkC++.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "render\define.h"
#include "FrameworkC++.h"
#include "Application.h"

#define MAX_LOADSTRING 100

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application *win = new Application(SCREEN_W, SCREEN_H);
	win->Init(hInstance);
	win->Run();

	return 0;
}