#include "Cardio.h"
#include <iostream>
#include <iomanip>

// Construtor novo
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto)
    : Exercicio(nome), duracao(duracao), caloriasPorMinuto(caloriasPorMinuto) {}

// Construtor arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo), duracao(duracao), caloriasPorMinuto(caloriasPorMinuto) {}

void Cardio::exibirDetalhes() const {
    std::cout << "Tipo: Cardio\n";
    std::cout << "ID: " << id << " | Nome: " << nome << " | Status: " << (ativo ? "Ativo" : "Inativo") << "\n";
    std::cout << "Duracao: " << duracao << " min | Calorias/min: " << caloriasPorMinuto << "\n";
}

double Cardio::calcularTempoEstimado() const {
    // Tempo estimado é exatamente a duração (em minutos)
    return static_cast<double>(duracao);
}

double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto;
}

int Cardio::getTipo() const {
    return 1;
}

int Cardio::getDuracao() const {
    return duracao;
}

double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto;
}
