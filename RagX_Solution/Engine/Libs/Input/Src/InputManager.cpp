// ============================
// RagX Engine - InputManager
// ============================

//---------
// Includes
//---------
#include "InputManager.h"
#include "LoggerMacros.h"

#include <string>

namespace Input
{
    // --------------------------------------------------
    // Utilitários internos (somente debug)
    // --------------------------------------------------

#ifdef _DEBUG
    // Converte o código da tecla em nome legível (ex: "W", "Espaço")
    static std::wstring GetKeyName(unsigned char key)
    {
        BYTE keyboardState[256] = {};
        if (!GetKeyboardState(keyboardState)) return L"Desconhecida";

        UINT scanCode = MapVirtualKey(key, MAPVK_VK_TO_VSC);
        WCHAR buffer[64] = {};
        LONG lParam = (scanCode << 16);

        if (key == VK_LEFT || key == VK_RIGHT || key == VK_UP || key == VK_DOWN ||
            key == VK_HOME || key == VK_END || key == VK_INSERT || key == VK_DELETE ||
            key == VK_PRIOR || key == VK_NEXT)
            lParam |= (1 << 24); // Estende bit extra para essas teclas especiais

        int result = GetKeyNameTextW(lParam, buffer, 64);
        return (result > 0) ? std::wstring(buffer) : L"Desconhecida";
    }

    // Retorna o nome legível de um botão do mouse
    static std::wstring GetMouseButtonName(int button)
    {
        switch (button)
        {
        case 0: return L"Botão Esquerdo";
        case 1: return L"Botão Direito";
        case 2: return L"Botão do Meio";
        case 3: return L"Botão Extra 1";
        case 4: return L"Botão Extra 2";
        default: return L"Desconhecido";
        }
    }
#endif

    // --------------------------------------------------
    // Construtor / Destrutor
    // --------------------------------------------------

    InputManager::InputManager()
    {
        InitAndResetInput();
    }

    InputManager::~InputManager() = default;

    void InputManager::Destroy()
    {
#ifdef _DEBUG
        LOG_INFO_F(L"[Engine_System][RagX System Input] InputManager destruído e estados das teclas resetados.");
#endif
        InitAndResetInput();
    }

    // --------------------------------------------------
    // Inicialização ou Reset de todos os dados
    // --------------------------------------------------

    void InputManager::InitAndResetInput()
    {
        fpsMouseModeEnable = false;
        targetWindow = nullptr;

        // Zera todos os estados das teclas e botões
        currentKeys.fill(false);
        previousKeys.fill(false);
        keyPressed.fill(false);
        keyReleased.fill(false);
        keyConsumed.fill(false);

        currentMouseButton.fill(false);
        previousMouseButton.fill(false);
        mouseButtonPressed.fill(false);
        mouseButtonReleased.fill(false);
        mouseButtonConsumed.fill(false);

        mousePosition = { 0, 0 };
        lastMousePosition = { 0, 0 };
        mouseDeltaX = mouseDeltaY = mouseWheelDelta = 0;
        centerX = centerY = 0;
    }

    // --------------------------------------------------
    // Atualização por frame
    // Detecta transições (press/release) e delta do mouse
    // --------------------------------------------------

    void InputManager::UpdateInput()
    {
        // Detecta teclas pressionadas e liberadas neste frame
        for (int i = 0; i < Input::KEY_COUNT; i++)
        {
            keyPressed[i] = !previousKeys[i] && currentKeys[i];
            keyReleased[i] = previousKeys[i] && !currentKeys[i];
            if (keyPressed[i]) keyConsumed[i] = false;
        }

        // Detecta botões do mouse pressionados/liberados
        for (int i = 0; i < Input::MOUSE_COUNT; i++)
        {
            mouseButtonPressed[i] = !previousMouseButton[i] && currentMouseButton[i];
            mouseButtonReleased[i] = previousMouseButton[i] && !currentMouseButton[i];
            if (mouseButtonPressed[i]) mouseButtonConsumed[i] = false;
        }

        // Se modo FPS está ativo, calcula o delta e centraliza o cursor
        if (fpsMouseModeEnable && targetWindow)
        {
            POINT currentPos;
            GetCursorPos(&currentPos);
            ScreenToClient(targetWindow, &currentPos);

            mouseDeltaX = currentPos.x - centerX;
            mouseDeltaY = currentPos.y - centerY;

            POINT centerPos = { centerX, centerY };
            ClientToScreen(targetWindow, &centerPos);
            SetCursorPos(centerPos.x, centerPos.y);

            mousePosition = { centerX, centerY };
        }
        else
        {
            mouseDeltaX = 0;
            mouseDeltaY = 0;
        }

        lastMousePosition = mousePosition;

        // Armazena o estado atual como anterior para o próximo frame
        previousKeys = currentKeys;
        previousMouseButton = currentMouseButton;
        mouseWheelDelta = 0;
    }

    // --------------------------------------------------
    // Eventos da WinAPI recebidos via WndProc
    // --------------------------------------------------

    void InputManager::OnKeyDown(unsigned char key)
    {
        currentKeys[key] = true;
#ifdef _DEBUG
        LOG_INFO_F(L"[Engine_Input] KeyDown: %s (%d)", GetKeyName(key).c_str(), key);
#endif
    }

    void InputManager::OnKeyUp(unsigned char key)
    {
        currentKeys[key] = false;
#ifdef _DEBUG
        LOG_INFO_F(L"[Engine_Input] KeyUp: %s (%d)", GetKeyName(key).c_str(), key);
#endif
    }

    void InputManager::OnMouseMove(int x, int y)
    {
        mousePosition = { x, y };
    }

    void InputManager::OnMouseButtonDown(int button)
    {
        if (button >= 0 && button < Input::MOUSE_COUNT)
        {
            currentMouseButton[button] = true;
#ifdef _DEBUG
            LOG_INFO_F(L"[Engine_Input] MouseDown: %s", GetMouseButtonName(button).c_str());
#endif
        }
    }

    void InputManager::OnMouseButtonUp(int button)
    {
        if (button >= 0 && button < Input::MOUSE_COUNT)
        {
            currentMouseButton[button] = false;
#ifdef _DEBUG
            LOG_INFO_F(L"[Engine_Input] MouseUp: %s", GetMouseButtonName(button).c_str());
#endif
        }
    }

    // --------------------------------------------------
    // Consultas - Teclado
    // --------------------------------------------------

    bool InputManager::IsKeyHeld(unsigned char key) const
    {
        return currentKeys[key];
    }

    bool InputManager::IsKeyPressed(unsigned char key) const
    {
        return keyPressed[key] && !keyConsumed[key];
    }

    bool InputManager::IsKeyReleased(unsigned char key) const
    {
        return keyReleased[key];
    }

    // --------------------------------------------------
    // Consultas - Mouse
    // --------------------------------------------------

    bool InputManager::IsMouseButtonHeld(int button) const
    {
        return currentMouseButton[button];
    }

    bool InputManager::IsMouseButtonPressed(int button) const
    {
        return mouseButtonPressed[button] && !mouseButtonConsumed[button];
    }

    bool InputManager::IsMouseButtonReleased(int button) const
    {
        return mouseButtonReleased[button];
    }

    POINT InputManager::GetMousePosition() const
    {
        return mousePosition;
    }

    int InputManager::GetMouseDeltaX() const
    {
        return mouseDeltaX;
    }

    int InputManager::GetMouseDeltaY() const
    {
        return mouseDeltaY;
    }

    // =============================================
    // Sistema de Consumo de Input (Teclado e Mouse)
    // =============================================

    // --------------------------------------------------
    // ConsumeKey
    // Marca uma tecla como "consumida", ou seja, evita
    // que ela seja processada novamente com IsKeyPressed()
    // no mesmo frame por outros sistemas.
    // --------------------------------------------------
    void InputManager::ConsumeKey(unsigned char key)
    {
        if (key < Input::KEY_COUNT)
            keyConsumed[key] = true;
    }

    // --------------------------------------------------
    // IsKeyConsumed
    // Retorna se a tecla já foi consumida neste frame.
    // Útil para evitar múltiplos usos da mesma tecla.
    // --------------------------------------------------
    bool InputManager::IsKeyConsumed(unsigned char key) const
    {
        return (key < Input::KEY_COUNT) ? keyConsumed[key] : false;
    }

    // --------------------------------------------------
    // ConsumeMouseButton
    // Marca um botão do mouse como "consumido", bloqueando
    // a detecção por IsMouseButtonPressed() no mesmo frame.
    // --------------------------------------------------
    void InputManager::ConsumeMouseButton(int button)
    {
        if (button >= 0 && button < Input::MOUSE_COUNT)
            mouseButtonConsumed[button] = true;
    }

    // --------------------------------------------------
    // IsMouseButtonConsumed
    // Retorna se o botão do mouse foi consumido no frame
    // atual. Útil para prevenir múltiplas ações com o clique.
    // --------------------------------------------------
    bool InputManager::IsMouseButtonConsumed(int button) const
    {
        return (button >= 0 && button < Input::MOUSE_COUNT) ? mouseButtonConsumed[button] : false;
    }


    void InputManager::OnMouseWheelScroll(int delta)
    {
        mouseWheelDelta = delta;
#ifdef _DEBUG
        LOG_INFO_F(L"[Engine_System] MouseWheel Scroll: delta = %d", delta);
#endif
    }

    int InputManager::GetMouseWheelDelta() const
    {
        return mouseWheelDelta;
    }

    // --------------------------------------------------
    // FPS Mouse Mode
    // --------------------------------------------------

    // Define se o modo FPS do mouse está ativado (cursor escondido, travado no centro)
    void InputManager::SetMouseFPSMode(bool enable)
    {
        fpsMouseModeEnable = enable;

        if (enable)
        {
            RECT windowRect;
            GetWindowRect(targetWindow, &windowRect);
            ClipCursor(&windowRect);
            ShowCursor(FALSE);
        }
        else
        {
            ClipCursor(NULL);
            ShowCursor(TRUE);
        }
    }

    // Define a janela que o mouse ficará travado (modo FPS)
    void InputManager::SetMouseCaptureWindow(HWND hwnd, int width, int height)
    {
        targetWindow = hwnd;
        centerX = width / 2;
        centerY = height / 2;
    }

    // Permite configurar o centro manualmente (opcional)
    void InputManager::SetMouseCenter(int x, int y)
    {
        centerX = x;
        centerY = y;
    }
}
