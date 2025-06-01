#ifndef AGENDAMENTO_H
#define AGENDAMENTO_H

#define maxSala 100

#include "../paciente/paciente.h"

//Estrutura de data
typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

//Estrutura de hora
typedef struct {
  int hora;
  int minuto;
} Hora;

//Estrutura que representa os dados de um agendamento
typedef struct {
  Paciente paciente;
  char sala[maxSala];
  Data data;
  Hora hora;
} Agendamento;

//Estrutura do nó de agendamentos
typedef struct NoAgendamento {
  Agendamento agendamento;
  struct NoAgendamento* proximo;
} NoAgendamento;

//Lista de agendamentos com cabeçalho
typedef struct {
  NoAgendamento* cabecalho;
  int totalAgendamentos;
} ListaAgendamentos;

//Funções de criação e liberação da lista
ListaAgendamentos* criarListaAgendamentos();
void liberarListaAgendamentos(ListaAgendamentos* lista);

//Funções de cadastro e remoção de agendamentos
void cadastrarAgendamento(ListaAgendamentos* ListaAgendamentos, Paciente paciente, const char* sala, Data data, Hora hora);
int removerAgendamento(ListaAgendamentos* lista, const char* CPF, int dia, int mes, int ano);
//Funções de listagem e busca de agendamentos
void listarAgendamentoCPF(ListaAgendamentos* lista, const char* CPF);
void listarAgendamentoSala(ListaAgendamentos* lista, const char* sala);

//Histórico com todos os agendamentos realizados 
void apresentarHistorico(ListaAgendamentos* lista);

#endif
