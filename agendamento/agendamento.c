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
  /*
    Verifica se o agendamento que se deseja cadastrar:
      - Já foi cadastrado;
      - Se o paciente já possui um agendamento para a mesma data e horário;
      - Se a sala já possui um agendamento para a mesma data e horário.
  */
  if(existeConflitoAgendamento(listaAgendamentos, paciente, sala, data, hora)) {
    return;
  }

  //Se não houver conflito, aloca-se a memória para o novo agendamento
  NoAgendamento* novoAgendamento = (NoAgendamento*) malloc(sizeof(NoAgendamento));

  //Adiciona os dados aos campos correspondentes
  novoAgendamento->agendamento.paciente = paciente;
  strcpy(novoAgendamento->agendamento.sala, sala);
  novoAgendamento->agendamento.data = data;
  novoAgendamento->agendamento.hora = hora;
  novoAgendamento->proximo = NULL;

  //Se a lista estiver vazia, o novo nó será inserido na primeira posição
  if(listaAgendamentos->cabecalho->proximo == NULL) {
    listaAgendamentos->cabecalho->proximo = novoAgendamento;
  } else {
    //Se não, percorre a lista toda até o final
    NoAgendamento* atual = listaAgendamentos->cabecalho->proximo;
    
    while(atual->proximo != NULL) {
      atual = atual->proximo;
    }

    //Adiciona o novo agendamento ao final da lista
    atual->proximo = novoAgendamento;
  }

  listaAgendamentos->totalAgendamentos++;

  printf("\nAgendamento cadastrado com sucesso.\n");
}


//Aparentemente as duas variações são equivalentes:
//void imprimirString(const char *str);
//void imprimirString(const char str[]);
//isso daqui l->agendamento.paciente.CPF   se chama campo comum
///////////////////////////////////////////////////////////////////////////////Minha versão(está correta! mas ficou feia)
//Leonardo

int removerAgendamento(ListaAgendamentos* lista, const char* CPF, int dia, int mes, int ano) {
  if(dia > 31 || dia < 1 || mes < 1 || mes > 12 || ano < 2023){
    return 0;  //data inválida
  }

  NoAgendamento *l = lista->cabecalho;
  NoAgendamento *ant = NULL;
  int igual;
  
  if(l == NULL){
    return 0;  //lista está vazia
  }

  int a = strcmp(l->agendamento.paciente.CPF, CPF);  
  if(a == 0){
    igual = 1;
  }else{
    igual = 0;
  }

  while(l != NULL && !(igual && l->agendamento.data.dia == dia && l->agendamento.data.mes == mes && l->agendamento.data.ano == ano)){
    ant = l;
    l = l->proximo;

    if(l != NULL){   //se l ainda não for nulo
      a = strcmp(l->agendamento.paciente.CPF, CPF);  
      if(a == 0){
        igual = 1;
      }else{
        igual = 0;
      }
    }

  }

  if(l == NULL){
    return 0;   //Não achou
  }

  if(ant == NULL){
    lista->cabecalho = l->proximo;
  }else{
    ant->proximo = l->proximo;
  }
  
  free(l);
  lista->totalAgendamentos--;
  return 1;  //achou e removeu
}
  
//////////////////////////////////////////////////////////versão GPT (baseada na minha, só que fica mais fácil de entender)
/*int removerAgendamento(ListaAgendamentos* lista, const char* CPF, int dia, int mes, int ano) {
    if (dia > 31 || dia < 1 || mes < 1 || mes > 12 || ano < 2023) {
        return 0;  // Data inválida
    }

    NoAgendamento *l = lista->cabecalho;
    NoAgendamento *ant = NULL;

    while (l != NULL) {
        if (
            strcmp(l->agendamento.paciente.CPF, CPF) == 0 &&
            l->agendamento.data.dia == dia &&
            l->agendamento.data.mes == mes &&
            l->agendamento.data.ano == ano
        ) {
            // Encontrou o agendamento, remove
            if (ant == NULL) {
                lista->cabecalho = l->proximo;
            } else {
                ant->proximo = l->proximo;
            }
            free(l);
            lista->totalAgendamentos--;
            return 1;
        }

        ant = l;
        l = l->proximo;
    }
    return 0;  // Não encontrou
}
*/

//Carolina
int listarAgendamentoCPF(ListaAgendamentos* lista, const char* CPF) {
  //Cria um nó auxiliar para percorrer a lista desde o início
  NoAgendamento* atual = lista->cabecalho->proximo;

  //Variável de contagem de agendamentos encontrados
  int agendamentosEncontrados = 0;

  printf("\n\n==========================================\n");
  printf("   AGENDAMENTO CADASTRADO PARA O CPF |%s|       \n", CPF);
  printf("==========================================\n\n");
  
  //Enquanto o nó atual for diferente de NULL, imprima as informações do agendamento
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
    
    //Atualiza o atual para o próximo para percorrer toda a lista
    atual = atual->proximo;
  }

  //Se não forem encontrados agendamentos para o CPF informado, mostrar mensagem de aviso
  if(agendamentosEncontrados == 0) {
    printf("Nenhum agendamento encontrado para o CPF |%s|.", CPF);

    return 0;
  }

  return 1;
}

//Leonardo ou Letícia
void listarAgendamentoSala(ListaAgendamentos* lista, const char* sala) {
  NoAgendamento* p = lista->cabecalho;
  for(p; p != NULL; p = p->proximo){
    if(strcmp(sala, p->agendamento.sala) == 0){
      printf("Paciente: %s | Data: %02d/%02d/%04d | Hora: %02d:%02d | Sala: %s\n", p->agendamento.paciente.nome, p->agendamento.data.dia,  
        p->agendamento.data.mes,  p->agendamento.data.ano, p->agendamento.hora.hora, p->agendamento.hora.minuto, p->agendamento.sala);
    }
  }
}

//Carolina
void apresentarHistorico(ListaAgendamentos* lista) {
  NoAgendamento* atual = lista->cabecalho->proximo;

  printf("\n\n==========================================\n");
  printf("        HISTÓRICO DE AGENDAMENTO       \n");
  printf("==========================================\n\n");
  printf("Total de agendamentos: %d\n\n", lista->totalAgendamentos);

  //Percorre até o final da lista até imprimir todos os elementos
  while (atual != NULL) {
    printf("\nPaciente: %s", atual->agendamento.paciente.nome);
    printf("\nCPF: %s", atual->agendamento.paciente.CPF);
    printf("\nMatrícula: %s", atual->agendamento.paciente.matricula);
    printf("\nCurso: %s", atual->agendamento.paciente.curso);
    printf("\nSala: %s", atual->agendamento.sala);
    printf("\nData: %02d/%02d/%04d", atual->agendamento.data.dia, atual->agendamento.data.mes, atual->agendamento.data.ano);
    printf("\nHora: %02d:%02d\n", atual->agendamento.hora.hora, atual->agendamento.hora.minuto);
    printf("\n==========================================\n\n");

    atual = atual->proximo;
  }
}