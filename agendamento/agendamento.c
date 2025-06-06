#include "agendamento.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
  Autora: Carolina Milano
  Descrião: Cria e inicializa uma lista simplesmente encadeada com nó-cabeçalho para armazenar agendamentos.
            A função aloca dinamicamente a estrutura da lista e o nó-cabeçalho, que serve como ponto inicial da lista.
            Inicializa o ponteiro do nó-cabeçalho para NULL e define o total de agendamentos como zero.
*/
ListaAgendamentos* criarListaAgendamentos() {
  ListaAgendamentos* agendamentos = (ListaAgendamentos*) malloc(sizeof(ListaAgendamentos));

  agendamentos->cabecalho = (NoAgendamento*) malloc(sizeof(NoAgendamento)); 
  agendamentos->cabecalho->proximo = NULL;
  agendamentos->totalAgendamentos = 0;
 
  return agendamentos;
}

/*
  Autora: Carolina Milano
  Descrição: Libera toda a memória alocada para uma lista simplesmente encadeada com nó-cabeçalho de agendamentos.
             A função percorre a lista, liberando cada nó, incluindo o nó-cabeçalho e, por fim, libera a estrutura da lista.
             Também redefine os ponteiros para NULL e zera o total de agendamentos para evitar acesso a memória inválida.
*/
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

/*
  Autora: Carolina Milano
  Descrição: Compara se duas datas são iguais.
*/
int compararData(Data d1, Data d2) {
    return d1.dia == d2.dia && d1.mes == d2.mes && d1.ano == d2.ano;
}

/*
  Autora: Carolina Milano
  Descrição: Compara se dois horários são iguais.
*/
int compararHora(Hora h1, Hora h2) {
    return h1.hora == h2.hora && h1.minuto == h2.minuto;
}

/*
  Autora: Carolina Milano
  Descrição: Verifica se existe conflito de agendamento na lista, considerando o paciente,
             a sala, a data e o horário informados. Retorna 1 caso haja conflito (agendamento duplicado,
             conflito de horário para o mesmo paciente ou sala ocupada) e 0 caso não haja conflito.
*/
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

/*
  Autora: Carolina Milano
  Descrição: Exibe todos os horários disponíveis para uma sala específica.
*/
void visualizarHorariosDisponiveis(ListaAgendamentos* lista, const char* sala, Data data) {
  //Array pra armazenar os horários ocupados entre 08h e 18h  
  int horariosOcupados[11] = {0};

  NoAgendamento* atual = lista->cabecalho->proximo;

  while (atual != NULL) {
    if (
        strcmp(atual->agendamento.sala, sala) == 0 &&
        atual->agendamento.data.dia == data.dia &&
        atual->agendamento.data.mes == data.mes &&
        atual->agendamento.data.ano == data.ano
    ) {

      horariosOcupados[atual->agendamento.hora.hora - 8] = 1; 
    }

    atual = atual->proximo;
  }

  printf("\nHorários disponíveis na sala |%s| em %02d/%02d/%04d:\n\n", sala, data.dia, data.mes, data.ano);

  //Variável de controle para mostrar se tem, pelo menos, 1 horário disponível
  int algumDisponivel = 0;

  for (int i = 0; i <= 10; i++) {
    if (!horariosOcupados[i]) {
      printf("-> %02d:00\n", i + 8);
      algumDisponivel = 1;
    }
  }

  printf("\n");

  if (!algumDisponivel) {
    printf("Nenhum horário disponível neste dia.\n");
  }
}

/*
  Autora: Carolina Milano
  Descrição: Cadastra um novo agendamento na lista, após verificar se não há conflitos 
             com agendamentos existentes para o mesmo paciente, sala, data e horário. Se não houver 
             conflito, insere o novo agendamento no final da lista e atualiza o total de agendamentos.
*/
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



///////////////////////////////////////////////////////////////////////////////
//Autor: LeonardoLeonardo -->deleta um agendamento com base no cpf e data

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

/*
  Autora: Carolina Milano
  Descrição: Lista todos os agendamentos cadastrados para um paciente, utilizando o CPF 
             informado para filtrar e exibir os dados de cada agendamento (nome, CPF, sala, data e horário).
             Retorna 1 se encontrar agendamentos ou 0 se não encontrar.
*/
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

/* Autora: Letícia 
   Descrição: Lista todos os agendamentos de uma determinada sala, filtrados pelo nome da sala
              e exibe os dados de agendamento dos pacientes (nome, CPF, data e hora)*/


void listarAgendamentoSala(ListaAgendamentos* lista, const char* sala) {
    // Começa a percorrer a lista a partir do primeiro nó real
    NoAgendamento* atual = lista->cabecalho->proximo;

    // Variável de controle de agendamentos encontrados
    int encontrados = 0;

    printf("\n\n============================================\n");
    printf("      AGENDAMENTOS PARA A SALA: %s\n", sala);
    printf("============================================\n");

    // Enquanto o nó atual for diferente de "NULL", imprime os dados de agendamento
    while (atual != NULL) {
        if (strcmp(atual->agendamento.sala, sala) == 0) {
            printf("Nome: %s\n", atual->agendamento.paciente.nome);
            printf("C.P.F: %s\n", atual->agendamento.paciente.CPF);
            printf("Data: %02d/%02d/%04d\n", atual->agendamento.data.dia,
                                              atual->agendamento.data.mes,
                                              atual->agendamento.data.ano);
            printf("Hora: %02d:%02d\n", atual->agendamento.hora.hora,
                                          atual->agendamento.hora.minuto);
            printf("--------------------------------------------\n");

            // Incrementa o contador de agendamentos encontrados
            encontrados++;
        }
        // Aponta para o próximo agendamento da lista
        atual = atual->proximo;
    }

    // Mensagem de aviso caso não encontre agendamentos para a sala informada
    if (encontrados == 0) {
        printf("Nenhum agendamento encontrado para a sala '%s'.\n", sala);
    }
}

/*
  Autora: Carolina Milano
  Descrição: Remove todos os agendamentos de um paciente com CPF específico. 
             A função percorre a lista de agendamentos, verifica cada nó comparando o CPF do 
             paciente. Quando encontra um agendamento com o CPF informado, remove o nó da lista 
             e libera a memória correspondente. O total de agendamentos é decrementado a cada remoção.
*/
void removerAgendamentosPorCPF(ListaAgendamentos* lista, const char* CPF) {
  //Cria um nó auxiliar apontando para o primeiro elemento da lista
  NoAgendamento* atual = lista->cabecalho->proximo;
  //Cria um outro nó auxiliar para realocação dos ponteiros
  NoAgendamento* anterior = NULL;

  //Enquanto não chegar ao final da lista
  while (atual != NULL) {
    //Se o CPF informado for igual ao CPF do agendamento encontrad0
    if (strcmp(atual->agendamento.paciente.CPF, CPF) == 0) {
      //Cria um nó auxiliar para remoção do agendamento
      NoAgendamento* paraRemover = atual;

      //Se o anterior for NULL, significa que o nó encontrado é o primeiro da lista
      if (anterior == NULL) {
        //Atualiza os ponteiros
        lista->cabecalho->proximo = atual->proximo;
        atual = lista->cabecalho->proximo;
      } else {
        //Se não, ele não é o primeiro da lista
        anterior->proximo = atual->proximo;
        atual = anterior->proximo;
      }

      //Libera a memória do agendamento encontrado
      free(paraRemover);
      
      //Decrementa o total de agendamentos
      lista->totalAgendamentos--;
    } else {
      //Se não o CPF informado não foi o mesmo do agendamento, apenas atualiza os ponteiros para observar o próximo nó
      anterior = atual;
      atual = atual->proximo;
    }
  }

  printf("Agendamentos vinculados ao CPF |%s| removidos com sucesso.\n", CPF);
}

/*
  Autora: Carolina Milano
  Descrição: Exibe o histórico completo de agendamentos cadastrados na lista, 
             mostrando os dados do paciente, sala, data e horário de cada agendamento, 
             além do total de agendamentos registrados.
*/
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
