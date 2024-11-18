#pragma once

struct vetor {
    float x, y, z;
};

// Funções utilitárias para operações com vetores
float vetor_tamanho(const vetor& v);
vetor vetor_escala(const vetor& v, float escalar);
float vetor_produto(const vetor& v1, const vetor& v2);
vetor vetor_subtrair(const vetor& v1, const vetor& v2);
vetor vetor_soma(const vetor& v1, const vetor& v2);
vetor vetor_multiplica(const vetor& v1, const vetor& v2);
vetor vetor_unitario(const vetor& v);
double maximo(float a, float b);
double minimo(float a, float b);

bool IntersecaoEsfera(const vetor& origem, const vetor& dr, double& distancia, const vetor& centro_esfera, float rEsfera);
bool IntersecaoPlano(const vetor& origem, const vetor& dr, const vetor& ponto, const vetor& normal, double& distancia);

vetor vetor_reflexao(const vetor& v, const vetor& normal);

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
    const vetor& d_cone

);


bool IntersecaoCilindro(const vetor& origem, const vetor& dr, double& distancia, const vetor& centrob_cone, float rb_cilindro, float hCilindro, const vetor& direcao);
bool IntersecaoCone(const vetor& origem, const vetor& dr, double& distancia, const vetor& centrob_cone, float rb_cone, float hCone, const vetor& direcao);