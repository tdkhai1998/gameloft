#include "videoDriver.h"

VideoDriver* VideoDriver::s_Instance = NULL;

static Gdiplus::Bitmap*				g_MemoryDevice;
static Gdiplus::Graphics*			g_MemoryGraphic;

static Gdiplus::Graphics*			g_Graphic;
static HWND							g_HWND;

static Gdiplus::GdiplusStartupInput	g_gdiplusStartupInput;
static ULONG_PTR					g_gdiplusToken;

static Gdiplus::Pen* m_Pen;
static Gdiplus::SolidBrush* m_SolidBrush;

VideoDriver::VideoDriver()
{
	
}

VideoDriver::~VideoDriver()
{
	delete g_Graphic;
	delete g_MemoryDevice;
	Gdiplus::GdiplusShutdown(g_gdiplusToken);
}

void VideoDriver::Init(HWND hWnd)
{
	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);
	g_HWND = hWnd;
	g_Graphic = new Gdiplus::Graphics(GetDC(hWnd));
	m_Pen = new Gdiplus::Pen(Color(0, 0, 255));
	m_SolidBrush = new Gdiplus::SolidBrush(Color(0, 0, 255));
	GetWindowRect(g_HWND, &rect);

	g_MemoryDevice = new Gdiplus::Bitmap(SCREEN_W, SCREEN_H);
	g_MemoryGraphic = Gdiplus::Graphics::FromImage(g_MemoryDevice);

	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;
}

VideoDriver* VideoDriver::GetInstance()
{
	if (s_Instance == NULL)
	{
		s_Instance = new VideoDriver();
	}
	return s_Instance;
}

void VideoDriver::FillRect(int x, int y, int width, int height)
{
	// FILL RECTANGLE
	//g_Graphic->FillRectangle(m_SolidBrush, x, y, width, height);
	g_MemoryGraphic->FillRectangle(m_SolidBrush, x, y, width, height);
}

void VideoDriver::DrawRect(int x, int y, int width, int height, int weight)
{
	// DRAW RECTANGLE
	g_MemoryGraphic->DrawRectangle(m_Pen, x, y, width, height);
}

void VideoDriver::DrawCircle(int cx, int cy, int width, int height)
{
	// DRAW ELLIPSE
	g_MemoryGraphic->DrawEllipse(m_Pen, cx, cy, width, height);
};

void VideoDriver::FillCircle(int cx, int cy, int radius)
{
	// FILL ELLIPSE
	g_MemoryGraphic->FillEllipse(m_SolidBrush, cx - radius, cy - radius, radius * 2, radius * 2);

};

void VideoDriver::DrawLine(float x1, float y1, float x2, float y2)
{
	/* ----------    LINE    ---------- */
	g_MemoryGraphic->DrawLine(m_Pen, x1, y1, x2, y2);
}

void DrawImage(LPWSTR fileName, int x, int y, int width, int height)
{
	Image image(fileName);
	Rect destRect(x, y, width, height);
	g_MemoryGraphic->DrawRectangle(m_Pen, destRect);
	g_MemoryGraphic->DrawImage(&image, destRect);
}

void DrawImage(LPWSTR fileName, int x, int y)
{
	Image image(fileName);
	g_MemoryGraphic->DrawImage(&image, x, y);
}

void VideoDriver::Render()
{
	if (g_Graphic != NULL)
	{
		GetWindowRect(g_HWND, &rect);
		g_Graphic->DrawImage(g_MemoryDevice, 0, 0, SCREEN_W, SCREEN_H);
	}
}

void VideoDriver::SetColor(unsigned int _color)
{
	color[0] = ((_color >> 16) & 0xFF) / 255.0f;
	color[1] = ((_color >> 8) & 0xFF) / 255.0f;
	color[2] = ((_color)& 0xFF) / 255.0f;

	color[3] = ((_color >> 24) / 255.0f);
	if (color[3] == 0.0f)
		color[3] = 1.0f;

	m_Pen->SetColor(Gdiplus::Color(color[0], color[1], color[2]));
}

void VideoDriver::CleanScreen()
{
	g_MemoryGraphic->Clear(Gdiplus::Color(0, 0, 0));
}