#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    double G = 9.81;
    double velocidade_inicial = 30;    // em metros por segundo
    double angulo = 45 * (M_PI / 180); // angulo em radianos
    double velocidade_inicialX = velocidade_inicial * cos(angulo);
    double velocidade_inicialY = velocidade_inicial * sin(angulo);

    double tempo;
    double posicao_inicialX = 0;
    double posicao_inicialY = 0;

    double posicao_anteriorX = 0;
    double posicao_anteriorY = 0;
    double tempo_anterior = 0;

    double X_interpolado;
    double tempo_interpolado;

    double tempo_voo = ((2 * velocidade_inicial * sin(angulo)) / G);
    double distancia_formula = velocidade_inicial * cos(angulo) * tempo_voo;

    double erro;

    int contador = 0;

    cout << "Digite o tempo da simulacao: ";
    cin >> tempo;

    cout << "----------------------------------------------\n";

    ofstream arq("trajetoria.csv");
    arq << "x,y\n";


    for (double t = 0; t <= tempo; t = t + 0.0001)
    {
        
        double posicao_atualX = posicao_inicialX + (velocidade_inicialX * t);
        double posicao_atualY = posicao_inicialY + (velocidade_inicialY * t) - ((G * (t * t)) / 2);

        if (posicao_atualY >= 0)
        {
            arq << posicao_atualX << "," << posicao_atualY << "\n";

            if(contador % 1000 == 0){
                cout << "Tempo: " << t << "\n";
                cout << "Posicao atual no eixo X: " << posicao_atualX << endl;
                cout << "Posicao atual no eixo Y: " << posicao_atualY << "\n";
                cout << "----------------------------------------------\n";
                
            }
            contador += 1;

            posicao_anteriorX = posicao_atualX;
            posicao_anteriorY = posicao_atualY;
            tempo_anterior = t;
        }
        else
        {
            X_interpolado = posicao_anteriorX + (posicao_atualX - posicao_anteriorX) * ((0 - posicao_anteriorY) / (posicao_atualY - posicao_anteriorY));
            tempo_interpolado = tempo_anterior + (t - tempo_anterior) * ((0 - posicao_anteriorY) / (posicao_atualY - posicao_anteriorY));

            arq << X_interpolado << ",0\n";

            cout << "Chegou no chao!!\n\n";
            cout << "A distancia percorrida calculada pela simulacao foi de " << X_interpolado << " metros. " << "Em " << tempo_interpolado << " segundos.\n";
            cout << "A distancia percorrida calculada pela formula foi de " << distancia_formula << " metros. " << "Em " << tempo_voo << " segundos.\n";

            cout << "\nO erro simulacao em relacao a formula foi de\n"
                 << "Metros: " << abs(distancia_formula - X_interpolado) << " (" << (abs(X_interpolado - distancia_formula) / abs(distancia_formula)) * 100 << "%)"
                 << "\nSegundos: " << abs(tempo_interpolado - tempo_voo) << " (" << (abs(tempo_interpolado - tempo_voo) / abs(tempo_voo)) * 100 << "%)\n";

            break;
        }
        
    }

    system("pause");
    return 0;
}