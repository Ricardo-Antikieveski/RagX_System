// ========================
// RagX Engine - EngineCore
// ========================
#ifndef _RAGX_ENGINECORE_
#define _RAGX_ENGINECORE_

//===========
// DLL EXPORT
//===========
#ifdef RAGX_ENGINE_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

// ---------
// Includes
// ---------
#include "EngineGlobal.h"

#include <Windows.h>
#include <memory>

// Forward declarations para evitar depend�ncias pesadas
namespace Graphics { class IWindow; }
namespace FrameTime { class IEngineTimer; }
namespace Input { class IInputManager; }

namespace Engine
{
    // ===========================================================
    // Classe: EngineCore
    // -----------------------------------------------------------
    // N�cleo principal da RagX Engine. Respons�vel por:
    // - Inicializar os sistemas (janela, timer, etc.)
    // - Rodar o loop principal
    // - Realizar shutdown e libera��o de recursos
    // ===========================================================
    class DLL EngineCore
    {
    public:
        EngineCore();
        ~EngineCore();

        // Inicializa os subsistemas
        bool Init(HINSTANCE hInstance, int width, int height);

        // Loop principal da engine (update, mensagens, etc.)
        void Run();

        // Libera todos os recursos registrados no collector
        void Shutdown();

        // Acesso � inst�ncia global (singleton)
        static EngineCore& Get();

    private:
        // Inst�ncia singleton da engine
        inline static EngineCore* instance = nullptr;

        // Subsistemas principais da engine
        std::unique_ptr<Graphics::IWindow> iWindow;
        std::unique_ptr<FrameTime::IEngineTimer> iEngineTimer;
        std::unique_ptr<Input::IInputManager> iInputManager;
    };
}

#endif
