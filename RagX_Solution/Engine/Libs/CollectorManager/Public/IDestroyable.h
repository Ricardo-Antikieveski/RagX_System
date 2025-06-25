// ==========================
// RagX Engine - IDestroyable
// ==========================
#ifndef _RAGX_IDESTROYABLE_
#define _RAGX_IDESTROYABLE_

// ----------------------------
// Interface base de destruição
// ----------------------------
// Essa interface deve ser herdada por qualquer sistema ou classe
// que precise executar uma limpeza manual de recursos.
// Ex: liberar buffers, handles, memoria heap, etc.
namespace CollectorManager
{
	class IDestroyable
	{
	public:
		// Método virtual puro que deve ser implementado para liberar recursos
		virtual void Destroy() = 0;

		// Destrutor virtual padrão
		virtual ~IDestroyable() = default;
	};
}

#endif
