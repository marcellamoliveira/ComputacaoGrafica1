#include <cmath>
#include <raylib.h>
#include "funcoes.h"

//dimensões da tela
const int wTela = 600;
const int hTela = 500;

// dimensões da janela/frame
const float wJanela = 6.0;
const float hJanela = 5.0;

//o número de colunas/linhas
const int nCol = 600;
const int nLin = 500;


// Distância do frame ao observador
float dJanela = 2.0;                 

// Raio da esfera
float rEsfera = 6.0;             

// Centro da esfera
vetor centro_esfera = { 0.0, 0.0, -(dJanela + rEsfera) };



// I_F = Intensidade da da fonte pontual
vetor Intensidade_Fonte = { 0.7, 0.7, 0.7 };       

// P_F - Posição da fonte pontual situada a 5 metros acima do olho do observador.
vetor Posicao_Fonte = { 0.0, 5.0, 0.0 };       

// material da esfera
const vetor k = { 0.5, 0.0, 0.0 }; 

// Expoente para iluminação especular
const double exp_especular = 10.0;        


int main() {

    //iniciar a janela
    InitWindow(wTela, hTela, "Atividade 2");
    SetTargetFPS(60);

    //inicialização o dx e o dy
    double dx = wJanela / nCol;
    double dy = hJanela / nLin;

    //tamanho dos retângulos na janela para cada ponto do frame
    int wPixel = wTela / nCol;
    int hPixel = hTela / nLin;

  
    while (!WindowShouldClose()) {
        //ponto superior esquerdo
        vetor PSE = { -wJanela * 0.5, hJanela * 0.5, -dJanela };

        // do observador até o centro da esfera
        vetor distancia = vetor_escala(centro_esfera, -1);

        BeginDrawing();
        ClearBackground(Color{ 100, 100, 100 });        

        for (int i = 0; i < nLin; ++i) {
            double yp = PSE.y - dy * 0.5 - i * dy;

            for (int j = 0; j < nCol; ++j) {
                double xp = PSE.x + dx * j + dx * 0.5;

                vetor P = { xp, yp, -dJanela };

                // vetor normalizado do observador até o ponto P
                vetor dr = vetor_unitario(P);

                //coeficientes de bhaskara
                double a = vetor_produto(dr, dr);
                double b = 2 * vetor_produto(dr, distancia);
                double c = vetor_produto(distancia, distancia) - rEsfera * rEsfera;
                double delta = b * b - 4 * a * c;

                // verificação de interseção com a esfera
                if (delta < 0.0) continue;
                double raiz = (-b - sqrt(delta)) / (2 * a);
                if (raiz < 0.0) { raiz = (-b + sqrt(delta)) / (2 * a); };
                if (raiz < 0.0) continue;



                // interseção do vetor dr até a esfera, obtendo as coordenadas da intersecção
                vetor interseccao = vetor_escala(dr, raiz);

                //vetor normal apartir da intersecção
                vetor normal = vetor_unitario(vetor_subtrair(interseccao, centro_esfera));

                // inversão da direção da intersecção para o observador
                vetor vetor_invertido = vetor_escala(dr, -1);

                // aponta da intersecção para a fonte de luz(Posicao_Fonte)
                vetor fonte_invertida = vetor_unitario(vetor_subtrair(Posicao_Fonte, interseccao));

                //luz refletida no ponto de intersecção
                vetor refletido = vetor_subtrair(vetor_escala(normal, 2 * vetor_produto(normal, fonte_invertida)), fonte_invertida);

                // I_d - reflexão difusa
                vetor I_difusa = vetor_escala(vetor_multiplica( Intensidade_Fonte, k), maximo(vetor_produto(fonte_invertida, normal), 0));

                //  I_e - reflexão especular >> brilho refletido na intersecção
                vetor I_especular = vetor_escala(vetor_multiplica( Intensidade_Fonte, k), maximo(pow(vetor_produto(vetor_invertido, refletido), exp_especular), 0));

                // intensidade total da luz
                vetor IntensidadeTotal = vetor_soma(I_difusa, I_especular);

                //cálculo da intensidade de luz para valores de cor (0-255)
                Color pixelColor = Color{
                    static_cast<unsigned char>(minimo(IntensidadeTotal.x * 255.0, 255.0)),
                    static_cast<unsigned char>(minimo(IntensidadeTotal.y * 255.0, 255.0)),
                    static_cast<unsigned char>(minimo(IntensidadeTotal.z * 255.0, 255.0)),
                    255  
                };

                //pintando o pixel
                DrawRectangle(wPixel * j, hPixel * i, wPixel, hPixel, pixelColor);
            }
        }

        EndDrawing();
    }

    CloseWindow();  //fechar a janela
    return 0;
}