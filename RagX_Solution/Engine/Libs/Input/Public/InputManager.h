// ============================
// RagX Engine - InputManager
// ============================

#ifndef _RAGX_INPUTMANAGER_
#define _RAGX_INPUTMANAGER_

//---------
// Includes
//---------
#include "IInputManager.h"
#include "InputTypes.h"

#include <Windows.h>
#include <array>

namespace Input
{
    // ------------------------------------------------------------------------
    // Classe: InputManager
    // Respons�vel por gerenciar o estado do teclado e mouse em tempo real.
    // Captura de eventos via WinAPI (OnKeyDown, OnMouseMove, etc)
    // ------------------------------------------------------------------------
    class InputManager : public IInputManager
    {
    public:
        InputManager();
        ~InputManager() override;

        // Inicializa��o
        void InitAndResetInput() override;

        // Atualiza��o por frame (transi��es + delta do mouse)
        void UpdateInput() override;

        // Define janela e centro da �rea de captura para modo FPS
        void SetMouseCaptureWindow(HWND hwnd, int width, int height) override;
        void SetMouseCenter(int x, int y) override;
        void SetMouseFPSMode(bool enable) override;

        // Eventos da WinAPI (chamados pelo Window)
        void OnKeyDown(unsigned char key) override;
        void OnKeyUp(unsigned char key) override;
        void OnMouseMove(int x, int y) override;
        void OnMouseButtonDown(int button) override;
        void OnMouseButtonUp(int button) override;

        // Consome uma tecla (evita que seja detectada novamente com IsKeyPressed)
        void ConsumeKey(unsigned char key) override;
        bool IsKeyConsumed(unsigned char key) const override;

        // Consome um bot�o do mouse
        void ConsumeMouseButton(int button) override;
        bool IsMouseButtonConsumed(int button) const override;

        void OnMouseWheelScroll(int delta) override;
        [[nodiscard]] int GetMouseWheelDelta() const override;

        // -------- Leitura do Teclado -------- //
        [[nodiscard]] bool IsKeyHeld(unsigned char key) const override;
        [[nodiscard]] bool IsKeyPressed(unsigned char key) const override;
        [[nodiscard]] bool IsKeyReleased(unsigned char key) const override;

        // -------- Leitura do Mouse -------- //
        [[nodiscard]] bool IsMouseButtonHeld(int button) const override;
        [[nodiscard]] bool IsMouseButtonPressed(int button) const override;
        [[nodiscard]] bool IsMouseButtonReleased(int button) const override;

        [[nodiscard]] POINT GetMousePosition() const override;
        [[nodiscard]] int GetMouseDeltaX() const override;
        [[nodiscard]] int GetMouseDeltaY() const override;

        // Limpeza (CollectorManager)
        void Destroy() override;

    private:
        bool fpsMouseModeEnable;
        int mouseWheelDelta;

        // -------- Estado do Teclado -------- //
        std::array<bool, Input::KEY_COUNT> currentKeys{};
        std::array<bool, Input::KEY_COUNT> previousKeys{};
        std::array<bool, Input::KEY_COUNT> keyPressed{};
        std::array<bool, Input::KEY_COUNT> keyReleased{};
        std::array<bool, Input::KEY_COUNT> keyConsumed{};

        // -------- Estado do Mouse (m�x. 5 bot�es) -------- //
        std::array<bool, Input::MOUSE_COUNT> currentMouseButton{};
        std::array<bool, Input::MOUSE_COUNT> previousMouseButton{};
        std::array<bool, Input::MOUSE_COUNT> mouseButtonPressed{};
        std::array<bool, Input::MOUSE_COUNT> mouseButtonReleased{};
        std::array<bool, Input::MOUSE_COUNT> mouseButtonConsumed{};

        // -------- Posi��o e delta do mouse -------- //
        POINT mousePosition{};
        POINT lastMousePosition{};
        int mouseDeltaX;
        int mouseDeltaY;

        // -------- Centro da �rea ativa de captura -------- //
        int centerX;
        int centerY;

        // -------- Janela onde o mouse ser� recentralizado (modo FPS) -------- //
        HWND targetWindow;
    };

}

#endif
