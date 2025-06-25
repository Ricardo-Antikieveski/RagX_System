#include <windows.h>
#include <iostream>
#include <iomanip>

int main()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER previousTime, currentTime;

    // Obtem a frequência do timer de alta precisão
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&previousTime);

    std::cout << "Imprimindo deltaTime em segundos (pressione Ctrl+C para sair):\n";

    while (true)
    {
        QueryPerformanceCounter(&currentTime);

        LONGLONG deltaTicks = currentTime.QuadPart - previousTime.QuadPart;
        double deltaTime = static_cast<double>(deltaTicks) / frequency.QuadPart;

        // Atualiza tempo anterior para o próximo frame
        previousTime = currentTime;

        // Imprime com 6 casas decimais (precisão de microssegundos)
        std::cout << std::fixed << std::setprecision(6)
            << "deltaTime: " << deltaTime << " segundos\n";

        // Simula um trabalho de renderização leve (~sleep de 16ms para simular 60fps)
        //Sleep(16);
    }


    /* Simula os ticks do processador
    unsigned __int64 start = __rdtsc();
    // ... faz algo ...
    unsigned __int64 end = __rdtsc();

    unsigned __int64 ticks = end - start;*/

    return 0;
}
