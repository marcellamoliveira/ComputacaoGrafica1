#include <cmath>
#include <raylib.h>
#include "funcoes.h"

// Dimensões da janela
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Dimensões físicas do frame virtual (na cena 3D)
const float FRAME_WIDTH = 8.0;
const float FRAME_HEIGHT = 6.0;

// Resolução do frame
const int FRAME_ROWS = 600;
const int FRAME_COLS = 800;

// Parâmetros da cena
float frameDist = 2.0;                 // Distância do frame ao observador
float sphereRadius = 6.0;             // Raio da esfera
vetor sphereCenter = { 0.0, 0.0, -10.0 }; // Centro da esfera

// Material da esfera e fonte de luz
const vetor sphereMaterial = { 1.0, 0.0, 0.0 }; // Cor da esfera
const double specularExponent = 50.0;           // Expoente para iluminação especular
vetor lightIntensity = { 0.7, 0.7, 0.7 };       // Intensidade da luz
vetor lightPosition = { 0.0, 5.0, 0.0 };        // Posição da luz

// Funções auxiliares para cálculo do máximo e mínimo
double max(double a, double b) { return (a > b) ? a : b; }
double min(double a, double b) { return (a < b) ? a : b; }

int main() {
    // Inicialização da janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raytracing");
    SetTargetFPS(60);

    // Passo em x e y no frame virtual
    double dx = FRAME_WIDTH / FRAME_COLS;
    double dy = FRAME_HEIGHT / FRAME_ROWS;

    // Tamanho dos retângulos na janela para cada ponto do frame
    int pixelWidth = SCREEN_WIDTH / FRAME_COLS;
    int pixelHeight = SCREEN_HEIGHT / FRAME_ROWS;

    // Loop principal de renderização
    while (!WindowShouldClose()) {
        // Controle de movimentação da esfera e ajuste da distância do frame
        if (IsKeyDown(KEY_W)) frameDist += 0.05;
        if (IsKeyDown(KEY_S) && frameDist > 0.10) frameDist -= 0.05;
        if (IsKeyDown(KEY_J)) sphereCenter.y += 0.05;
        if (IsKeyDown(KEY_K)) sphereCenter.y -= 0.05;
        if (IsKeyDown(KEY_H)) sphereCenter.x -= 0.05;
        if (IsKeyDown(KEY_L)) sphereCenter.x += 0.05;

        // Configuração do ponto superior esquerdo do frame
        vetor topLeft = { -FRAME_WIDTH * 0.5, FRAME_HEIGHT * 0.5, -frameDist };

        // Vetor que vai do observador ao centro da esfera
        vetor viewToSphere = vetor_escala(sphereCenter, -1);

        BeginDrawing();
        ClearBackground(Color{ 100, 100, 100, 255 });

        // Loop sobre as linhas e colunas do frame
        for (int i = 0; i < FRAME_ROWS; ++i) {
            double yp = topLeft.y - dy * 0.5 - i * dy;
            for (int j = 0; j < FRAME_COLS; ++j) {
                double xp = topLeft.x + dx * j + dx * 0.5;
                vetor P = { xp, yp, -frameDist };

                // Vetor normalizado do observador até o ponto P
                vetor dr = vetor_unitario(P);

                // Coeficientes da equação quadrática para interseção com a esfera
                double a = vetor_produto(dr, dr);
                double b = 2 * vetor_produto(dr, viewToSphere);
                double c = vetor_produto(viewToSphere, viewToSphere) - sphereRadius * sphereRadius;
                double discriminant = b * b - 4 * a * c;

                // Verificação de interseção com a esfera
                if (discriminant < 0.0) continue;

                double t = (-b - sqrt(discriminant)) / (2 * a);
                if (t < 0.0) t = (-b + sqrt(discriminant)) / (2 * a);
                if (t < 0.0) continue;

                // Ponto de interseção e normal no ponto
                vetor intersection = vetor_escala(dr, t);
                vetor normal = vetor_unitario(vetor_subtrair(intersection, sphereCenter));

                // Cálculo dos vetores para iluminação
                vetor viewDir = vetor_escala(dr, -1);
                vetor lightDir = vetor_unitario(vetor_subtrair(lightPosition, intersection));
                vetor reflected = vetor_subtrair(vetor_escala(normal, 2 * vetor_produto(normal, lightDir)), lightDir);

                // Iluminação difusa e especular
                vetor diffuse = vetor_escala(vetor_multiplica(sphereMaterial, lightIntensity),
                    max(vetor_produto(lightDir, normal), 0));
                vetor specular = vetor_escala(vetor_multiplica(sphereMaterial, lightIntensity),
                    max(pow(vetor_produto(viewDir, reflected), specularExponent), 0));

                // Intensidade total da luz
                vetor totalIntensity = vetor_soma(diffuse, specular);

                // Conversão da intensidade de luz para valores de cor (0-255)
                Color pixelColor = Color{
                    static_cast<unsigned char>(min(totalIntensity.x * 255.0, 255.0)),
                    static_cast<unsigned char>(min(totalIntensity.y * 255.0, 255.0)),
                    static_cast<unsigned char>(min(totalIntensity.z * 255.0, 255.0)),
                    255
                };

                // Desenho do pixel
                DrawRectangle(pixelWidth * j, pixelHeight * i, pixelWidth, pixelHeight, pixelColor);
            }
        }

        EndDrawing();
    }

    CloseWindow(); // Fechar a janela corretamente
    return 0;
}