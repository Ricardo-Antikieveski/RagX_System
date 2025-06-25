// ============================
// RagX Engine - InputTypes
// ============================

#ifndef _RAGX_INPUTTYPES_
#define _RAGX_INPUTTYPES_

namespace Input {

    // --------------------------------------------
    // Constantes
    // --------------------------------------------

    // Total de teclas suportadas (0-255 = códigos virtuais do Windows)
    constexpr int KEY_COUNT = 256;

    // Total de botões suportados pelo mouse (0 - 4)
    constexpr int MOUSE_COUNT = 5;

    // --------------------------------------------
    // Estado da tecla ou botão
    // --------------------------------------------
    enum class KeyState {
        None,       // Nenhuma interação
        Pressed,    // Pressionado neste frame
        Held,       // Mantido pressionado
        Released    // Solto neste frame
    };

    // --------------------------------------------
    // Índices dos botões do mouse
    // --------------------------------------------
    enum MouseButton {
        Left = 0,
        Right,
        Middle,
        Extra1,
        Extra2
    };

} // namespace Input

#endif // _RAGX_INPUTTYPES_
