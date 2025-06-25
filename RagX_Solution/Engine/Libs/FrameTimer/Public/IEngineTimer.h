// ==========================
// RagX Engine - IEngineTimer
// ==========================
#ifndef _RAGX_IENGINE_TIMER_
#define _RAGX_IENGINE_TIMER_

#include "IDestroyable.h"

namespace FrameTime
{
	// ---------------------------------------------------------------
	// Interface base para sistemas de tempo da RagX Engine.
	// Usada para atualização de DeltaTime, tempo total e cálculo de FPS.
	// ---------------------------------------------------------------
	class IEngineTimer : public CollectorManager::IDestroyable
	{
	public:
		virtual ~IEngineTimer() = default;

		// Atualiza o estado de tempo do frame atual
		virtual void UpdateStateTick() = 0;

		// Retorna o tempo em segundos entre o frame atual e o anterior
		virtual double GetDeltaTime() const = 0;

		// Retorna o tempo total desde o início da engine
		virtual double GetTotalTime() const = 0;

		// Retorna o número de frames por segundo (FPS) atual
		virtual unsigned int GetFPS() const = 0;

		// Destrói o sistema (chamado pelo ResourceCollector)
		virtual void Destroy() = 0;
	};
}

#endif
