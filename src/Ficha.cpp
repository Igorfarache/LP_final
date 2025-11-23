#include "Ficha.h"
#include <iostream>

int Ficha::proximoId = 1;

Ficha::Ficha(std::string nome)
    : id(proximoId++), nome(nome) {}

Ficha::Ficha(int id, std::string nome)
    : id(id), nome(nome) {
    if (id >= proximoId) proximoId = id + 1;
}

Ficha::~Ficha() {
    // Não deletamos os exercícios porque o dono dos exercícios é o Sistema (evitar double-delete)
}

void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if (exercicio) exercicios.push_back(exercicio);
}

void Ficha::exibirFicha() const {
    std::cout << "=== FICHA ID: " << id << " - " << nome << " ===\n";
    if (exercicios.empty()) {
        std::cout << "(Nenhum exercicio nesta ficha)\n";
        return;
    }
    for (auto* e : exercicios) {
        if (e) {
            std::cout << "-> [" << e->getId() << "] " << e->getNome() << " | ";
            e->exibirDetalhes();
        }
    }
    double tempo = calcularTempoTotal();
    double calorias = calcularCaloriasTotais();
    std::cout << "TOTAL (estimado): Tempo = " << tempo << " min | Calorias = " << calorias << "\n";
}

double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (auto* e : exercicios) {
        if (e && e->isAtivo()) total += e->calcularTempoEstimado();
    }
    return total;
}

double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (auto* e : exercicios) {
        if (e && e->isAtivo()) total += e->calcularCaloriasGastas();
    }
    return total;
}

int Ficha::getId() const { return id; }
std::string Ficha::getNome() const { return nome; }
const std::vector<Exercicio*>& Ficha::getExercicios() const { return exercicios; }

void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) proximoId = maiorId + 1;
}
