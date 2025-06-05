#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
  Autora: Carolina Milano
  Descrição: Cria e inicializa uma nova lista simplesmente encadeada de pacientes.
             A função aloca dinamicamente a estrutura da lista, define o ponteiro 
             para o primeiro nó como NULL e inicializa o total de pacientes com 0.
             Retorna o ponteiro para a lista criada.
*/
ListaPacientes* criarListaPacientes() {
  ListaPacientes* pacientes = (ListaPacientes*) malloc(sizeof(ListaPacientes));

  pacientes->primeiro = NULL;
  pacientes->totalPacientes = 0;

  return pacientes;
}

/*
  Autora: Carolina Milano
  Descrição: Verifica se a lista de pacientes está inicializada e se não está vazia.
             Retorna 1 se a lista for válida ou não estiver vazia.
             Retorna 0 se a lista for NULL ou estiver vazia,
             exibindo uma mensagem de aviso para cada caso.
*/
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

/*
  Autora: Carolina Milano
  Descrição: Libera a memória alocada para uma lista simplesmente encadeada de pacientes.
             A função percorre a lista, liberando cada nó individualmente para evitar vazamentos de memória.
             Ao final, define o ponteiro para o primeiro nó como NULL, zera o total de pacientes 
             e libera a memória alocada para a estrutura da lista.
*/             
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
//dificuldade encontrada ter que entender a estrutura e que ao cadastrar tem que incrementar mais um nao apenas adc
void cadastrarPaciente(ListaPacientes* lista, const char* nome, const char* CPF, const char* matricula, const char* curso) {
  //Se a lista não estiver vazia
  if(lista->totalPacientes >= 1) {
    //Faz a busca para evitar duplicidade de cadastro
    if(buscarPaciente(lista, CPF)) {
      printf("\nErro: O paciente com o CPF |%s| já foi cadastrado.\n", CPF);

      return;
    }
  }

    // Aloca memória para um novo nó da lista encadeada e zera os campos
    NoPaciente* novoPaciente = (NoPaciente*)calloc(1, sizeof(NoPaciente));

    // Copia os dados para o novo paciente
    strcpy(novoPaciente->paciente.nome, nome);
    strcpy(novoPaciente->paciente.CPF, CPF);
    strcpy(novoPaciente->paciente.matricula, matricula);
    strcpy(novoPaciente->paciente.curso, curso);


    // Inserir o novo nó na lista
    if (lista->primeiro == NULL) {
        // Lista vazia, novo paciente será o primeiro
        lista->primeiro = novoPaciente;
    } else {
        // Percorre até o final da lista para inserir no fim
        NoPaciente* atual = lista->primeiro;
        while (atual->proximoNo != NULL) {
            atual = atual->proximoNo;
        }
        atual->proximoNo = novoPaciente;
    }

    printf("\nPaciente cadastrado com sucesso!\n");
    lista->totalPacientes +=1;
}

/*
  Autora: Carolina Milano
  Descrição: Remove um paciente da lista com base no CPF informado. Percorre a lista para 
             localizar o paciente, remove o nó correspondente e ajusta os ponteiros. Retorna 1 
             se a remoção foi bem-sucedida ou 0 se o paciente não foi encontrado ou se a lista estiver vazia.
*/
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

/*
  Autora: Carolina Milano
  Descrição: Lista todos os pacientes cadastrados na lista, exibindo nome, CPF, matrícula e curso.
             Caso a lista esteja vazia, a função não realiza nenhuma ação.
*/
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

/*
  Autora: Carolina Milano
  Descrição: Busca e retorna o nó do paciente na lista que possua o CPF informado.
             Retorna NULL caso o paciente não seja encontrado ou se a lista estiver vazia.
*/
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
