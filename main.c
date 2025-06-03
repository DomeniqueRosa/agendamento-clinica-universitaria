#include <stdio.h>
#include <stdlib.h>
#include "paciente/paciente.h"
#include "agendamento/agendamento.h"

void mostrarAreaDeAcesso() {
  printf("\n\n========== Área de Acesso ==========\n");
  printf("1. Painel de pacientes\n");
  printf("2. Painel de agendamentos\n");
  printf("0. Sair\n");
  printf("=====================================\n\n");
  printf("Escolha uma opção: ");
}

void mostrarPainelPacientes() {
  printf("\n\n======= Painel de Pacientes =======\n");
  printf("1. Cadastrar paciente\n");
  printf("2. Remover paciente\n");
  printf("3. Listar pacientes\n");
  printf("4. Buscar paciente\n");
  printf("0. Voltar à Área de Acesso\n");
  printf("===================================\n\n");
  printf("Escolha uma opção: ");
}

void mostrarPainelAgendamentos() {
  printf("\n\n======== Painel de Agendamentos ========\n");
  printf("1. Cadastrar agendamento\n");
  printf("2. Remover agendamento\n");
  printf("3. Listar agendamentos por CPF\n");
  printf("4. Listar agendamentos por sala\n");
  printf("5. Apresentar histórico de agendamentos\n");
  printf("0. Voltar à Área de Acesso\n");
  printf("========================================\n\n");
  printf("Escolha uma opção: ");
}

int main() {
  ListaPacientes* listaPacientes = criarListaPacientes();
  ListaAgendamentos* listaAgendamentos = criarListaAgendamentos();

  int areaDeAcesso = -1;
  int painelPacientes = -1;
  int painelAgendamentos = -1;

  char nome[100], CPF[12], matricula[12], curso[100], sala[100];
  
  int dia, mes, ano, hora, minuto;

  do {
    system("cls");
    mostrarAreaDeAcesso();
    scanf("%d", &areaDeAcesso);

    switch(areaDeAcesso) {
      case 1:
        painelPacientes = -1;
        system("cls");
        
        do {
          mostrarPainelPacientes();
          scanf("%d", &painelPacientes);          
          
          switch(painelPacientes) {
            case 1:
              printf("\n\n====================================\n");
              printf("         CADASTRAR PACIENTE       \n");
              printf("====================================\n");

              printf("\nDigite o nome: ");
              scanf("%s", nome);
              
              printf("Digite o CPF: ");
              scanf("%s", CPF);
              
              printf("Digite o matrícula: ");
              scanf("%s", matricula);
              
              printf("Digite o curso: ");
              scanf("%s", curso);

              cadastrarPaciente(listaPacientes, nome, CPF, matricula, curso);
            break;
            
            case 2:
              if(listaPacientes->totalPacientes == 0) {
                printf("\nRemoção não permitida: nenhum paciente cadastrado. Por favor, cadastre um paciente.\n");
              } else {
                printf("\n\n====================================\n");
                printf("         REMOVER PACIENTE       \n");
                printf("====================================\n");

                printf("\nDigite o CPF: ");
                scanf("%s", CPF);

                removerPaciente(listaPacientes, CPF);
              }
            break;
            
            case 3:
              if(listaPacientes->totalPacientes == 0) {
                printf("\nListagem não permitida: nenhum paciente cadastrado. Por favor, cadastre um paciente.\n");
              } else {
                listarPacientes(listaPacientes);
              }
            break;
            
            case 4:
              if(listaPacientes->totalPacientes == 0) {
                printf("\nBusca não permitida: nenhum paciente cadastrado. Por favor, cadastre um paciente.\n");
              } else {
                printf("\n\n====================================\n");
                printf("           BUSCAR PACIENTE       \n");
                printf("====================================\n");

                printf("\nDigite o CPF: ");
                scanf("%s", CPF);
                
                NoPaciente* resposta = buscarPaciente(listaPacientes, CPF);
                
                if(resposta == NULL) {
                  printf("\nPaciente não encontrado.\n");
                } else {
                  printf("\n\n====================================\n");
                  printf("          PACIENTE ENCONTRADO       \n");
                  printf("====================================\n\n");
                  printf("Nome: %s\n", resposta->paciente.nome);
                  printf("CPF: %s\n", resposta->paciente.CPF);
                  printf("Matrícula: %s\n", resposta->paciente.matricula);
                  printf("Curso: %s\n", resposta->paciente.curso);
                }
              }
            break;
            
            case 0:
              printf("\nRetornando à Área de Acesso...\n");
            break;
            
            default:
              printf("\nOpção inválida. Tente novamente.\n");  
          }
        } while (painelPacientes != 0);
        break;
        
        case 2: 
        painelAgendamentos = -1;
        system("cls");

        do {
          mostrarPainelAgendamentos();
          scanf("%d", &painelAgendamentos);

          switch(painelAgendamentos) {
            case 1:
              if(listaPacientes->totalPacientes == 0) {
                printf("\nAgendamento não permitido: nenhum paciente cadastrado. Por favor, cadastre um paciente.\n");
              } else {
                printf("\n\n====================================\n");
                printf("         CADASTRAR AGENDAMENTO       \n");
                printf("====================================\n");

                printf("Digite o CPF do paciente: ");
                scanf("%s", CPF);

                NoPaciente* resposta = buscarPaciente(listaPacientes, CPF);
                
                if(resposta == NULL) {
                  printf("\nPaciente não encontrado.\n");
                } else {
                  printf("Digite a sala: ");
                  scanf("%s", sala);

                  visualizarHorariosDisponiveis(listaAgendamentos, sala);
                  
                  printf("Digite o dia: ");
                  scanf("%d", &dia);
                  
                  printf("Digite o mês: ");
                  scanf("%d", &mes);
                  
                  printf("Digite o ano: ");
                  scanf("%d", &ano);
                  
                  printf("Digite o hora: ");
                  scanf("%d", &hora);
                  
                  printf("Digite o minuto: ");
                  scanf("%d", &minuto);
  
                  Data data;
                  data.dia = dia;
                  data.mes = mes;
                  data.ano = ano;

                  Hora horario;
                  horario.hora = hora;
                  horario.minuto = minuto;
                  
                  cadastrarAgendamento(listaAgendamentos, resposta->paciente, sala, data, horario);
                }
              }
            break;
            
            case 2:
              if(listaAgendamentos->totalAgendamentos == 0) {
                printf("\nRemoção não permitida: nenhum agendamento foi cadastrado até o momento. Por favor, cadastre um agendamento.\n");
              } else {
                printf("\n\n====================================\n");
                printf("         REMOVER AGENDAMENTO       \n");
                printf("====================================\n");

                printf("Digite o CPF do paciente: ");
                scanf("%s", CPF);

                NoPaciente* resposta = buscarPaciente(listaPacientes, CPF);
                
                if(resposta == NULL) {
                  printf("\nPaciente não encontrado.\n");
                } else {
                  if(!listarAgendamentoCPF(listaAgendamentos, resposta->paciente.CPF) == 0){
                    printf("\nEscolha a data do agendamento que deseja remover\n");
                    printf("Digite o dia: ");
                    scanf("%d", &dia);
                    
                    printf("Digite o mês: ");
                    scanf("%d", &mes);
                    
                    printf("Digite o ano: ");
                    scanf("%d", &ano);
  
                    removerAgendamento(listaAgendamentos, CPF, dia, mes, ano);
                  }
                }
              }
            break;
            
            case 3:
              if(listaAgendamentos->totalAgendamentos == 0) {
                printf("\nListagem não permitida: nenhum agendamento foi cadastrado até o momento. Por favor, cadastre um agendamento.\n");
              } else {
                printf("\n\n====================================\n");
                printf("         LISTAGEM POR CPF       \n");
                printf("====================================\n");

                printf("Digite o CPF do paciente: ");
                scanf("%s", CPF);

                NoPaciente* resposta = buscarPaciente(listaPacientes, CPF);
                
                if(resposta == NULL) {
                  printf("\nPaciente não cadastrado.\n");
                } else {
                  listarAgendamentoCPF(listaAgendamentos, resposta->paciente.CPF);
                }
              }
            break;
            
            case 4:
              if(listaAgendamentos->totalAgendamentos == 0) {
                printf("\nListagem não permitida: nenhum agendamento foi cadastrado até o momento. Por favor, cadastre um agendamento.\n");
              } else {
                printf("\n\n====================================\n");
                printf("         LISTAGEM POR SALA       \n");
                printf("====================================\n");

                printf("Digite a sala desejada: ");
                scanf("%s", sala);
                
                listarAgendamentoSala(listaAgendamentos, sala);            
              }
            break;

            case 5:
              if(listaAgendamentos->totalAgendamentos == 0) {
                printf("\nApresentação de histórico não permitida: nenhum agendamento foi cadastrado até o momento. Por favor, cadastre um agendamento.\n");
              } else {
                apresentarHistorico(listaAgendamentos);
              }
            break;
            
            case 0:
              printf("\nRetornando à Área de Acesso...\n");
            break;
            
            default:
            printf("\nOpção inválida. Tente novamente.\n");  
          }
        } while (painelAgendamentos != 0);
      break;

      case 0:
        printf("\nEncerrando programa...\n");

        liberarListaPacientes(listaPacientes);      
        liberarListaAgendamentos(listaAgendamentos);      
      break;

      default:
       printf("\nOpção inválida. Tente novamente.\n");
    }
  } while (areaDeAcesso != 0);
}
