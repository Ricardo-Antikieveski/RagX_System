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
	// Classe respons�vel por registrar e destruir sistemas da engine
	// de forma centralizada e segura, evitando vazamentos de mem�ria.
	// -----------------------------------------------------------------
	class ResourceCollector
	{
	public:
		// Adiciona um objeto � lista de destrui��o autom�tica
		void Register(IDestroyable* obj);

		// Remove um objeto da lista sem destru�-lo
		void Unregister(IDestroyable* obj);

		// Executa Destroy() em todos os objetos registrados
		void UnregisterAll();

		// Limpa a lista sem chamar Destroy() nos objetos (uso avan�ado)
		void Clear();

	private:
		std::vector<IDestroyable*> objects; // Lista de objetos registrados
	};
}

#endif
