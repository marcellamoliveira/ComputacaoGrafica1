#include "funcoes.h"
#include <cmath>

// retorna o tamanho de um vetor
float vetor_tamanho(const vetor& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// escala um vetor pelo valor do escalar
vetor vetor_escala(const vetor& v, float escalar) {
    return { v.x * escalar, v.y * escalar, v.z * escalar };
}

// produto escalar de dois vetores
float vetor_produto(const vetor& v1, const vetor& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// subtração de dois vetores
vetor vetor_subtrair(const vetor& v1, const vetor& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// soma de dois vetores
vetor vetor_soma(const vetor& v1, const vetor& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// multiplica dois vetores
vetor vetor_multiplica(const vetor& v1, const vetor& v2) {
    return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

// normalizar um vetor, tornando-o unitário
vetor vetor_unitario(const vetor& v) {
    float tamanho = vetor_tamanho(v);
    if (tamanho > 0) {
        return vetor_escala(v, 1 / tamanho);
    }
    return { 0, 0, 0 };
}

//encontra o maior
double maximo(float a, float b) {
    if (a > b) {
        return a;
    }
    else return b;
}

//encontrar o menor
double minimo(float a, float b) {
    if (a < b) {
        return a;
    }
    else return b;
}