#include "declaracoes.h"
#include <cmath>

// retorna o tamanho de um vetor
float funcoes :: vetor_tamanho(vetor v) { 
    float tamanho = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return tamanho;
}

// escala um vetor pelo valor do escalar
vetor funcoes::vetor_escala(vetor v, float escalar) {
    vetor escalonado = { v.x * escalar, v.y * escalar, v.z * escalar };
    return escalonado;
}

// produto escalar de dois vetores
float funcoes::vetor_produto(vetor v1, vetor v2) {
    float produto = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return produto;
}

// subtração de dois vetores
vetor funcoes::vetor_subtrair(vetor v1, vetor v2) {
    vetor subtracao = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return subtracao;
}

//soma de dois vetores
vetor funcoes::vetor_soma(vetor v1, vetor v2) {
    vetor soma = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return soma;
}

//multiplica dois vetores
vetor funcoes::vetor_multiplica(vetor v1, vetor v2) {
    vetor produto = { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
    return produto;
}

//normalizar um vetor, tornando-o unitário
vetor funcoes::vetor_unitario(vetor v) {
    float tamanho = vetor_tamanho(v);
    if (tamanho > 0) {
        return vetor_escala(v, 1 / tamanho);
    }
    else {
        return vetor{0,0,0};
    }
}

