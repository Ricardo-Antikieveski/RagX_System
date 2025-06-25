// ========================
// RagX Engine - EngineCore
// ========================

// ---------
// Includes
// ---------
#include <cassert>

#include "EngineCore.h"
#include "Window.h"
#include "InputManager.h"
#include "EngineTimer.h"
#include "LoggerMacros.h"

#include "ResourceCollector.h"
#include "SafeDestroy.h"

// ---------
// Usings
// ---------
using namespace Engine;
using namespace Graphics;
using namespace Input;
using namespace FrameTime;
using namespace CollectorManager;

// ==============================
// Instância global do collector
// ==============================
ResourceCollector collector;

// ==============================
// Construtor / Destrutor
// ==============================

// --------------------------------------------------
// Construtor - Garante que apenas uma instância exista
// --------------------------------------------------
EngineCore::EngineCore()
{
	assert(instance == nullptr && "[Engine_System] Engine já foi instanciada!");
	instance = this;
}

// -------------------------------
// Destrutor - Libera recursos via Shutdown()
// -------------------------------
EngineCore::~EngineCore() = default;

// ==============================
// Inicialização e Desligamento
// ==============================

// ------------------------------------------
// Shutdown - Libera os recursos registrados
// ------------------------------------------
void EngineCore::Shutdown()
{
	if (instance == nullptr)
	{
		LOG_INFO_F(L"[Engine_System] Engine não foi inicializada!");
		return;
	}

	// Libera todos os subsistemas registrados
	SafeDestroyAll(collector, iWindow, iEngineTimer, iInputManager);

	delete instance;
	instance = nullptr;
}

// --------------------------------------------------------
// Get - Retorna a instância singleton da engine.
// Cria uma nova se ainda não existir.
// --------------------------------------------------------
EngineCore& EngineCore::Get()
{
	if (instance == nullptr)
	{
		new EngineCore();
		assert(instance != nullptr && "[Engine_System] Falha ao inicializar a instância da Engine.");
	}
	return *instance;
}

// -----------------------------------------------------------
// Init - Inicializa os sistemas da engine:
// - Cria a janela e registra no collector
// - Cria o input manager e conecta com a janela
// - Cria o timer da engine
// -----------------------------------------------------------
bool EngineCore::Init(HINSTANCE hInstance, int width, int height)
{
	if (instance == nullptr)
	{
		LOG_INFO_F(L"[Engine_System] RagX Engine não foi iniciada!");
		return false;
	}

	// ---------- Janela ----------
	iWindow = std::make_unique<Window>();
	collector.Register(iWindow.get());

	if (!iWindow->Create(hInstance, width, height, L"RagX Engine - Game"))
		return false;

	// ---------- Sistema de Input ----------
	iInputManager = std::make_unique<InputManager>();
	collector.Register(iInputManager.get());

	// Conecta input com a janela
	iWindow->ConnectInputSystem(iInputManager.get());

	// ---------- Timer da Engine ----------
	iEngineTimer = std::make_unique<EngineTimer>();
	collector.Register(iEngineTimer.get());

	LOG_INFO_F(L"[Engine_System] Todos os sistemas foram inicializados com sucesso.");
	return true;
}

// ==============================
// Loop Principal
// ==============================

// ---------------------------------------------------
// Run - Loop principal da engine. Executa enquanto
// a janela estiver ativa, atualizando o timer,
// input e processando mensagens do sistema.
// ---------------------------------------------------
void EngineCore::Run()
{
	// Checagem de segurança para evitar acesso nulo
	if (!iWindow || !iEngineTimer || !iInputManager)
	{
		LOG_INFO_F(L"[Engine_System] Um ou mais sistemas não foram inicializados.");
		return;
	}

#ifdef _DEBUG
	float titleUpdateTimer = 0.0f;
	wchar_t buffer[128];
#endif

	// ---------------------------
	// Loop principal da aplicação
	// ---------------------------
	while (!iWindow->ShouldClose())
	{
		// ---------- Atualiza tempo ----------
		iEngineTimer->UpdateStateTick();

#ifdef _DEBUG
		// ---------- Atualiza título da janela ----------
		titleUpdateTimer += static_cast<float>(iEngineTimer->GetDeltaTime());

		if (titleUpdateTimer >= 1.0f)
		{
			swprintf_s(buffer, 128, L"Ragx Engine - FPS: %u | Δt: %.4f",
				iEngineTimer->GetFPS(), iEngineTimer->GetDeltaTime());

			iWindow->UpdateWindowTitle(buffer);
			titleUpdateTimer = 0.0f;
		}
#endif

		// ---------- Processa eventos do sistema (input, redimensionamento, etc) ----------
		iWindow->ProcessMessages();

		// ---------- Atualiza estado do input ----------
		iInputManager->UpdateInput();

		// ---------- [TODO] Atualizar lógica do jogo ----------

		// ---------- [TODO] Renderizar frame ----------

		int scroll = iInputManager->GetMouseWheelDelta();
		if (scroll > 0)
			LOG_INFO_F(L"[Engine_Input] Scroll para cima: %d", scroll);
		else if (scroll < 0)
			LOG_INFO_F(L"[Engine_Input] Scroll para baixo: %d", scroll);
	}
}
