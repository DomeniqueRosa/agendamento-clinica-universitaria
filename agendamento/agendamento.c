#include "agendamento.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ListaAgendamentos* criarListaAgendamentos() {
  ListaAgendamentos* agendamentos = (ListaAgendamentos*) malloc(sizeof(ListaAgendamentos));

  agendamentos->cabecalho = (NoAgendamento*) malloc(sizeof(NoAgendamento)); 
  agendamentos->cabecalho->proximo = NULL;
  agendamentos->totalAgendamentos = 0;
 
  return agendamentos;
}

void liberarListaAgendamentos(ListaAgendamentos* lista) {
  NoAgendamento* atual = lista->cabecalho;

  while (atual != NULL) {
    NoAgendamento* temp = atual;
    atual = atual->proximo;
    free(temp);
  }

  lista->cabecalho = NULL;
  lista->totalAgendamentos = 0;

  free(lista);
}

int compararData(Data d1, Data d2) {
    return d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano;
}

int compararHora(Hora h1, Hora h2) {
    return h1.hora == h2.hora && h1.minuto == h2.minuto;
}

int existeConflitoAgendamento(ListaAgendamentos* listaAgendamentos, Paciente paciente, const char* sala, Data data, Hora hora) {
  NoAgendamento* atual = listaAgendamentos->cabecalho->proximo;
  
  while(atual != NULL) {
    int mesmoPaciente = strcmp(atual->agendamento.paciente.CPF, paciente.CPF) == 0;
    int mesmaSala = strcmp(atual->agendamento.sala, sala) == 0;
    int mesmaData = compararData(atual->agendamento.data, data);
    int mesmaHora = compararHora(atual->agendamento.hora, hora);

    if(mesmoPaciente && mesmaSala && mesmaData && mesmaHora) {
      printf("\nAgendamento duplicado: O paciente já possui um compromisso marcado nesta sala, na mesma data e horário.\n");

      return 1;
    }

    if(mesmoPaciente && mesmaData && mesmaHora) {
      printf("\nConflito de horário: O paciente já tem um agendamento em outro local para esta data e horário.\n");

      return 1;
    }

    if(mesmaSala && mesmaData && mesmaHora) {
      printf("\nSala ocupada: Já existe um agendamento para esta sala na mesma data e horário.\n");

      return 1;
    }

    atual = atual->proximo;
  }

  return 0;
}

//Carolina
void cadastrarAgendamento(ListaAgendamentos* listaAgendamentos, Paciente paciente, const char* sala, Data data, Hora hora) {
  if(existeConflitoAgendamento(listaAgendamentos, paciente, sala, data, hora)) {
    return;
  }

  NoAgendamento* novoAgendamento = (NoAgendamento*) malloc(sizeof(NoAgendamento));

  novoAgendamento->agendamento.paciente = paciente;
  strcpy(novoAgendamento->agendamento.sala, sala);
  novoAgendamento->agendamento.data = data;
  novoAgendamento->agendamento.hora = hora;
  novoAgendamento->proximo = NULL;

  if(listaAgendamentos->cabecalho->proximo == NULL) {
    listaAgendamentos->cabecalho->proximo = novoAgendamento;
  } else {
    NoAgendamento* atual = listaAgendamentos->cabecalho->proximo;
    
    while(atual->proximo != NULL) {
      atual = atual->proximo;
    }

    atual->proximo = novoAgendamento;
  }

  listaAgendamentos->totalAgendamentos++;

  printf("\nAgendamento cadastrado com sucesso.\n");
}

//Leonardo
int removerAgendamento(ListaAgendamentos* lista, const char* CPF, Data data) {

}

//Carolina
void listarAgendamentoCPF(ListaAgendamentos* lista, const char* CPF) {
  NoAgendamento* atual = lista->cabecalho->proximo;

  int agendamentosEncontrados = 0;
  printf("\n\n==========================================\n");
  printf("   AGENDAMENTO CADASTRADO PARA O CPF |%s|       \n", CPF);
  printf("==========================================\n\n");
  
  while(atual != NULL) {
    if(strcmp(atual->agendamento.paciente.CPF, CPF) == 0) {
      printf("Nome: %s\n", atual->agendamento.paciente.nome);
      printf("C.P.F: %s\n", atual->agendamento.paciente.CPF);
      printf("Sala: %s\n", atual->agendamento.sala);
      printf("Data: %02d/%02d/%04d às %02d:%02d\n", 
                                          atual->agendamento.data.dia,
                                          atual->agendamento.data.mes,
                                          atual->agendamento.data.ano,
                                          atual->agendamento.hora.hora,
                                          atual->agendamento.hora.minuto);
      
      printf("\n==========================================\n\n");

      agendamentosEncontrados++;
    }
    
    atual = atual->proximo;
  }

  if(agendamentosEncontrados == 0) {
    printf("Nenhum agendamento encontrado para o CPF |%s|.", CPF);
  }
}

//Leonardo
void listarAgendamentoSala(ListaAgendamentos* lista, const char* sala) {

}

//Em aberto
void apresentarHistorico(ListaAgendamentos* lista) {

}