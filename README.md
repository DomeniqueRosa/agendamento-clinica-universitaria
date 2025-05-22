# Sistema de Gerenciamento de Agendamentos

Projeto desenvolvido para a disciplina de Estrutura de Dados I, que consiste em um sistema para gerenciamento de agendamento de consultas em uma clínica universitária.

## Sumário

- [Descrição do Projeto](#descrição-do-projeto)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Estrutura de Dados](#estrutura-de-dados)
- [Funcionalidades e Autoria](#funcionalidades-e-autoria)
- [Compilação e Execução](#compilação-e-execução)
- [Colaboradores](#-colaboradores)


## 📋 Descrição do Projeto

Este projeto foi desenvolvido para a disciplina **Estrutura de Dados I** e consiste em um **Sistema de Agendamento de Consultas para uma Clínica Universitária**.

O objetivo é criar uma aplicação em linguagem C que utilize listas lineares para armazenar, manipular e exibir dados de pacientes e agendamentos.

O sistema permite o cadastro de pacientes, o agendamento de consultas, a consulta e listagem de agendamentos por CPF ou sala, além do gerenciamento de histórico e remoção de agendamentos.

O contexto do projeto é uma clínica universitária que organiza os atendimentos mediante agendamento prévio, disponibilizando horários em salas específicas.


## 🗂️ Estrutura do projeto

O projeto está organizado em pastas separadas para facilitar a manutenção e organização do código. A estrutura possui:

<div align="center">

```
src/              
├── paciente/   
  │   ├── paciente.h
  │   └── paciente.c
├── agendamento/
     │   ├── agendamento.h
     │   └── agendamento.c
└── main.c      
```

</div>

- **`paciente/`**
  - **`paciente.h`**: cabeçalho com as definições das funções e estrutura da lista dos pacientes.
  - **`paciente.c`**: implementação das funções definidas em `paciente.h` para manipulação de pacientes.

- **`agendamento/`**
  - **`agendamento.h`**: cabeçalho com as definições das funções e estrutura de lista de agendamentos.
  - **`agendamento.c`**: implementação das funções definidas em `agendamento.h` para manipulação de agendamentos.

- **`main.c`**: arquivo principal que contém os menus de interação e gerencia o fluxo do programa.

## 🏗️ Estruturas de Dados

O projeto utiliza duas estruturas de dados principais para a organização das informações:

- **Lista simplesmente encadeada** para gerenciar os pacientes. Cada nó armazena os dados de um paciente e um ponteiro para o próximo elemento.

  ```
  typedef struct {
    char nome[maxNome];
    char CPF[maxCPF];
    char matricula[maxMatricula];
    char curso[maxCurso];
  } Paciente;
  ```
  ```
  typedef struct NoPaciente {
    Paciente paciente;
    struct NoPaciente* proximoNo;
  } NoPaciente;
  ```

  ```
  typedef struct {
    NoPaciente* primeiro;
    int totalPacientes;
  } ListaPacientes;
  ```

- **Lista com nó-cabeçalho** para gerenciar os agendamentos. O nó-cabeçalho facilita operações como inserção e remoção, armazenando um ponteiro para o primeiro elemento da lista.

  ```
  typedef struct {
    Paciente paciente;
    char sala[maxSala];
    Data data;
    Hora hora;
  } Agendamento;
  ```
  ```
  typedef struct NoAgendamento {
    Agendamento agendamento;
    struct NoAgendamento* proximo;
  } NoAgendamento;
  ```

  ```
  typedef struct {
    NoAgendamento* cabecalho;
    int totalAgendamentos;
  } ListaAgendamentos;
  ```

## 🧠 Funcionalidades e Autoria

Abaixo, listamos as funcionalidades implementadas, separadas por arquivo e com a autoria de cada uma.

### 👥 paciente.c

- **`criarListaPacientes`**  
  Cria uma nova lista simplesmente encadeada para pacientes.  
  *Desenvolvido coletivamente*
- **`liberarListaPacientes`**  
  Libera toda a memória da lista de pacientes.  
  *Desenvolvido coletivamente*
- **`cadastrarPaciente`**  
  Cadastra um paciente no final da lista de pacientes.  
  *Desenvolvido por: ...*
- **`removerPaciente`**  
  Remove o paciente da lista correspondente ao CPF informado.  
  *Desenvolvido por: Carolina Milano*
- **`listarPacientes`**  
  Lista todos os pacientes cadastrados.  
  *Desenvolvido por: Carolina Milano*
- **`buscarPaciente`**  
  Busca o paciente correspondente ao CPF informado.  
  *Desenvolvido por: Carolina Milano*

### ⏰ agendamento.c

- **`criarListaAgendamentos`**  
  Cria uma nova lista com nó-cabeçalho para agendamentos.  
  *Desenvolvido coletivamente*
- **`liberarListaAgendamentos`**  
  Libera toda a memória da lista de agendamentos.  
  *Desenvolvido coletivamente*
- **`cadastrarAgendamento`**  
  Cadastra um agendamento no final da lista de agendamentos.  
  *Desenvolvido por: Carolina Milano*
- **`removerAgendamento`**  
  Remove um agendamento da lista correspondente ao CPF informado.  
  *Desenvolvido por: ...*
- **`listarAgendamentoCPF`**  
  Lista todos os agendamentos correspondentes ao CPF informado.  
  *Desenvolvido por: Carolina Milano*
- **`listarAgendamentoSala`**  
  Lista todos os agendamentos correspondentes à sala informada.  
  *Desenvolvido por: ...*
- **`apresentarHistorico`**  
  Apresenta o histórico com todos os agendamentos cadastrados no sistema.  
  *Desenvolvido por: ...*

## 🛠️ Compilação e Execução

1. Clone o repositório:  
```bash
git clone https://github.com/DomeniqueRosa/agendamento-clinica-universitaria.git
```

2. Compile o projeto:

```bash
gcc main.c agendamento/agendamento.c paciente/paciente.c -o sistemaAgendamento
```

3. Execute o projeto:

```bash
./sistemaAgendamento
```

## 👩‍💻 Colaboradores

Este projeto foi desenvolvido em grupo como parte das atividades da disciplina de **Estrutura de Dados I** da **Universidade Federal do Paraná - UFPR**.   

**Membros:**  
- [Alires](...) 
- [Carolina Milano](https://github.com/CarolGMilano) 
- [Leon](...) 
- [Leonardo](...) 
- [Leticia](...) 
