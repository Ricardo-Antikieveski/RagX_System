// ====================
// RagX Engine - Window
// ====================

// ---------
// Includes
// ---------
#include "LoggerMacros.h"
#include "Window.h"
#include "WindowInternal.h"

namespace Graphics
{
	// -------------------------------
	// Construtor - inicializa estado interno
	// -------------------------------
	Window::Window()
		: WinInternal(std::make_unique<WindowInternalState>())
	{
		WinInternal->hInstance = nullptr;
		WinInternal->hwnd = nullptr;
		WinInternal->width = 0;
		WinInternal->height = 0;
		WinInternal->centerX = 0;
		WinInternal->centerY = 0;
		WinInternal->shouldClose = false;
		WinInternal->mode = WindowMode::WINDOWED;
	}

	Window::~Window() = default;

	// ----------------------------------
	// Liberação de recursos e fechamento
	// ----------------------------------
	void Window::Destroy()
	{
		if (WinInternal->hInstance)
		{
			WinInternal->shouldClose = true;
			DestroyWindow(WinInternal->hwnd);
			WinInternal->hwnd = nullptr;

			if (WinInternal->hInstance)
				UnregisterClass(WINDOW_CLASS_NAME, WinInternal->hInstance);
		}

		LOG_INFO_F(L"[Engine_System] Destroy chamado.");
	}

	// -------------------------------------------------------------------
	// Cria a janela principal da aplicação com as configurações básicas
	// -------------------------------------------------------------------
	bool Window::Create(HINSTANCE instance, int w, int h, const std::wstring& title)
	{
		WinInternal->hInstance = instance;
		WinInternal->width = w;
		WinInternal->height = h;
		WinInternal->centerX = static_cast<float>(w) / 2.0f;
		WinInternal->centerY = static_cast<float>(h) / 2.0f;

		WNDCLASS wc = {};
		wc.lpfnWndProc = StaticWndProc;
		wc.hInstance = WinInternal->hInstance;
		wc.lpszClassName = WINDOW_CLASS_NAME;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);

		if (!RegisterClass(&wc))
		{
			LOG_INFO_F(L"[Engine_System] Falha ao registrar a classe da janela.");
			return false;
		}

		DWORD style = WinInternal->GetDefaultWindowStyle();
		RECT rect = { 0, 0, WinInternal->width, WinInternal->height };
		AdjustWindowRect(&rect, style, FALSE);

		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		WinInternal->hwnd = CreateWindowEx(
			0,
			WINDOW_CLASS_NAME,
			title.c_str(),
			style,
			CW_USEDEFAULT, CW_USEDEFAULT,
			windowWidth, windowHeight,
			nullptr, nullptr,
			WinInternal->hInstance,
			this
		);

		if (!WinInternal->hwnd)
			return false;

		ShowWindow(WinInternal->hwnd, SW_SHOW);
		return true;
	}

	// --------------------------------------------------------------------
	// Processa as mensagens da fila do Windows (input, redraw, etc.)
	// --------------------------------------------------------------------
	bool Window::ProcessMessages()
	{
		MSG msg = {};
		while (PeekMessage(&msg, WinInternal->hwnd, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				LOG_INFO_F(L"[Engine_System] Cliente requisitou WM_QUIT");
				WinInternal->shouldClose = true;
				return false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return true;
	}

	// ----------------------------------------------------------
	// Retorna se a janela recebeu sinal de fechamento (WM_QUIT)
	// ----------------------------------------------------------
	bool Window::ShouldClose() const
	{
		return WinInternal->shouldClose;
	}

	// ----------------------------------------------------------------
	// Função WndProc estática - redireciona chamadas para o objeto real
	// ----------------------------------------------------------------
	LRESULT CALLBACK Window::StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_NCCREATE)
		{
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
		}

		Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (window)
			return window->WndProc(hwnd, msg, wParam, lParam);

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	// -----------------------------------------------
	// Manipulação de mensagens específicas da janela
	// -----------------------------------------------
	LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			// Mensagens de teclado
		case WM_KEYDOWN:
		case WM_KEYUP:
			// Mensagens de mouse
		case WM_MOUSEMOVE:	 case WM_MOUSEWHEEL:
		case WM_LBUTTONDOWN: case WM_LBUTTONUP:
		case WM_RBUTTONDOWN: case WM_RBUTTONUP:
		case WM_MBUTTONDOWN: case WM_MBUTTONUP:
			if (inputCallback)
				inputCallback(msg, wParam, lParam);
			break;
		}

		if (msg == WM_DESTROY)
		{
			WinInternal->shouldClose = true;
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	// -----------------------------------------------
	// Manipulação do título da janela
	// -----------------------------------------------
	void Window::UpdateWindowTitle(const std::wstring& title)
	{
		SetWindowText(WinInternal->hwnd, title.c_str());
	}

	// -----------------------------------------------
	// Define função lambda de input para uso no WndProc
	// -----------------------------------------------
	void Window::SetInputCallback(InputCallback callback)
	{
		inputCallback = std::move(callback);
	}

	// -----------------------------------------------
	// Faz a conexão de uma instância do input manager
	// -----------------------------------------------
	void Window::ConnectInputSystem(Input::IInputManager* inputSystem)
	{
		if (input != nullptr)
		{
			LOG_INFO_F(L"[Engine_System] ConnectInputSystem já foi chamado anteriormente.");
			return;
		}

		input = inputSystem;

		SetInputCallback([inputSystem](UINT msg, WPARAM wParam, LPARAM lParam)
			{
				if (!inputSystem) return;
				switch (msg)
				{
				case WM_KEYDOWN:         inputSystem->OnKeyDown(static_cast<unsigned char>(wParam)); break;
				case WM_KEYUP:           inputSystem->OnKeyUp(static_cast<unsigned char>(wParam)); break;
				case WM_MOUSEMOVE:       inputSystem->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)); break;
				case WM_LBUTTONDOWN:     inputSystem->OnMouseButtonDown(0); break;
				case WM_LBUTTONUP:       inputSystem->OnMouseButtonUp(0); break;
				case WM_RBUTTONDOWN:     inputSystem->OnMouseButtonDown(1); break;
				case WM_RBUTTONUP:       inputSystem->OnMouseButtonUp(1); break;
				case WM_MBUTTONDOWN:     inputSystem->OnMouseButtonDown(2); break;
				case WM_MBUTTONUP:       inputSystem->OnMouseButtonUp(2); break;
				case WM_XBUTTONDOWN:     inputSystem->OnMouseButtonDown((GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4); break;
				case WM_XBUTTONUP:       inputSystem->OnMouseButtonUp((GET_XBUTTON_WPARAM(wParam) == XBUTTON1) ? 3 : 4); break;
				case WM_MOUSEWHEEL:		 inputSystem->OnMouseWheelScroll(GET_WHEEL_DELTA_WPARAM(wParam)); break;
				}
			});
	}
}
