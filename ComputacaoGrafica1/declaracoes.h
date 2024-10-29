#pragma once  //diretiva de pré-processador que faz o arquivo ser compilado uma vez só

struct vetor {
	float x;
	float y;
	float z;
};

class funcoes {
public:
    static float vetor_tamanho(vetor v);

    static vetor vetor_escala(vetor v, float escalar);

    static float vetor_produto(vetor v1, vetor v2);

    static vetor vetor_subtrair(vetor v1, vetor v2);

    static vetor vetor_soma(vetor v1, vetor v2);

    static vetor vetor_multiplica(vetor v1, vetor v2);

    static vetor vetor_unitario(vetor v);
};