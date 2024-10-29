#include "raylib.h"
#include "funcoes_utilitarias.cpp"

//O olho do pintor está na origem do sistema de coordenadas(0, 0, 0)


// dimensões da janela
float wJanela = 100;
float hJanela = 100;
 
//distância do olho até a janela 
float dJanela = 2;

//raio da esfera 
float rEsfera = 5;


// centro da esfera  - O centro da esfera deve estar sobre o eixo z com coordenada z < -(dJanela + rEsfera)
vetor centro_esfera = { 0.0, 0.0, -(dJanela + rEsfera) };

// cor da esfera    / A cor da esfera deve ser esfColor = 255, 0, 0
vetor esfColor = { 255.0, 0.0, 0.0 };

// cor do background  -  A cor de background deve ser cinza bgColor = 100, 100, 100
vetor bgColor = { 100.0, 100.0, 100.0 };



//o número de colunas
int nCol = 10;


//número de linhas
int nLin = 10;
 /*Note que
O loop aninhado mais externo é o loop de linhas que vai de 0 até nLin - 1.  ( for int l = 0; l < nLin; l++)
O loop aninhado mais interno é o loop de colunas que vai de 0 até nCol -1  (for int c =0; c < nCol; c++)

As dimensões dos retângulos da tela de mosquito são:
Dx = wJanela/nCol
Dy = hJanela/nLin

As coordenadas do ponto do centro de um retângulo da tela de mosquito correspondente ao retângulo (riscado a lápis) na posição (l, c) é dado por

x = - wJanela/2. + Dx/2  + c*Dx
y =.  hJanela/2.  -  Dy/2  -  l*Dy

Cada raio (semi reta) parte do olho do pintor E = (0,0, 0) e  passa pelo ponto (x, y, -dJanela).

Caso o raio enviado não tenha interseção com a esfera, armazene a cor de background na posição (l, c) da matriz de cores do Canvas.
Caso o raio tangencie ou tenha interseção plena com a esfera, armazene a cor da esfera (esfColor) na posição (l, c) da matriz de cores do Canvas.*/


int main(void) {

}