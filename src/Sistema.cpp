#include "Sistema.h"
#include "Forca.h"
#include "Cardio.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <limits>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    // o sistema é dono dos objetos Exercicio e das Fichas -> liberar memória
    for (auto* e : exercicios) delete e;
    for (auto* f : fichas) delete f;
}

Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto* e : exercicios) {
        if (e && e->getId() == id) return e;
    }
    return nullptr;
}

Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto* f : fichas) {
        if (f && f->getId() == id) return f;
    }
    return nullptr;
}

void Sistema::carregarDados() {
    // ---------- exercicios.txt ----------
    exercicios.clear();
    std::ifstream inEx("exercicios.txt");
    if (inEx.is_open()) {
        std::string linha;
        while (std::getline(inEx, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string token;

            // Formato: TIPO;ID;NOME;...;STATUS
            std::getline(ss, token, ';'); int tipo = stoi(token);
            std::getline(ss, token, ';'); int id = stoi(token);
            std::string nome;
            std::getline(ss, nome, ';');

            if (tipo == 1) {
                // Cardio: DURACAO;CALORIAS_POR_MIN;STATUS
                std::getline(ss, token, ';'); int dur = stoi(token);
                std::getline(ss, token, ';'); double calpm = stod(token);
                std::getline(ss, token, ';'); bool ativo = (token == "1");
                Cardio* c = new Cardio(id, nome, ativo, dur, calpm);
                exercicios.push_back(c);
            } else if (tipo == 2) {
                // Força: CARGA;SERIES;REPETICOES;DESCANSO;STATUS
                std::getline(ss, token, ';'); double carga = stod(token);
                std::getline(ss, token, ';'); int series = stoi(token);
                std::getline(ss, token, ';'); int reps = stoi(token);
                std::getline(ss, token, ';'); int descanso = stoi(token);
                std::getline(ss, token, ';'); bool ativo = (token == "1");
                Forca* f = new Forca(id, nome, ativo, carga, series, reps, descanso);
                exercicios.push_back(f);
            }
        }
        inEx.close();
    }

    // ---------- fichas.txt ----------
    fichas.clear();
    std::ifstream inF("fichas.txt");
    if (inF.is_open()) {
        std::string linha;
        while (std::getline(inF, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string token;

            // Formato: ID_FICHA;NOME_FICHA;TOTAL_EXERCICIOS;ID_EX_1;ID_EX_2;...
            std::getline(ss, token, ';'); int idFicha = stoi(token);
            std::string nomeFicha;
            std::getline(ss, nomeFicha, ';');
            std::getline(ss, token, ';'); int totalEx = stoi(token);

            Ficha* f = new Ficha(idFicha, nomeFicha);

            for (int i = 0; i < totalEx; ++i) {
                if (!std::getline(ss, token, ';')) break;
                if (token.empty()) continue;
                int idEx = stoi(token);
                Exercicio* e = buscarExercicioPorId(idEx);
                if (e) f->adicionarExercicio(e);
            }
            fichas.push_back(f);
        }
        inF.close();
    }

    // ---------- historico.txt ----------
    historico.carregarDeArquivo();
}

void Sistema::salvarDados() {
    // ---------- exercicios.txt ----------
    std::ofstream outEx("exercicios.txt");
    if (outEx.is_open()) {
        for (auto* e : exercicios) {
            if (!e) continue;
            int tipo = e->getTipo();
            // COMMON prefix: TIPO;ID;NOME;
            outEx << tipo << ";" << e->getId() << ";" << e->getNome() << ";";
            if (tipo == 1) {
                Cardio* c = dynamic_cast<Cardio*>(e);
                outEx << c->getDuracao() << ";" << c->getCaloriasPorMinuto() << ";" << (e->isAtivo() ? "1" : "0");
            } else if (tipo == 2) {
                Forca* f = dynamic_cast<Forca*>(e);
                outEx << f->getCarga() << ";" << f->getSeries() << ";" << f->getRepeticoes() << ";" << f->getTempoDescanso() << ";" << (e->isAtivo() ? "1" : "0");
            }
            outEx << "\n";
        }
        outEx.close();
    }

    // ---------- fichas.txt ----------
    std::ofstream outF("fichas.txt");
    if (outF.is_open()) {
        for (auto* f : fichas) {
            outF << f->getId() << ";" << f->getNome() << ";";
            const auto& vec = f->getExercicios();
            outF << vec.size();
            for (auto* e : vec) {
                outF << ";" << e->getId();
            }
            outF << "\n";
        }
        outF.close();
    }

    // ---------- historico.txt ----------
    historico.salvarEmArquivo();
}

void Sistema::cadastrarExercicio() {
    limparTela();
    std::cout << "--- CADASTRAR EXERCICIO ---\n";
    std::cout << "1 - Cardio\n2 - Forca\nOpcao: ";
    int opc;
    if (!(std::cin >> opc)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada invalida.\n";
        pausar();
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (opc == 1) {
        std::string nome;
        int dur;
        double calpm;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        std::cout << "Duracao (minutos): ";
        std::cin >> dur;
        std::cout << "Calorias por minuto: ";
        std::cin >> calpm;
        Cardio* c = new Cardio(nome, dur, calpm);
        exercicios.push_back(c);
        std::cout << "Cardio cadastrado com ID " << c->getId() << "\n";
    } else if (opc == 2) {
        std::string nome;
        double carga;
        int series, repeticoes, descanso;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        std::cout << "Carga (kg): ";
        std::cin >> carga;
        std::cout << "Series: ";
        std::cin >> series;
        std::cout << "Repeticoes por serie: ";
        std::cin >> repeticoes;
        std::cout << "Tempo de descanso (segundos): ";
        std::cin >> descanso;
        Forca* f = new Forca(nome, carga, series, repeticoes, descanso);
        exercicios.push_back(f);
        std::cout << "Forca cadastrada com ID " << f->getId() << "\n";
    } else {
        std::cout << "Opcao invalida.\n";
    }
    pausar();
}

void Sistema::listarExercicios() const {
    limparTela();
    std::cout << "--- EXERCICIOS (apenas Ativos) ---\n";
    bool any = false;
    for (auto* e : exercicios) {
        if (e && e->isAtivo()) {
            any = true;
            std::cout << "[" << e->getId() << "] " << e->getNome() << " | ";
            e->exibirDetalhes();
        }
    }
    if (!any) std::cout << "(Nenhum exercicio ativo cadastrado)\n";
    pausar();
}

void Sistema::excluirExercicio() {
    limparTela();
    std::cout << "--- EXCLUIR (DESATIVAR) EXERCICIO ---\n";

    // Listar todos (ativos e inativos) para facilitar a escolha
    for (auto* e : exercicios) {
        if (e) {
            std::cout << "[" << e->getId() << "] " << e->getNome() << " | Status: " << (e->isAtivo() ? "Ativo" : "Inativo") << "\n";
        }
    }

    std::cout << "Digite o ID do exercicio para desativar: ";
    int id;
    std::cin >> id;
    Exercicio* e = buscarExercicioPorId(id);
    if (e) {
        e->desativar();
        std::cout << "Exercicio desativado com sucesso.\n";
    } else {
        std::cout << "Exercicio nao encontrado.\n";
    }
    pausar();
}

void Sistema::criarFicha() {
    limparTela();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "--- CRIAR FICHA ---\n";
    std::string nome;
    std::cout << "Nome da ficha: ";
    std::getline(std::cin, nome);
    Ficha* f = new Ficha(nome);
    fichas.push_back(f);
    std::cout << "Ficha criada com ID " << f->getId() << "\n";
    pausar();
}

void Sistema::adicionarExercicioFicha() {
    limparTela();
    std::cout << "--- ADICIONAR EXERCICIO A FICHA ---\n";
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        pausar();
        return;
    }

    // listar fichas resumido
    for (auto* f : fichas) {
        std::cout << "ID: " << f->getId() << " | " << f->getNome() << " | Exercicios: " << f->getExercicios().size() << "\n";
    }

    std::cout << "Digite o ID da ficha: ";
    int idFicha;
    std::cin >> idFicha;
    Ficha* f = buscarFichaPorId(idFicha);
    if (!f) {
        std::cout << "Ficha nao encontrada.\n";
        pausar();
        return;
    }

    // listar exercicios (ativos apenas)
    std::cout << "Exercicios ativos:\n";
    for (auto* e : exercicios) {
        if (e && e->isAtivo()) {
            std::cout << "[" << e->getId() << "] " << e->getNome() << "\n";
        }
    }

    std::cout << "Digite o ID do exercicio para adicionar: ";
    int idEx;
    std::cin >> idEx;
    Exercicio* ex = buscarExercicioPorId(idEx);
    if (!ex) {
        std::cout << "Exercicio nao encontrado.\n";
        pausar();
        return;
    }
    f->adicionarExercicio(ex);
    std::cout << "Exercicio adicionado na ficha.\n";
    pausar();
}

void Sistema::listarFichas() const {
    limparTela();
    std::cout << "--- FICHAS ---\n";
    if (fichas.empty()) {
        std::cout << "(Nenhuma ficha cadastrada)\n";
        pausar();
        return;
    }
    for (auto* f : fichas) {
        f->exibirFicha();
        std::cout << "-------------------------\n";
    }
    pausar();
}

void Sistema::registrarTreino() {
    limparTela();
    std::cout << "--- REGISTRAR TREINO ---\n";
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada.\n";
        pausar();
        return;
    }

    // listar fichas resumido
    for (auto* f : fichas) {
        std::cout << "ID: " << f->getId() << " | " << f->getNome() << "\n";
    }
    std::cout << "Digite o ID da ficha utilizada: ";
    int idFicha;
    std::cin >> idFicha;
    Ficha* f = buscarFichaPorId(idFicha);
    if (!f) {
        std::cout << "Ficha nao encontrada.\n";
        pausar();
        return;
    }

    double tempo = f->calcularTempoTotal();
    double calorias = f->calcularCaloriasTotais();

    // Data/Hora atual no formato DD/MM/YYYY HH:MM:SS
    std::time_t t = std::time(nullptr);
    std::tm* tm_info = std::localtime(&t);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);

    RegistroTreino r;
    r.dataHora = buffer;
    r.idFicha = f->getId();
    r.nomeFicha = f->getNome();
    r.tempoTotal = tempo;
    r.caloriasTotal = calorias;

    historico.adicionarRegistro(r);
    historico.salvarEmArquivo();

    std::cout << "Treino registrado: Tempo = " << tempo << " min | Calorias = " << calorias << "\n";
    pausar();
}

void Sistema::exibirHistorico() const {
    limparTela();
    historico.exibirHistorico();
    pausar();
}
