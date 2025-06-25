// ==========================
// RagX Engine - LoggerMacros
// ==========================
#ifndef _RAGX_LOGGER_MACROS_
#define _RAGX_LOGGER_MACROS_

#include "Logger.h"

// ----------------------------------------
// Macros de log (ativas somente em _DEBUG)
// ----------------------------------------
#ifdef _DEBUG

#define LOG_INFO(msg)            Logger::Info(msg)
#define LOG_INFO_F(format, ...)  Logger::InfoFormatted(format, __VA_ARGS__)

// (Futuro) Macros para outros níveis
// #define LOG_WARN(msg)         Logger::Warn(msg)
// #define LOG_ERROR(msg)        Logger::Error(msg)

#else

// Em modo Release, todos os logs são removidos do código
#define LOG_INFO(msg)            ((void)0)
#define LOG_INFO_F(format, ...)  ((void)0)
#define LOG_WARN(msg)            ((void)0)
#define LOG_ERROR(msg)           ((void)0)

#endif

#endif
