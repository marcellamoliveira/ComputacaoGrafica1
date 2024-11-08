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




// cor da esfera    / A cor da esfera deve ser esfColor = 255, 0, 0
vetor esfColor = { 255.0, 0.0, 0.0 };

// cor do background  -  A cor de background deve ser cinza bgColor = 100, 100, 100
vetor bgColor = { 100.0, 100.0, 100.0 };

//olho do pintor
vetor E = { 0.0f, 0.0f, 0.0f };




// I_F = Intensidade da da fonte pontual
vetor Intensidade_Fonte = { 0.7, 0.7, 0.7 };       

// P_F - Posição da fonte pontual situada a 5 metros acima do olho do observador.
vetor Posicao_Fonte = { 0.0, 5.0, 0.0 };       



// Material da esfera e fonte de luz
const vetor sphereMaterial = { 1.0, 0.0, 0.0 }; // Cor da esfera
const double specularExponent = 50.0;           // Expoente para iluminação especular







int main() {

    //iniciar a janela
    InitWindow(wTela, hTela, "Atividade 2");
    SetTargetFPS(60);

    //inicialização o dx e o dy
    double dx = wJanela / nCol;
    double dy = hJanela / nLin;

    // Tamanho dos retângulos na janela para cada ponto do frame
    int pixelWidth = wTela / nCol;
    int pixelHeight = hTela / nLin;

    // Loop principal de renderização
    while (!WindowShouldClose()) {
        // Controle de movimentação da esfera e ajuste da distância do frame
        if (IsKeyDown(KEY_W)) dJanela += 0.05;
        if (IsKeyDown(KEY_S) && dJanela > 0.10) dJanela -= 0.05;
        if (IsKeyDown(KEY_J)) centro_esfera.y += 0.05;
        if (IsKeyDown(KEY_K)) centro_esfera.y -= 0.05;
        if (IsKeyDown(KEY_H)) centro_esfera.x -= 0.05;
        if (IsKeyDown(KEY_L)) centro_esfera.x += 0.05;

        // Configuração do ponto superior esquerdo do frame
        vetor topLeft = { -wJanela * 0.5, hJanela * 0.5, -dJanela };

        // Vetor que vai do observador ao centro da esfera
        vetor viewToSphere = vetor_escala(centro_esfera, -1);

        BeginDrawing();
        ClearBackground(Color{ 100, 100, 100});

        // Loop sobre as linhas e colunas do frame
        for (int i = 0; i < nLin; ++i) {
            double yp = topLeft.y - dy * 0.5 - i * dy;
            for (int j = 0; j < nCol; ++j) {
                double xp = topLeft.x + dx * j + dx * 0.5;
                vetor P = { xp, yp, -dJanela };

                // Vetor normalizado do observador até o ponto P
                vetor dr = vetor_unitario(P);

                // Coeficientes da equação quadrática para interseção com a esfera
                double a = vetor_produto(dr, dr);
                double b = 2 * vetor_produto(dr, viewToSphere);
                double c = vetor_produto(viewToSphere, viewToSphere) - rEsfera * rEsfera;
                double discriminant = b * b - 4 * a * c;

                // Verificação de interseção com a esfera
                if (discriminant < 0.0) continue;

                double t = (-b - sqrt(discriminant)) / (2 * a);
                if (t < 0.0) t = (-b + sqrt(discriminant)) / (2 * a);
                if (t < 0.0) continue;

                // Ponto de interseção e normal no ponto
                vetor intersection = vetor_escala(dr, t);
                vetor normal = vetor_unitario(vetor_subtrair(intersection, centro_esfera));

                // Cálculo dos vetores para iluminação
                vetor viewDir = vetor_escala(dr, -1);
                vetor lightDir = vetor_unitario(vetor_subtrair(Posicao_Fonte, intersection));
                vetor reflected = vetor_subtrair(vetor_escala(normal, 2 * vetor_produto(normal, lightDir)), lightDir);

                // Iluminação difusa e especular
                vetor diffuse = vetor_escala(vetor_multiplica(sphereMaterial, Intensidade_Fonte),
                    maximo(vetor_produto(lightDir, normal), 0));
                vetor specular = vetor_escala(vetor_multiplica(sphereMaterial, Intensidade_Fonte),
                    maximo(pow(vetor_produto(viewDir, reflected), specularExponent), 0));

                // Intensidade total da luz
                vetor totalIntensity = vetor_soma(diffuse, specular);

                // Conversão da intensidade de luz para valores de cor (0-255)
                Color pixelColor = Color{
                    static_cast<unsigned char>(minimo(totalIntensity.x * 255.0, 255.0)),
                    static_cast<unsigned char>(minimo(totalIntensity.y * 255.0, 255.0)),
                    static_cast<unsigned char>(minimo(totalIntensity.z * 255.0, 255.0)),
                    255
                };

                // Desenho do pixel
                DrawRectangle(pixelWidth * j, pixelHeight * i, pixelWidth, pixelHeight, pixelColor);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}