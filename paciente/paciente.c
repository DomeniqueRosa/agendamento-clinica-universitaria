#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ListaPacientes* criarListaPacientes() {
  ListaPacientes* pacientes = (ListaPacientes*) malloc(sizeof(ListaPacientes));

  pacientes->primeiro = NULL;
  pacientes->totalPacientes = 0;

  return pacientes;
}

int verificarListaPaciente(ListaPacientes* lista) {
  if(lista == NULL) {
    printf("\nErro: A lista de pacientes não foi inicializada.\n");
    
    return 0;
  } 
  
  if (lista->totalPacientes == 0) {
    printf("\nA lista de pacientes está vazia.\n");

    return 0;
  }

  return 1;
}

void liberarListaPacientes(ListaPacientes* lista) {
  if(!verificarListaPaciente(lista)) return;

  NoPaciente* atual = lista->primeiro;  
  NoPaciente* proximo;
  
  while(atual != NULL) {
    proximo = atual->proximoNo;
    
    free(atual);

    atual = proximo;
  }

  lista->primeiro = NULL;
  lista->totalPacientes = 0;

  free(lista);
}

//Domenique
void cadastrarPaciente(ListaPacientes* lista, const char* nome, const char* CPF, const char* matricula, const char* curso) {

}

int removerPaciente(ListaPacientes* lista, const char* CPF) {
  if (!verificarListaPaciente(lista)) return 0;

  NoPaciente* resposta = buscarPaciente(lista, CPF);

  if(resposta == NULL) {
    printf("\nPaciente não encontrado.\n");
    
    return 0;
  } 
  
  if(lista->primeiro == resposta) {
    lista->primeiro = resposta->proximoNo;
    free(resposta);    
    lista->totalPacientes--;

    printf("\nPaciente removido com sucesso.\n");
    
    return 1;
  }
  
  NoPaciente* atual = lista->primeiro;

  while(atual->proximoNo != resposta) {    
    atual = atual->proximoNo;
  }

  atual->proximoNo = resposta->proximoNo;
  free(resposta);
  lista->totalPacientes--;

  printf("\nPaciente removido com sucesso.\n");

  return 1;
}

void listarPacientes(ListaPacientes* lista) {
  if(!verificarListaPaciente(lista)) return;

  printf("\n\n====================================\n");
  printf("         PACIENTES CADASTRADOS       \n");
  printf("====================================\n\n");
  
  NoPaciente* atual = lista->primeiro;
  
  while(atual != NULL) {
    printf("Nome: %s\n", atual->paciente.nome);
    printf("C.P.F: %s\n", atual->paciente.CPF);
    printf("Matrícula: %s\n", atual->paciente.matricula);
    printf("Curso: %s\n", atual->paciente.curso);
    
    printf("\n====================================\n\n");
    
    atual = atual->proximoNo;
  }
}

NoPaciente* buscarPaciente(ListaPacientes* lista, const char* CPF) {
  if(!verificarListaPaciente(lista)) return NULL;

  NoPaciente* atual = lista->primeiro;

  while(atual != NULL) {
    if(strcmp(atual->paciente.CPF, CPF) == 0) {
      return atual;
    }  

    atual = atual->proximoNo;
  }

  return NULL;
}
