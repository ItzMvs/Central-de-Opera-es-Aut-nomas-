/*
1- criar uma struct de operadores com os dados pedidos
2- criar uma struct de equipamento com os dados pedidos
3-criar uma fun��o que cadastra um certo numero de operadores
4- criar uma fun��o que registra uma certa quantidade de equipamentos
5- usar switch case para selecionar os status e Estado Operacional
6- criar um menu principal exibindo as fun��es dentro de um loop;
7- criar uma fun��o pra poder exibir todos os dados registrados;
8- criar uma fun��o que verifica se os setores foram escritos corretamentes;
9- analisar a necessidade de criar uma fun��o para cada pedido da aba "atualiza��o"

*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct Operadores{
    int ID_operador;
    char nome[70];
    char setor_operador[4];
    char nivel[50];
    char status[50];
    int Operacoes_feitas;

}Opr;

typedef struct Equipamento{
    int ID_maquina;
    char categoria[40];
    char setor_maquina[4];
    char Estado[20];
    Opr setor_operador;
    

}Equip;

void Classificar_maquina(Equip maquinas[], int n){
    printf("\n--- CATEGORIAS DE MAQUINAS ---\n");
    printf("\n")
}

int Verificar_setor_operador(char setor[]){
    for (int i =0; i <2; i++){
            if ((setor[i] + 1)%2 ==0 || (setor[i]+1)%2!=0 ){
                continue;
              }
            else{
                return 0;
                break;
              }
      }
   for (int i = 2; i<=4; i++){
        if ((setor[i] + 1)%2 ==0 || (setor[i]+1)%2!=0 ){
            return 0;
            break;
        }
        else{
            return 1;
        }
     }
}

void Registrar_Operador(Opr operadores[], int n){
    int ID;
    char nome[70];
    int setor;
    int nivel;
    int operacoes;
    do
    {
    for (int i=0; i<n; i++){
      printf("\nInforme o ID do operador %d(4 digitos): ", i);
      scanf("%d",&ID);
      if(ID > 1000 && ID<10000){
        operadores[i].ID_operador = ID;

            }
         else{
          printf("\nValor invalido! deve ter somente 4 digitos.\n");
         }
      }

    }while(ID>10000 || ID<1000);

    do
    {
        for (int i = 0; i<n; i++){
      printf("Informe o nome do operador %d: \n", i);
      fgets(nome, 70, stdin);

      nome[strcspn(nome, "\n")] = "\0";
      while ((getchar()) != '\n' && getcahr() != EOF);
      if( strlen(nome) < 71 || strlen(nome <5)){

         strcpy(operadores[i].nome, nome);
      }
      else{
        printf("\nNome invalido! Por favor escreva de (5-70) caracteres.\n");
      }

    }
   }while (strlen(nome)> 70 || strlen(nome)< 5);

   do
{
    for (int i = 0; i <n; i++){
         printf("\nRegistro do Setor: 2 d�gitos num�ricos e em seguida 2 caracteres.\n");
         printf("\nInforme o Setor do seu operador %d: \n");
         scanf("%d", &setor);
         if(Verificar_setor_operador(setor)== 1){
            operadores[i].setor_operador = setor;

            }
         else{
            printf("\nOps! Formato invalido...");
            }
      }

}while (Verificar_setor_operador(setor)!= 1);


for(int j = 0; j<n; j++){
    printf("\n--- TABELA DE N�VEIS OPERACIONAIS ---\n");
    printf("1. Basico\n");
    printf("2. Intermediario\n");
    printf("3. Supervisor tecnico\n");
    printf("Selecione o N�vel operacional do cadastrado atual: \n");
    scanf("%d",n�vel);
    switch(nivel){
    case 1:
        strcpy(operadores[i].nivel, "Basico");
        break;
    case 2:
        strcpy(operadores[i].nivel, "Intermediario");
        break;
    case 3:
        strcpy(operadores[i].nivel, "Supervisor tecnico");
        break;
    default:
        printf("\nEssa op��o n�o existe! erro...");
        break;
}

for (int h =0; h <n; h++){
    printf("\nQuantas opera��es o operador %d ja fez?: \n", i);
    scanf("%d", &operacoes);
}


    }


}

void Registrar_Maquinas(Equip maquinas[], int n){
    int ID_maquina;
    do
    {
        for (int i= 0; i< n; i++){
            printf("Registre o ID da maquina %d: ", i);
            scanf("%d", &ID_maquina);
            if (Verificar_setor_operador(ID_maquina)== 1){
                maquinas[i].ID_maquina = ID_maquina;

            }
            else{
                printf("\nFormato invalido, por favor mande 2 digitos e 2 caracteres!\n");

            }
    } while (Verificar_setor_operador(ID_maquina)!= 1);







    }


}

void Consultar_registro(Equip maquinas[], Opr operadores[], int n){

}

void Relatorios_Operacionais(Equip maquinas[], Opr operadores[])



int main()
{
    Opr operadores[40];
    Equip maquinas[40];
    int opt;

    do
    {
        printf("\n--------------------------------------------------------------\n");
        printf("\n---------------- SISTEMA DE CADASTRO INDUSTRIAL --------------\n");
        printf("\n--------------------------------------------------------------\n");
        printf("\n");
        printf("1.Cadastrar Operadores\n");
        printf("2.Cadastrar Equipamentos\n");
        printf("3.Atualiza��o de parametros\n");
        printf("4.Consulta de registros\n");
        printf("5.Relatorios operacionais\n");
        printf("6.Sair do Sistema\n");
        printf("\n--------------------------------------------------------------\n");
        printf("Selecione uma opcao: \n");
        scanf("%d", &opt);
        switch(opt){
        case 1:
            int n1;
            printf("\nQuantos Operadores voce deseja cadastrar?(1-40): \n");
            scanf("%d", &num);
            //chamar a fun��o de cadastro aqui.
            break;
        case 2:
            int n2;
            printf("\nQuantos equipamentos voce deseja registrar?(1-40): \n");
            scanf("%d", &n2);
            //chamar a fun��o de registrar maquinas aqui.
            break;
        case 3:
            printf("Encerrando sistema!Obrigado...");
            break;
        default:
            printf("Erro! Numero invalido...");
            break;
        }

    }while(opt >3 || opt<1);
    return 0;
}
