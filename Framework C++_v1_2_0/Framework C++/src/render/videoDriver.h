#ifndef __VIDEO_DRIVER_H__
#define __VIDEO_DRIVER_H__

#include "define.h"
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class VideoDriver
{
private:
	float color[4];
	RECT rect;
	static VideoDriver* s_Instance;


public:

	VideoDriver(void);
	~VideoDriver(void);

	void Init(HWND hWnd);
	void Render();
	void DrawRect(int x, int y, int width, int height, int weight = 1);
	void FillRect(int x, int y, int width, int height);
	void DrawCircle(int cx, int cy, int width, int height);
	void FillCircle(int cx, int cy, int radius);
	void DrawLine(float x1, float y1, float x2, float y2);

	void SetColor(unsigned int color);
	void CleanScreen();

	static VideoDriver* GetInstance();
};

#endif