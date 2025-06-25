// ===============================
// RagX Engine - ResourceCollector
// ===============================

// ---------
// Includes
// ---------
#include "ResourceCollector.h"
#include <algorithm>

using namespace CollectorManager;

// ----------------------------
// Adiciona um objeto à lista
// ----------------------------
void ResourceCollector::Register(IDestroyable* obj)
{
	if (obj)
		objects.push_back(obj);
}

// ------------------------------------
// Remove um objeto manualmente da lista
// ------------------------------------
void ResourceCollector::Unregister(IDestroyable* obj)
{
	objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
}

// ------------------------------------------------------------
// Chama Destroy() em todos os objetos e limpa a lista inteira
// Ideal para uso quando a engine está sendo desligada
// ------------------------------------------------------------
void ResourceCollector::UnregisterAll()
{
	for (auto* obj : objects)
	{
		if (obj)
			obj->Destroy();
	}
	objects.clear();
}

// -------------------------
// Limpa a lista sem destruir
// -------------------------
void ResourceCollector::Clear()
{
	objects.clear();
}
