#include "Forca.h"
#include <iostream>
#include <iomanip>

// Construtor novo
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {}

// Construtor arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {}

void Forca::exibirDetalhes() const {
    std::cout << "Tipo: Forca\n";
    std::cout << "ID: " << id << " | Nome: " << nome << " | Status: " << (ativo ? "Ativo" : "Inativo") << "\n";
    std::cout << "Carga: " << carga << " kg | Series: " << series << " | Repeticoes: " << repeticoes
              << " | Descanso: " << tempoDescanso << " s\n";
}

double Forca::calcularTempoEstimado() const {
    // Fórmula do enunciado:
    // (Series × Repeticoes × 3 seg) + (Series × Tempo de Descanso)
    double totalSegundos = (static_cast<double>(series) * repeticoes * 3.0)
                          + (static_cast<double>(series) * tempoDescanso);
    return totalSegundos / 60.0; // retorna em minutos
}

double Forca::calcularCaloriasGastas() const {
    // Fórmula do enunciado:
    // Series × Repeticoes × Carga × 0.15
    return static_cast<double>(series) * repeticoes * carga * 0.15;
}

int Forca::getTipo() const {
    return 2;
}

double Forca::getCarga() const { return carga; }
int Forca::getSeries() const { return series; }
int Forca::getRepeticoes() const { return repeticoes; }
int Forca::getTempoDescanso() const { return tempoDescanso; }
