#include "Window.h"
#include <iostream>
#include <thread>
#include <Dbt.h>	// Device plugging/unplugging


bool CWindow::Create(const uint32_t xPos, const uint32_t yPos, const uint32_t winWidth, const uint32_t winHeight, const std::wstring title)
{
	// Data/params for setup
	m_Width     = winWidth;
	m_Height    = winHeight;
	m_AppTitle  = title;

	WNDCLASSEX wc{ 0 };
	wc.cbSize         = sizeof(WNDCLASSEX);
	wc.style          = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc    = MessageRouter;
	wc.hbrBackground  = HBRUSH(COLOR_WINDOW + 1);
	wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName  = L"CWindow";

	// Register Class
	if (!RegisterClassEx(&wc)) 
	{
		return false;
	}

	RECT rect 
	{
		static_cast<LONG>(xPos),
		static_cast<LONG>(yPos),
		static_cast<LONG>(xPos + m_Width),
		static_cast<LONG>(yPos + m_Height)
	};

	// Create Window
	m_Hwnd = CreateWindowEx(0, wc.lpszClassName, title.c_str(), m_WinStyle, rect.left, rect.top, rect.right, rect.bottom, nullptr,	nullptr, ::GetModuleHandle(nullptr), this);

	if (!m_Hwnd) 
	{
		auto err = GetLastError();
		return false;
	}

	ShowWindow(m_Hwnd, SW_SHOW);

	return true;
}


int CWindow::Run(){

	MSG msg = { nullptr };

	m_mainTimer.Reset();
	m_mainTimer.Start();
	
	while (!m_ExitFlag && msg.message != WM_QUIT) {

		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE) && msg.hwnd != INVALID_HANDLE_VALUE)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else 
		{
			m_mainTimer.Tick();

			float deltaT = m_mainTimer.DeltaTime();
			float worldT = m_mainTimer.TotalTime();

			// Update status
			//UIRenderer::Update(deltaT, worldT);

			// update scene
			// . . .

			// buffer swap
			// . . .
		}
	}

	return static_cast<int>(m_ExitFlag ? 0 : msg.wParam);
}


LRESULT CWindow::MsgProc(HWND const hWnd, UINT const msg, WPARAM const wParam, LPARAM const lParam) 
{
	switch (msg) 
	{

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			break;

		case WM_KEYUP:
			break;

		case WM_MOUSEMOVE:
			break;

		case WM_LBUTTONDOWN:
			break;

		case WM_LBUTTONUP:
			break;

		case WM_RBUTTONDOWN:
			break;

		case WM_RBUTTONUP:
			break;

		case WM_EXITSIZEMOVE:
			break;

		case WM_DEVICECHANGE:
			if (wParam == DBT_DEVICEARRIVAL) 
			{
				// Check for removal of device

			} else if (wParam == DBT_DEVICEREMOVECOMPLETE) 
			{
				// Check for removal of device
			}
			break;

		case WM_PAINT:
			HDC hDC;
			PAINTSTRUCT ps;
			hDC = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return LRESULT();
}


LRESULT CWindow::MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CWindow* window{ nullptr };

	if (msg == WM_CREATE)
	{
		window = reinterpret_cast<CWindow*>(reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams);
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	window = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return window->MsgProc(hWnd, msg, wParam, lParam);
}

