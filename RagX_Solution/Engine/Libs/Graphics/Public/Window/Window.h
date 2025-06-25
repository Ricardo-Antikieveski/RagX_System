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
	// Classe Window - Implementação da IWindow usando WinAPI.
	// Gerencia criação, loop de mensagens e destruição da janela.
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

		// WndProc estática necessária para CreateWindowEx
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// WndProc real associada ao objeto Window
		LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// Estado interno da janela (resolução, HWND, modo, etc.)
		std::unique_ptr<WindowInternalState> WinInternal;
	};
}

#endif
