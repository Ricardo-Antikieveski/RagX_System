// ===============================
// RagX Engine - ResourceCollector
// ===============================
#ifndef _RAGX_RESOURCE_COLLECTOR_
#define _RAGX_RESOURCE_COLLECTOR_

// ---------
// Includes
// ---------
#include <vector>
#include "IDestroyable.h"

using namespace CollectorManager;

namespace CollectorManager
{
	// -----------------------------------------------------------------
	// Classe responsável por registrar e destruir sistemas da engine
	// de forma centralizada e segura, evitando vazamentos de memória.
	// -----------------------------------------------------------------
	class ResourceCollector
	{
	public:
		// Adiciona um objeto à lista de destruição automática
		void Register(IDestroyable* obj);

		// Remove um objeto da lista sem destruí-lo
		void Unregister(IDestroyable* obj);

		// Executa Destroy() em todos os objetos registrados
		void UnregisterAll();

		// Limpa a lista sem chamar Destroy() nos objetos (uso avançado)
		void Clear();

	private:
		std::vector<IDestroyable*> objects; // Lista de objetos registrados
	};
}

#endif
