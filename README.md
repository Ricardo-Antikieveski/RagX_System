# 🎮 RagX Engine

> 🧱 Uma engine modular de FPS feita do zero em C++ com arquitetura profissional, WinAPI e DirectX.

---

## 🚀 Visão Geral

A **RagX Engine** é uma engine de jogos independente, desenvolvida totalmente em C++ com foco em performance, modularidade e aprendizado profundo. Inspirada na arquitetura de motores profissionais como Unreal Engine, ela permite a criação de jogos FPS com controle total sobre cada subsistema — sem depender de engines prontas.

---

## 🛠️ Tecnologias e Arquitetura

- 🔧 **C++20** como padrão oficial
- 🖼️ **WinAPI** para criação de janelas e captura de input
- 🎮 **Input Manager** com detecção de teclas, mouse e scroll
- ⏱️ **Sistema de Tempo** com deltaTime, FPS, pausa, time scale
- 🧩 Arquitetura baseada em **interfaces puras** e **injeção de dependência**
- 🔗 Organização modular com **.lib** para sistemas e **.dll** para a engine
- 🧪 Visualização de logs em tempo real via `OutputDebugString` e app auxiliar `RagaDebugViewer`

---

## 🧱 Estrutura Modular

| Módulo           | Descrição                                                                 |
|------------------|---------------------------------------------------------------------------|
| `Graphics`       | Criação e controle da janela (WinAPI), com suporte a fullscreen e título  |
| `Input`          | Captura de teclado e mouse via mensagens (WndProc) com sistema de consumo |
| `FrameTimer`     | Gerenciamento de tempo (deltaTime, FPS, time scale, pausa)                |
| `Logger`         | Sistema de logging com macros inteligentes e integração com Debug Viewer  |
| `CollectorManager` | Coleta e destruição segura de subsistemas (ResourceCollector)          |
| `EngineCore`     | Núcleo central da engine (init, loop, shutdown, orquestração modular)     |
| `Game`           | Executável final que usa a engine como DLL                                |

---

## 📸 Capturas e Progresso Visual

📁 [Drive com imagens e vídeos do desenvolvimento](https://drive.google.com/drive/folders/1jjGHlWPCjYo_GG0GlXdX8bBTM902-I7W?usp=sharing)

---

## 📌 Status Atual (Junho 2025)

- ✅ **Window System** com modo fullscreen e título dinâmico
- ✅ **InputManager** funcional (teclado, mouse, scroll e consumo de input)
- ✅ **FrameTimer** com FPS, deltaTime, pausa e time scale
- ✅ **Logger** com visualização em tempo real no `RagaDebugViewer`
- ✅ **CollectorManager** com `SafeDestroy` e gerenciamento centralizado
- ✅ **EngineCore** com estrutura modular e uso de interfaces
- ✅ **Game.exe** consumindo a `RagXEngine.dll` corretamente
- 🚧 Em desenvolvimento: sistema de renderização com DirectX 11

---

## 🧪 Projeto Atual

O projeto está 100% modular, com separação entre:

- **Engine (DLL)** – Código da engine real, não visível ao jogo
- **Sistemas (LIBs)** – Cada subsistema é independente (Input, Graphics, etc.)
- **Jogo (EXE)** – Apenas chama a engine via ponteiros para interfaces

---

## 🎯 Objetivos do Projeto

- Aprender e aplicar **programação de baixo nível com C++ e WinAPI**
- Criar uma engine de jogos FPS modular e reutilizável
- Simular pipelines reais com **arquitetura profissional** de engines comerciais
- Explorar conceitos como: injeção de dependência, macros, logs, interfaces, multithreading e gerenciamento manual de recursos

---

## 🗺️ Roadmap (próximas etapas)

- [ ] Sistema de renderização com DirectX (triângulo e pipeline inicial)
- [ ] Câmera 3D e sistema de cena
- [ ] Sistema de áudio básico
- [ ] Lobby estilo Point Blank
- [ ] Implementação de rede com instâncias de battle server
- [ ] Sistema de assets e pré-carregamento
- [ ] Ferramenta externa de debug remota (via socket)

---

## 📂 Código e Organização

> 🔒 O código-fonte completo está disponível em repositório privado.  
> Este repositório público serve como documentação e portfólio técnico do progresso da RagX Engine.

---

## 👨‍💻 Autor

**Ricardo Antikieveski**  
🔧 Desenvolvedor autodidata focado em engines e programação de baixo nível  
📧 antikieveski.ricardo@gmail.com  
📷 [Instagram: @_ricardoan](https://www.instagram.com/_ricardoan/)

---

## 📝 Licença

Este projeto é de uso privado e acadêmico.  
Entre em contato para permissões específicas ou parcerias.

