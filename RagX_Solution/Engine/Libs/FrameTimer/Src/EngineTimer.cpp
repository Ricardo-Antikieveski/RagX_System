// =========================
// RagX Engine - EngineTimer
// =========================

// ---------
// Includes
// ---------
#include "EngineTimer.h"
#include "LoggerMacros.h"

namespace FrameTime
{
	// ----------------------------
	// Construtor - inicializa contadores
	// ----------------------------
	EngineTimer::EngineTimer()
		: deltaTime(0.0), totalTime(0.0),
		FPS(0), frameCount(0), fpsAccumulator(0.0)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&currentTime);
		previousTime = startTime = currentTime;
	}

	// ----------------------------
	// Destruidor - placeholder
	// ----------------------------
	void EngineTimer::Destroy()
	{
		// Nenhum recurso a ser liberado por enquanto
	}

	// -----------------------------------------------------------------
	// Atualiza todos os dados de tempo:
	// - Calcula o deltaTime entre o frame atual e o anterior
	// - Soma ao tempo total acumulado
	// - Conta os frames para cálculo de FPS a cada 1 segundo
	// -----------------------------------------------------------------
	void EngineTimer::UpdateStateTick()
	{
		QueryPerformanceCounter(&currentTime);
		LONGLONG deltaTicks = currentTime.QuadPart - previousTime.QuadPart;

		deltaTime = static_cast<float>(deltaTicks) / frequency.QuadPart;
		totalTime += deltaTime;
		previousTime = currentTime;

		frameCount++;
		fpsAccumulator += deltaTime;

		if (fpsAccumulator >= 1.0)
		{
			FPS = frameCount;
			frameCount = 0;
			fpsAccumulator = 0.0;
		}
	}

	// ----------------------------
	// Retorna o deltaTime do frame
	// ----------------------------
	double EngineTimer::GetDeltaTime() const
	{
		return deltaTime;
	}

	// ----------------------------
	// Retorna o tempo total acumulado
	// ----------------------------
	double EngineTimer::GetTotalTime() const
	{
		return totalTime;
	}

	// ----------------------------
	// Retorna o FPS atual
	// ----------------------------
	unsigned int EngineTimer::GetFPS() const
	{
		return FPS;
	}
}
