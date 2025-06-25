// ============================
// RagX Engine - IInputManager
// ============================

#ifndef _RAGX_IINPUTMANAGER_
#define _RAGX_IINPUTMANAGER_

#include <Windows.h>
#include "IDestroyable.h"

namespace Input {

    // ----------------------------------------------------------
    // Interface: IInputManager
    // Interface abstrata para gerenciamento de entrada (teclado/mouse)
    // ----------------------------------------------------------
    class IInputManager : public CollectorManager::IDestroyable
    {
    public:
        virtual ~IInputManager() = default;

        // Inicialização e atualização
        virtual void InitAndResetInput() = 0;
        virtual void UpdateInput() = 0;

        // Captura do mouse (modo FPS)
        virtual void SetMouseCaptureWindow(HWND hwnd, int width, int height) = 0;
        virtual void SetMouseCenter(int x, int y) = 0;
        virtual void SetMouseFPSMode(bool enable) = 0;

        // Eventos da janela
        virtual void OnKeyDown(unsigned char key) = 0;
        virtual void OnKeyUp(unsigned char key) = 0;
        virtual void OnMouseMove(int x, int y) = 0;
        virtual void OnMouseButtonDown(int button) = 0;
        virtual void OnMouseButtonUp(int button) = 0;

        // Consome uma tecla (evita que seja detectada novamente com IsKeyPressed)
        virtual void ConsumeKey(unsigned char key) = 0;
        virtual bool IsKeyConsumed(unsigned char key) const = 0;

        // Consome um botão do mouse
        virtual void ConsumeMouseButton(int button) = 0;
        virtual bool IsMouseButtonConsumed(int button) const = 0;

        // Eventos de rolagem do mouse (scroll wheel)
        virtual void OnMouseWheelScroll(int delta) = 0;

        // Consulta do valor do scroll no último frame
        [[nodiscard]] virtual int GetMouseWheelDelta() const = 0;


        // Leitura de estado do teclado
        [[nodiscard]] virtual bool IsKeyHeld(unsigned char key) const = 0;
        [[nodiscard]] virtual bool IsKeyPressed(unsigned char key) const = 0;
        [[nodiscard]] virtual bool IsKeyReleased(unsigned char key) const = 0;

        // Leitura de estado do mouse
        [[nodiscard]] virtual bool IsMouseButtonHeld(int button) const = 0;
        [[nodiscard]] virtual bool IsMouseButtonPressed(int button) const = 0;
        [[nodiscard]] virtual bool IsMouseButtonReleased(int button) const = 0;

        [[nodiscard]] virtual POINT GetMousePosition() const = 0;
        [[nodiscard]] virtual int GetMouseDeltaX() const = 0;
        [[nodiscard]] virtual int GetMouseDeltaY() const = 0;

        virtual void Destroy() = 0;
    };

}

#endif
