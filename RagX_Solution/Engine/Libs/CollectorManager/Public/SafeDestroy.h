// =========================
// RagX Engine - SafeDestroy
// =========================
#ifndef _RAGX_SAFE_DESTROY_
#define _RAGX_SAFE_DESTROY_

// ---------
// Includes
// ---------
#include <memory>
#include "LoggerMacros.h"
#include "ResourceCollector.h"

namespace CollectorManager
{
	// ----------------------------------------------------------------------------
	// SafeDestroy - Libera corretamente um subsistema:
	// - Remove do coletor
	// - Chama Destroy()
	// - Reseta o ponteiro único
	// ----------------------------------------------------------------------------
	template<typename T>
	void SafeDestroy(ResourceCollector& collector, std::unique_ptr<T>& ptr)
	{
		if (ptr)
		{
			collector.Unregister(ptr.get());
			ptr->Destroy();
			ptr.reset();

#ifdef _DEBUG
			LOG_INFO_F(L"[SafeDestroy] Reset executado para tipo: %hs", typeid(T).name());
#endif
		}
	}

	// --------------------------------------------------------------------------
	// SafeDestroyAll - Chama SafeDestroy em lote para múltiplos ponteiros únicos
	// Ex: SafeDestroyAll(collector, window, renderer, input);
	// --------------------------------------------------------------------------
	template<typename... Ts>
	void SafeDestroyAll(ResourceCollector& collector, Ts&... systems)
	{
		(SafeDestroy(collector, systems), ...); // Fold expression C++17+
	}
}

#endif
