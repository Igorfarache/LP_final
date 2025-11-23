#include "Historico.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

void Historico::exibirHistorico() const {
    std::cout << "=== HISTORICO DE TREINOS ===\n";
    if (registros.empty()) {
        std::cout << "(Nenhum registro)\n";
        return;
    }
    for (const auto& r : registros) {
        std::cout << r.dataHora << ";" << r.idFicha << ";" << r.nomeFicha
                  << ";" << r.tempoTotal << ";" << r.caloriasTotal << "\n";
    }
}

const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

void Historico::carregarDeArquivo() {
    registros.clear();
    std::ifstream in("historico.txt");
    if (!in.is_open()) return;

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        RegistroTreino r;
        std::string token;

        // DATA (formato: DD/MM/YYYY HH:MM:SS)
        std::getline(ss, token, ';');
        r.dataHora = token;

        // ID_FICHA
        std::getline(ss, token, ';');
        r.idFicha = stoi(token);

        // NOME_FICHA
        std::getline(ss, token, ';');
        r.nomeFicha = token;

        // TEMPO_TOTAL
        std::getline(ss, token, ';');
        r.tempoTotal = stod(token);

        // CALORIAS_TOTAL
        std::getline(ss, token, ';');
        r.caloriasTotal = stod(token);

        registros.push_back(r);
    }

    in.close();
}

void Historico::salvarEmArquivo() const {
    std::ofstream out("historico.txt");
    if (!out.is_open()) return;

    for (const auto& r : registros) {
        out << r.dataHora << ";" << r.idFicha << ";" << r.nomeFicha
            << ";" << r.tempoTotal << ";" << r.caloriasTotal << "\n";
    }

    out.close();
}
