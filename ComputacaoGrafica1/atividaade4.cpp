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




const vetor centrob_cilindro = { 0, 0, -100 };
const float rb_cilindro = (1.0 / 3.0)* 40;
const float hCilindro = 120.0;
const vetor d_cil = { -1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3) };     //Vetor - direção do cilindro d_cil = (-1 / sqrt(3), 1 / sqrt(3), -1 / sqrt(3))
const vetor K_cilindro = { 0.2, 0.3, 0.8 };


const vetor centrob_cone = vetor_soma(centrob_cilindro, vetor_escala(d_cil, hCilindro));
//Centro da base localizado no centro do topo do cilindro
const float rb_cone = 60.0;
const float hCone = 20.0;
const vetor d_cone = d_cil;
const vetor K_cone = { 0.8, 0.3, 0.2 };

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

                double distancia_cilindro = INFINITY;
                double distancia_cone = INFINITY;

                //verifica se o raio de luz intersecta a esfera, o chão e o fundo, e retorna essa distaância
                bool intersecaoEsfera = IntersecaoEsfera({ 0, 0, 0 }, dr, distancia_esfera, centro_esfera, rEsfera);
                bool intersecaoChao = IntersecaoPlano({ 0, 0, 0 }, dr, ponto_chao, normal_chao, distancia_chao);
                bool intersecaoFundo = IntersecaoPlano({ 0, 0, 0 }, dr, ponto_fundo, normal_fundo, distancia_fundo);
                bool intersecaoCilindro = IntersecaoCilindro({ 0, 0, 0 }, dr, distancia_cilindro, centrob_cilindro, rb_cilindro, hCilindro, d_cil);
                bool intersecaoCone = IntersecaoCone({ 0, 0, 0 }, dr, distancia_cone, centrob_cone, rb_cone, hCone, d_cone);


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

                if (intersecaoCilindro && distancia_cilindro < interseccao_minima) {
                    interseccao_minima = distancia_cilindro;
                    interseccao = vetor_escala(dr, distancia_cilindro);
                    normal = vetor_unitario(vetor_subtrair(interseccao, vetor_soma(centrob_cilindro, vetor_escala(d_cil, vetor_produto(vetor_subtrair(interseccao, centrob_cilindro), d_cil)))));
                    k_d = K_cilindro;
                    k_a = K_cilindro;
                    k_e = K_cilindro;
                    exp_especular = 10.0;
                }

                if (intersecaoCone && distancia_cone < interseccao_minima) {
                    interseccao_minima = distancia_cone;
                    interseccao = vetor_escala(dr, distancia_cone);
                    normal = vetor_unitario(vetor_subtrair(interseccao, vetor_soma(centrob_cone, vetor_escala(d_cone, vetor_produto(vetor_subtrair(interseccao, centrob_cone), d_cone)))));
                    k_d = K_cone;
                    k_a = K_cone;
                    k_e = K_cone;
                    exp_especular = 10.0;
                }

                if (interseccao_minima < INFINITY) {
                    vetor cor = luz_e_sombra(
                        interseccao, normal, dr_invertido, k_d, k_a, k_e, exp_especular, centro_esfera, rEsfera, ponto_chao, normal_chao, ponto_fundo, normal_fundo, centrob_cilindro, rb_cilindro, hCilindro, d_cil, centrob_cone, rb_cone, hCone, d_cone
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