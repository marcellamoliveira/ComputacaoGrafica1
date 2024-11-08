/*#include "raylib.h"
#include "funcoes.h"
#include <math.h>


//dimensões da tela
const int wTela = 600;
const int hTela = 500;

// dimensões da janela
const double wJanela = 60.0;
const float hJanela = 50.0;


//o número de colunas/linhas
const int nCol = 600;
const int nLin = 500;
 
//distância do olho até a janela 
float dJanela = 8.0;

//raio da esfera 
float rEsfera = 10.0;



// centro da esfera  - O centro da esfera deve estar sobre o eixo z com coordenada z < -(dJanela + rEsfera)
vetor centro_esfera = { 0.0, 0.0, -(dJanela + rEsfera) };

// cor da esfera    / A cor da esfera deve ser esfColor = 255, 0, 0
vetor esfColor = { 255.0, 0.0, 0.0 };

// cor do background  -  A cor de background deve ser cinza bgColor = 100, 100, 100
vetor bgColor = { 100.0, 100.0, 100.0 };

//olho do pintor
vetor E = { 0.0f, 0.0f, 0.0f };




int main(void) {

    //iniciar a janela
    InitWindow(wTela, hTela, "Atividade 1");
    SetTargetFPS(60);

    //inicialização o dx e o dy
    double linhax = wJanela / nCol;
    double linhay = hJanela / nLin;

    // pixels por quadrado do frame
    int Deltax = wTela / nCol;
    int Deltay = hTela / nLin;

    //renderização
    while (!WindowShouldClose()) {
        vetor PSE = { -wJanela * 0.5f, hJanela * 0.5f, -dJanela };
        float zp = -dJanela;
        vetor distancia = vetor_subtrair(E, centro_esfera);  //centro da esfera ao olho do observador

        BeginDrawing(); {
            ClearBackground(BLACK);

            // Loop sobre as linhas
            for (int i = 0; i < nLin; ++i) {
                float yp = PSE.y - linhay * 0.5 - i * linhay;     

                // Loop sobre as colunas
                for (int j = 0; j < nCol; ++j) { 
                    float xp = PSE.x + linhax * 0.5 + j * linhax;
  
                    vetor P = { xp, yp, zp };   //ponto P que seria o o centro do quadrado
                    
                    vetor dr = vetor_unitario(vetor_subtrair(P, E));  // vetor dr normalizado do olho do observador ao ponto P

                    //equação de interseção entre a esfera e o raio
                    double a = vetor_produto(dr,dr);
                    double b = 2* vetor_produto(dr, distancia);
                    double c = vetor_produto(distancia, distancia) - rEsfera * rEsfera;
                    double delta = b * b - a * c;

                    // delta for menor que zero, não há interseção, pinta de cinza
                    if (delta < 0.0) {
                        DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, Color{ (unsigned char)bgColor.x, (unsigned char)bgColor.y, (unsigned char)bgColor.z, 255 });
                        
                    } else {
                        //há intersecção, pinta de vermelho
                        DrawRectangle(Deltax * j, Deltax * i, Deltax, Deltay, Color{ (unsigned char)esfColor.x, (unsigned char)esfColor.y, (unsigned char)esfColor.z, 255 });
                    }

                }
            }

        }
        EndDrawing();
    }
    return 0;
}*/