// ====================
// RagX Engine - Timer
// ====================
#ifndef _RAGX_FRAME_TIMER_
#define _RAGX_FRAME_TIMER_

// ---------
// Includes
// ---------
#include "IEngineTimer.h"
#include <Windows.h>

namespace FrameTime
{
	// ===========================================================
	// Classe EngineTimer - Implementação concreta do sistema de tempo
	// Utiliza o contador de alta precisão (QueryPerformanceCounter)
	// para medir tempo entre frames e calcular FPS com precisão.
	// ===========================================================
	class EngineTimer : public IEngineTimer
	{
	public:
		// Construtor
		EngineTimer();

		// Atualiza os dados de tempo a cada frame
		void UpdateStateTick() override;

		// Retorna o tempo entre frames (em segundos)
		[[nodiscard]] double GetDeltaTime() const override;

		// Retorna o tempo total desde o início (em segundos)
		[[nodiscard]] double GetTotalTime() const override;

		// Retorna o FPS atual calculado a cada segundo
		[[nodiscard]] unsigned int GetFPS() const override;

		// Liberação de recursos (obrigatório pela interface)
		void Destroy() override;

	private:
		// Contadores de alta precisão
		LARGE_INTEGER frequency;
		LARGE_INTEGER startTime;
		LARGE_INTEGER currentTime;
		LARGE_INTEGER previousTime;

		// Controle de tempo
		float deltaTime;
		double totalTime;

		// Cálculo de FPS
		unsigned int FPS;
		unsigned int frameCount;
		double fpsAccumulator;
	};
}

#endif
