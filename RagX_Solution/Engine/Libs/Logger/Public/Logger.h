// ====================
// RagX Engine - Logger
// ====================
#ifndef _RAGX_LOGGER_
#define _RAGX_LOGGER_

// ---------
// Includes
// ---------
#include <Windows.h>

namespace Logger
{
    // ------------------------------------------------------------------
    // Logger::Info
    // Envia uma mensagem simples para o OutputDebugString (Visual Studio)
    // ------------------------------------------------------------------
    void Info(const wchar_t* msg);

    // -----------------------------------------------------------------------------
    // Logger::InfoFormatted
    // Envia uma mensagem formatada com horário para o Output (como printf com time)
    // Ex: Logger::InfoFormatted(L"FPS: %d", fps);
    // -----------------------------------------------------------------------------
    void InfoFormatted(const wchar_t* format, ...);

    // (Futuro) Suporte para níveis de log adicionais como Warn, Error, etc.
    // void Warn(const wchar_t* msg);
    // void Error(const wchar_t* msg);
}

#endif
