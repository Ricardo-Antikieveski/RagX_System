// ============================
// RagX Engine - InputTypes
// ============================

#ifndef _RAGX_INPUTTYPES_
#define _RAGX_INPUTTYPES_

namespace Input {

    // --------------------------------------------
    // Constantes
    // --------------------------------------------

    // Total de teclas suportadas (0-255 = c�digos virtuais do Windows)
    constexpr int KEY_COUNT = 256;

    // Total de bot�es suportados pelo mouse (0 - 4)
    constexpr int MOUSE_COUNT = 5;

    // --------------------------------------------
    // Estado da tecla ou bot�o
    // --------------------------------------------
    enum class KeyState {
        None,       // Nenhuma intera��o
        Pressed,    // Pressionado neste frame
        Held,       // Mantido pressionado
        Released    // Solto neste frame
    };

    // --------------------------------------------
    // �ndices dos bot�es do mouse
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
