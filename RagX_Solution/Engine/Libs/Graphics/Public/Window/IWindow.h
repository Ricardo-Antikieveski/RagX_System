// =====================
// RagX Engine - IWindow
// =====================
#ifndef _RAGX_IWINDOW_
#define _RAGX_IWINDOW_

// ---------
// Includes
// ---------
#include "IDestroyable.h"
#include "WindowMode.h"
#include <Windows.h>
#include <string>

namespace Graphics
{
	// -----------------------------------------------
	// Interface base da janela, usada pela engine para 
	// comunicação desacoplada entre subsistemas e o Window.
	// -----------------------------------------------
	class IWindow : public CollectorManager::IDestroyable
	{
	public:
		virtual ~IWindow() = default;

		// Cria a janela principal da aplicação
		virtual bool Create(HINSTANCE hInstance, int width, int height, const std::wstring& title) = 0;

		// Processa as mensagens da fila de eventos do Windows
		virtual bool ProcessMessages() = 0;

		// Indica se a janela foi sinalizada para fechamento
		[[nodiscard]] virtual bool ShouldClose() const = 0;

		// Libera recursos relacionados à janela
		virtual void Destroy() override = 0;

		// Altera o titulo da janela
		virtual void UpdateWindowTitle(const std::wstring& title) = 0;
		
		// Conecta a instancia criada do Input na Engine com esse ponteiro
		virtual void ConnectInputSystem(Input::IInputManager* inputSystem) = 0;
	};
}

#endif
