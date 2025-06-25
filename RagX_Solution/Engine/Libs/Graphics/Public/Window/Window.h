// ====================
// RagX Engine - Window
// ====================
#ifndef _RAGX_WINDOW_
#define _RAGX_WINDOW_

// ---------
// Includes
// ---------
#include "IInputManager.h"
#include "IWindow.h"

#include <windowsx.h>
#include <functional>
#include <memory>

namespace Graphics
{
	struct WindowInternalState;

	// ------------------------------------------------------
	// Classe Window - Implementa��o da IWindow usando WinAPI.
	// Gerencia cria��o, loop de mensagens e destrui��o da janela.
	// ------------------------------------------------------
	class Window : public IWindow
	{
	public:
		Window();
		~Window();

		void Destroy() override;

		bool ProcessMessages() override;
		bool Create(HINSTANCE hInstance, int width, int height, const std::wstring& title) override;
		[[nodiscard]] bool ShouldClose() const override;

		void UpdateWindowTitle(const std::wstring& title) override;

		void ConnectInputSystem(Input::IInputManager* inputSystem);

	private:
		Input::IInputManager* input = nullptr;
		using InputCallback = std::function<void(UINT, WPARAM, LPARAM)>;
		InputCallback inputCallback;
		void SetInputCallback(InputCallback callback);

		// WndProc est�tica necess�ria para CreateWindowEx
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// WndProc real associada ao objeto Window
		LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// Estado interno da janela (resolu��o, HWND, modo, etc.)
		std::unique_ptr<WindowInternalState> WinInternal;
	};
}

#endif
