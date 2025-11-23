#include "Exercicio.h"

int Exercicio::proximoId = 1;

// Construtor para novos cadastros: usa proximoId e incrementa
Exercicio::Exercicio(std::string nome)
    : id(proximoId++), nome(nome), ativo(true) {}

// Construtor para leitura de arquivo: usa ID fornecido e atualiza proximoId se necessário
Exercicio::Exercicio(int id, std::string nome, bool ativo)
    : id(id), nome(nome), ativo(ativo) {
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

Exercicio::~Exercicio() {}

int Exercicio::getId() const { return id; }
std::string Exercicio::getNome() const { return nome; }
bool Exercicio::isAtivo() const { return ativo; }

void Exercicio::desativar() { ativo = false; }

void Exercicio::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) proximoId = maiorId + 1;
}
