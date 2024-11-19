#include "funcoes.h"
#include <cmath>
#include <iostream>

// Calcula o tamanho do vetor
float vetor_tamanho(const vetor& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Escala um vetor por um escalar
vetor vetor_escala(const vetor& v, float escalar) {
    return { v.x * escalar, v.y * escalar, v.z * escalar };
}

// Produto escalar entre dois vetores
float vetor_produto(const vetor& v1, const vetor& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Subtrai dois vetores
vetor vetor_subtrair(const vetor& v1, const vetor& v2) {
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

// Soma dois vetores
vetor vetor_soma(const vetor& v1, const vetor& v2) {
    return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

// Multiplica dois vetores componente a componente
vetor vetor_multiplica(const vetor& v1, const vetor& v2) {
    return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

// Normaliza um vetor
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

// função para interseção com uma esfera
bool IntersecaoEsfera(const vetor& origem, const vetor& dr, double& distancia, const vetor& centro_esfera, float rEsfera) {
    vetor diferenca = vetor_subtrair(origem, centro_esfera);
    double a = vetor_produto(dr, dr);
    double b = 2 * vetor_produto(dr, diferenca);
    double c = vetor_produto(diferenca, diferenca) - rEsfera * rEsfera;
    double delta = b * b - 4 * a * c;

    if (delta < 0.0) return false;

    double r1 = (-b - sqrt(delta)) / (2 * a);
    double r2 = (-b + sqrt(delta)) / (2 * a);
    distancia = (r1 > 0.0) ? r1 : r2;
    return distancia > 0.0;
}



bool IntersecaoCilindro(const vetor& origem, const vetor& dr, double& distancia, const vetor& centrob_cilindro, float rb_cilindro, float hCilindro, const vetor& direcao) {
    /*vetor w = vetor_subtrair(dr, vetor_multiplica(dr, vetor_multiplica(direcao, direcao)));
    vetor oc = vetor_subtrair(origem, centrob_cilindro);
    vetor v = vetor_subtrair(oc, vetor_multiplica(oc, vetor_multiplica(direcao, direcao)));

    float a = vetor_tamanho(vetor_multiplica(w, w));
    float b = vetor_tamanho(vetor_multiplica(w, w));
    float c = vetor_tamanho(vetor_multiplica(v,v)) - rb_cilindro*rb_cilindro;*/
    
    vetor oc = vetor_subtrair(origem, centrob_cilindro);

    float a = vetor_produto(dr, dr) - pow(vetor_produto(dr, direcao), 2);
    float b = 2 * (vetor_produto(dr, oc) - vetor_produto(dr, direcao) * vetor_produto(oc, direcao));
    float c = vetor_produto(oc, oc) - pow(vetor_produto(oc, direcao), 2) - rb_cilindro * rb_cilindro;

    double delta = b * b - 4 * a * c;
    if (delta < 0) return false;

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);

    double t = t1 > 0 ? t1 : t2;
    vetor ponto_interseccao = vetor_soma(origem, vetor_escala(dr, t));
    float distancia_alongamento = vetor_produto(vetor_subtrair(ponto_interseccao, centrob_cilindro), direcao);

    if (distancia_alongamento >= 0 && distancia_alongamento <= hCilindro) {
        distancia = t;
        return true;
    }
    return false;
}




bool IntersecaoCone(const vetor& origem, const vetor& dr, double& distancia, const vetor& centrob_cone, float rb_cone, float hCone, const vetor& direcao) {
        vetor oc = vetor_subtrair(origem, centrob_cone);
        float cos_theta = hCone / sqrt(hCone * hCone + rb_cone * rb_cone);
        float cos_theta2 = cos_theta * cos_theta;

        vetor direcao_normalizada = vetor_unitario(direcao);
        vetor dr_novo = vetor_unitario(dr);

        float d_dot_v = vetor_produto(dr_novo, direcao_normalizada);
        float oc_dot_v = vetor_produto(oc, direcao_normalizada);

        float a = vetor_produto(dr_novo, dr_novo) - cos_theta2 * d_dot_v * d_dot_v;
        float b = 2 * (vetor_produto(dr_novo, oc) - cos_theta2 * d_dot_v * oc_dot_v);
        float c = vetor_produto(oc, oc) - cos_theta2 * oc_dot_v * oc_dot_v;

        double delta = b * b - 4 * a * c;
        //std::cout << "a" << a << ", b " << b << "c   " << c << "delta   " << delta << "\n";
        if (delta < 0) return false;

        double t1 = (-b - sqrt(delta)) / (2 * a);
        double t2 = (-b + sqrt(delta)) / (2 * a);

        double t = t1 > 0 ? t1 : t2;
        if (t < 0) return false;
        vetor ponto_interseccao = vetor_soma(origem, vetor_escala(dr_novo, t));
        float distancia_alongamento = vetor_produto(vetor_subtrair(ponto_interseccao, centrob_cone), direcao_normalizada);

        if (distancia_alongamento >-1e-6 && distancia_alongamento <= hCone + 1e-6) {
            distancia = t;
            return true;
        }
        return false;
}

// função para interseção com um plano
bool IntersecaoPlano(const vetor& origem, const vetor& dr, const vetor& ponto, const vetor& normal, double& distancia) {
    double produto = vetor_produto(dr, normal);
    if (fabs(produto) > 1e-6) {   //evita divisões por zero
        vetor diferenca = vetor_subtrair(ponto, origem);
        distancia = vetor_produto(diferenca, normal) / produto;
        return distancia > 0.0;
    }
    return false;
}

// cálculo da direção da reflexão apartir da normal
vetor vetor_reflexao(const vetor& L, const vetor& normal) {
    double escalar = 2.0 * vetor_produto(L, normal);
    vetor projecao = vetor_escala(normal, escalar);
    return vetor_subtrair(L, projecao);  
}


vetor luz_e_sombra(  
    const vetor& interseccao,
    const vetor& normal,
    const vetor& dr_invertido,
    const vetor& k_d,
    const vetor& k_a,
    const vetor& k_e,
    double exp_especular,
    const vetor& centro_esfera,
    float rEsfera,
    const vetor& ponto_chao,
    const vetor& normal_chao,
    const vetor& ponto_fundo,
    const vetor& normal_fundo,
    const vetor& centrob_cilindro,
    float rb_cilindro,
    float hCilindro,
    const vetor& d_cil,
    const vetor& centrob_cone,
    float rb_cone,
    float hCone,
    const vetor& d_cone) {

    vetor Intensidade_Fonte = { 0.7, 0.7, 0.7 };
    vetor Posicao_Fonte = { 0.0, 60.0, -30.0 };
    vetor Intensidade_Ambiente = { 0.3, 0.3, 0.3 };

    vetor L = vetor_unitario(vetor_subtrair(Posicao_Fonte, interseccao));

    vetor I_ambiente = vetor_multiplica(k_a, Intensidade_Ambiente);
    vetor I_difusa = { 0.0, 0.0, 0.0 };
    vetor I_especular = { 0.0, 0.0, 0.0 };

    double t_sombra_esfera = INFINITY;
    double t_sombra_cilindro = INFINITY;
    double t_sombra_cone = INFINITY;

    bool sombra_esfera = IntersecaoEsfera(interseccao, L, t_sombra_esfera, centro_esfera, rEsfera) && t_sombra_esfera > 0.001;
    bool sombra_cilindro = IntersecaoCilindro(interseccao, L, t_sombra_cilindro, centrob_cilindro, rb_cilindro, hCilindro, d_cil) && t_sombra_cilindro > 0.001;
    bool sombra_cone = IntersecaoCone(interseccao, L, t_sombra_cone, centrob_cone, rb_cone, hCone, d_cone) && t_sombra_cone > 0.001;
   
    //se a intersecç~~ao nao tiver
    if (!sombra_esfera && !sombra_cilindro && !sombra_cone) {
        //componente difusa
        double cos_theta = maximo(vetor_produto(normal, L), 0.0);
        I_difusa = vetor_multiplica(k_d, vetor_escala(Intensidade_Fonte, cos_theta));

        //componente especular
        vetor R = vetor_reflexao(L, normal);
        double cos_alpha = maximo(vetor_produto(R, dr_invertido), 0.0);
        double fator_especular = 0.05*pow(cos_alpha, exp_especular);
        I_especular = vetor_multiplica(k_e, vetor_escala(Intensidade_Fonte, fator_especular));
    }

    return vetor_soma(I_ambiente, vetor_soma(I_difusa, I_especular));
}











