// ====================
// RagX Engine - Window
// ====================
#ifndef _RAGX_WINDOW_INTERNAL_
#define _RAGX_WINDOW_INTERNAL_

#include <Windows.h>
#include "WindowMode.h"

namespace Graphics
{
	// Nome padrão da classe de janela registrada na WinAPI
	constexpr auto WINDOW_CLASS_NAME = L"RAGX_WINDOW_CLASS";

	// -----------------------------------------------
	// Estrutura interna da janela, usada pela classe Window.
	// Contém todos os dados que definem o estado atual da janela.
	// -----------------------------------------------
	struct WindowInternalState
	{
		// Define o estilo padrão da janela (sem maximizar, sem redimensionar)
		static DWORD GetDefaultWindowStyle()
		{
			DWORD style = WS_OVERLAPPEDWINDOW;
			style &= ~WS_MAXIMIZEBOX;
			style &= ~WS_THICKFRAME;
			return style;
		}

		HINSTANCE hInstance;
		HWND hwnd;
		int width, height;
		float centerX, centerY;
		bool shouldClose;
		WindowMode mode;
	};
}

#endif
