#include <raylib.h>
#include "funcoes.h"
#include <cmath>

// tela/canvas
const int wTela = 500;
const int hTela = 500;

// janela/frame
const float wJanela = 60.0;
const float hJanela = 60.0;

const int nCol = 500;
const int nLin = 500;

float dJanela = 30.0;  //frame ao observador

vetor centro_esfera = { 0, 0, -100 };
float rEsfera = 40.0;

// Plano do chão
const vetor ponto_chao = { 0.0, -rEsfera, 0.0 };   
const vetor normal_chao = { 0.0, 1.0, 0.0 };  


// Plano de fundo
const vetor ponto_fundo = { 0.0, 0.0, -200.0 };   
const vetor normal_fundo = { 0.0, 0.0, 1.0 };



int main() {
    InitWindow(wTela, hTela, "Atividade 3");
    SetTargetFPS(60);

    double dx = wJanela / nCol;
    double dy = hJanela / nLin;
    int wPixel = wTela / nCol;
    int hPixel = hTela / nLin;



    while (!WindowShouldClose()) {
        vetor PSE = { -wJanela * 0.5f, hJanela * 0.5f, -dJanela };

        BeginDrawing();
        ClearBackground(Color{ 100, 100, 100 });

        for (int i = 0; i < nLin; ++i) {
            double yp = PSE.y - dy * 0.5 - i * dy;

            for (int j = 0; j < nCol; ++j) {
                double xp = PSE.x + dx * j + dx * 0.5;

                vetor P = { xp, yp, -dJanela };
                vetor dr = vetor_unitario(P);
                vetor dr_invertido = vetor_unitario(vetor_escala(dr, -1));

                //inicializar as variaveis - distância da origem do raio até o perspectivo
                double distancia_esfera = INFINITY;
                double distancia_chao = INFINITY;
                double distancia_fundo = INFINITY;

                //verifica se o raio de luz intersecta a esfera, o chão e o fundo, e retorna essa distaância
                bool intersecaoEsfera = IntersecaoEsfera({ 0, 0, 0 }, dr, distancia_esfera, centro_esfera, rEsfera);
                bool intersecaoChao = IntersecaoPlano({ 0, 0, 0 }, dr, ponto_chao, normal_chao, distancia_chao);
                bool intersecaoFundo = IntersecaoPlano({ 0, 0, 0 }, dr, ponto_fundo, normal_fundo, distancia_fundo);

                double interseccao_minima = INFINITY;
                vetor interseccao, normal, k_d, k_a, k_e;
                double exp_especular;

                if (intersecaoEsfera && distancia_esfera < interseccao_minima) {
                    interseccao_minima = distancia_esfera;
                    interseccao = vetor_escala(dr, distancia_esfera);
                    normal = vetor_unitario(vetor_subtrair(interseccao, centro_esfera));
                    k_d = { 0.7, 0.2, 0.2 };
                    k_a = { 0.7, 0.2, 0.2 };
                    k_e = { 0.7, 0.2, 0.2 };
                    exp_especular = 10.0;
                }

                if (intersecaoChao && distancia_chao < interseccao_minima) {
                    interseccao_minima = distancia_chao;
                    interseccao = vetor_escala(dr, distancia_chao);
                    normal = normal_chao;
                    k_d = { 0.2, 0.7, 0.2 };
                    k_a = { 0.2, 0.7, 0.2 };
                    k_e = { 0.0, 0.0, 0.0 };
                    exp_especular = 1.0;
                }
                if (intersecaoFundo && distancia_fundo < interseccao_minima) {
                    interseccao_minima = distancia_fundo;
                    interseccao = vetor_escala(dr, distancia_fundo);
                    normal = { 0, 0, 1 };
                    k_d = { 0.3, 0.3, 0.7 };
                    k_a = { 0.3, 0.3, 0.7 };
                    k_e = { 0.0, 0.0, 0.0 };
                    exp_especular = 1.0;
                }

                if (interseccao_minima < INFINITY) {
                    vetor cor = luz_e_sombra(
                        interseccao,normal, dr_invertido, k_d, k_a, k_e, exp_especular,centro_esfera,rEsfera, ponto_chao, normal_chao,ponto_fundo,normal_fundo
                    );
                    Color color = { 
                        (unsigned char)(cor.x * 255), 
                        (unsigned char)(cor.y * 255), 
                        (unsigned char)(cor.z * 255),
                        255 };
                    DrawRectangle(j * wPixel, i * hPixel, wPixel, hPixel, color);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}