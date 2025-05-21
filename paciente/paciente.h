#ifndef PACIENTE_H
#define PACIENTE_H

#define maxNome 100
#define maxCPF 12
#define maxMatricula 12
#define maxCurso 100

//Estrutura que representa os dados de um paciente
typedef struct {
  char nome[maxNome];
  char CPF[maxCPF];
  char matricula[maxMatricula];
  char curso[maxCurso];
} Paciente;

//Nó da lista encadeada de pacientes
typedef struct NoPaciente {
  Paciente paciente;
  struct NoPaciente* proximoNo;
} NoPaciente;

//Lista encadeada simples de pacientes
typedef struct {
  NoPaciente* primeiro;
  int totalPacientes;
} ListaPacientes;

//Funções de criação e liberação da lista
ListaPacientes* criarListaPacientes();
void liberarListaPacientes(ListaPacientes* lista);

//Funções de cadastro e remoção de pacientes da lista
void cadastrarPaciente(ListaPacientes* lista, const char* nome, const char* CPF, const char* matricula, const char* curso);
int removerPaciente(ListaPacientes* lista, const char* CPF);

//Funções de listagem e busca de pacientes
void listarPacientes(ListaPacientes* lista);
NoPaciente* buscarPaciente(ListaPacientes* lista, const char* CPF);

#endif
