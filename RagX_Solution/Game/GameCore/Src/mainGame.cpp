// ====================
// RagX Game - mainGame
// ====================

// ---------
// Includes
// ---------
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#include <iostream>

#include <Windows.h>
#include "EngineCore.h"

using Engine::EngineCore;

// ==============================
// Ponto de entrada do aplicativo
// ==============================
// - Inicializa o sistema de debug de memória (_CrtDbgFlag)
// - Inicializa a engine
// - Executa o loop principal
// - Realiza shutdown e finalização
// ==============================
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // Ativa o modo de verificação de vazamento de memória (Debug)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Inicialização da engine
    if (!gEngine.Init(hInstance, 1280, 720))
        return -1;

    // Loop principal da engine
    gEngine.Run();

    // Finalização e liberação de recursos
    gEngine.Shutdown();

    // (Opcional) Desligamento de sistemas auxiliares como logger, profiler, etc.

    // Retorna para o sistema. _CrtDumpMemoryLeaks será executado automaticamente
    return 0;
}
