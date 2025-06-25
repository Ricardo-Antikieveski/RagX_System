// ====================
// RagX Engine - Logger
// ====================
#include "Logger.h"
#include <format>
#include <chrono>
#include <ctime>

namespace Logger
{
#ifdef _DEBUG

    // ---------------------------
    // Envia string direta ao Output
    // ---------------------------
    void Info(const wchar_t* msg)
    {
        OutputDebugStringW(msg);
    }

    // ---------------------------------------------------------
    // Envia mensagem formatada com horário para o OutputDebug
    // Formato: [HH:MM:SS] [INFO] Mensagem
    // ---------------------------------------------------------
    void InfoFormatted(const wchar_t* format, ...)
    {
        wchar_t formattedMsg[512];

        va_list args;
        va_start(args, format);
        vswprintf_s(formattedMsg, sizeof(formattedMsg) / sizeof(wchar_t), format, args);
        va_end(args);

        // Obter horário atual formatado
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        tm localTime;
        localtime_s(&localTime, &now_time);

        wchar_t timestamp[32];
        wcsftime(timestamp, 32, L"%H:%M:%S", &localTime);

        wchar_t finalOutput[1024];
        swprintf_s(finalOutput, 1024, L"[%s] [INFO] %s\n", timestamp, formattedMsg);

        OutputDebugStringW(finalOutput);
    }

#else

    // Em Release, funções são vazias
    void Info(const wchar_t*) {}
    void InfoFormatted(const wchar_t*, ...) {}

    // Futuras implementações para modo Release
    void Warn(const wchar_t*) {}
    void Error(const wchar_t*) {}

#endif
}
