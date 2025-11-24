SGTP – Sistema de Gestão de Treinos Pessoais

Sistema desenvolvido em C++ para auxiliar no gerenciamento de rotinas de treino pessoais, substituindo fichas de papel e facilitando o acompanhamento dos exercícios.
Este projeto foi produzido como Trabalho Prático da disciplina de Programação.

## Objetivo do Sistema

O SGTP permite ao usuário:

- Cadastrar exercícios
- Criar fichas de treino personalizadas
- Registrar o histórico de treinos realizados
- Editar e consultar informações de forma simples

Persistir dados localmente através de arquivos .txt

## Estrutura do Projeto

```
SGTP/
│
├── README.md                    # Documentação do projeto
├── Makefile                     # Arquivo para compilação automatizada
│
├── include/                     # Headers (.h)
│   ├── Exercicio.h
│   ├── Cardio.h
│   ├── Forca.h
│   ├── Ficha.h
│   ├── Historico.h
│   ├── Sistema.h
│   └── Utils.h
│
├── src/                         # Implementações (.cpp)
│   ├── Exercicio.cpp
│   ├── Cardio.cpp
│   ├── Forca.cpp
│   ├── Ficha.cpp
│   ├── Historico.cpp
│   ├── Sistema.cpp
│   └── main.cpp    
│            
│
├── data/                        # Persistência dos dados
│   ├── exercicios.txt           # Lista de exercícios cadastrados
│   ├── fichas.txt               # Lista de fichas de treino
│   ├── historico.txt            # Registro do histórico de treinos
│   
│
├── build/                       # Arquivos de compilação
│   ├── utils.o
│   ├── menu.o
│   ├── exercicio.o
│   ├── ficha.o
│   ├── historico.o
│   ├── forca.o
│   └── main.o
│
├── bin/                         # Onde o executável final é gerado  
│   └── sgtp.exe                 # Executável no Windows
```

## Arquivos de Dados

| Arquivo         | Função                               |
|-----------------|----------------------------------------|
| exercicios.txt  | Armazena exercícios cadastrados        |
| fichas.txt      | Salva fichas de treino dos usuários    |
| historico.txt   | Registra treinos realizados            |

Se estiverem vazios, o sistema preencherá conforme o uso.

## Compilação

**Compilar:**
```
make
```

**Executar:**
```
make run
```

**Limpar:**
```
make clean
```

## Principais Módulos

- **main.cpp** – Fluxo principal e menus
- **utils.h/** – Funções auxiliares (limpar tela, validações etc.)
- **forca.cpp** – Módulo de jogo

Outros arquivos referentes à manipulação de fichas, exercícios e histórico

## Funcionalidades

✔ Cadastro e edição de exercícios

✔ Criação e gerenciamento de fichas

✔ Persistência completa em arquivos

✔ Histórico de treinos

✔ Separação modular (headers + src)

✔ Makefile funcional

✔ Interface simples em terminal

## Pontos Positivos

- Código organizado em módulos, facilitando manutenção.
- Uso de persistência em arquivos, permitindo salvar dados entre execuções.
- Makefile bem estruturado, automatizando a compilação em Windows/Linux.
- Boas práticas, como separação de headers e diretórios corretos.
- Interface clara, fácil de navegar via menus.
- Sistema expansível, permitindo novas funcionalidades futuramente.
- Baixa dependência externa: funciona apenas com C++ padrão.

## Pontos Negativos / Limitações

- Arquivos .txt não possuem validação robusta, podendo ser corrompidos manualmente.
- Não possui interface gráfica, o que pode limitar a usabilidade para usuários leigos.
- Dados não são criptografados, portanto não devem armazenar informações sensíveis.
- Escalabilidade limitada, já que arquivos texto não são tão eficientes quanto bancos de dados.
- Não há sistema de login completo, dependendo da implementação final.
- Tratamento de erros ainda simples, podendo ser reforçado.

