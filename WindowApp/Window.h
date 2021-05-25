#pragma once

#include <windows.h>
#include <string>
#include "Timer.h"

using namespace std;

class CWindow {

	public:

		CWindow(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, std::wstring title)
			: m_Width(0), m_Height(0), m_isWindowInitialized(false), m_ExitFlag(false), m_fTimeScale(1.0f), m_Hwnd(0)
		{
			m_isWindowInitialized = Create(xPos, yPos, width, height, title);
		}

		int Run();

		CWindow(const CWindow&) = delete;
		CWindow& operator=(const CWindow&) = delete;

		inline float GetTimeScale() 
		{ 
			return m_fTimeScale; 
		}

		inline void SetTimeScale(float const ftScale)
		{
			m_fTimeScale = ftScale; 
		}

		inline void Show(bool flag) 
		{ 
			ShowWindow(m_Hwnd, flag); 
		}

		inline const bool IsInitialized () const
		{
			return m_isWindowInitialized;
		}

	private:

		LRESULT CALLBACK         MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK  MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		bool                     Create(const uint32_t xPos, const uint32_t yPos, const uint32_t winWidth, const uint32_t winHeight, const std::wstring title);

		int     m_Width;
		int     m_Height;
		bool    m_isWindowInitialized;
		bool    m_ExitFlag;
		float   m_fTimeScale;
		HWND    m_Hwnd;
		wstring m_AppTitle;
		Timer   m_mainTimer;

		static constexpr DWORD m_WinStyles_Enabled   = { WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE | CS_HREDRAW | CS_VREDRAW };
		static constexpr DWORD m_WinStyles_Disabled  = { WS_MAXIMIZEBOX };
		static constexpr DWORD m_WinStyle            = {  m_WinStyles_Enabled & ~m_WinStyles_Disabled };
};

