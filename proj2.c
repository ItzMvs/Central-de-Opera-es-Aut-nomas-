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
10- criar uma quantidade de setores e tipos de maquinas pra apresentar num menu com switch case


*/
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct Operadores{
    int ID_operador; // 4 digitos , usar função recursiva
    char nome[70];
    char setor_operador[4]; // 2 letras e dois dígitos, nessa ordem (concatene strings)
    char nivel[50];
    char status[50];
    int Operacoes_feitas;

}Opr;

typedef struct Equipamento{
    int ID_maquina; // 1 letra e 2 dígitos (concatene strings)
    char categoria[40];
    char setor_maquina[4];
    char Estado[20];
    int id_operador_responsavel;
    char Nivel_prioridade;


}Equip;

void Registrar_Operador(Opr operadores[], int n){

    int ID;
    char nome[70];
    int setor;
    int nivel;
    int status;
    int operacoes;
    int x;

    // REGISTRAR ID DO OPERADOR:

    do
    {
    for (int i=0; i<n; i++){
      printf("\nInforme o ID do operador %d(4 digitos): ", i);
      scanf("%d",&ID);
      x = Check_ID_Op(ID);
      if (x == 4)
      {
          operadores[i].ID_operador = ID;
      }
      else
      {
          printf("\nFormato incorreto! tente novamente...");
      }

    }
    }while(Check_ID_Op(ID)!= 4);

    // REGISTRAR NOME:

    do
    {
        for (int i = 0; i<n; i++){
      printf("Informe o nome do operador %d: \n", i);
      fgets(nome, 70, stdin);

      nome[strcspn(nome, "\n")] = "\0";
      while ((getchar()) != '\n' && getchar() != EOF);
      if( strlen(nome) < 71 || strlen(nome)<1){

         strcpy(operadores[i].nome, nome);
      }
      else{
        printf("\nNome invalido! Por favor escreva de (5-70) caracteres.\n");
      }

    }
   }while (strlen(nome)> 70 || strlen(nome)< 1);


   //REGISTRAR O SETOR DO OPERADOR:

   do
{
    for (int i = 0; i <n; i++){
            printf("\n--- LISTA DE SETORES ---\n");
            printf("---------------------------");
            printf("\n1.Setor VX28-(Coleta)\n");
            printf("2.Setor VX29-(Montagem)\n");
            printf("3.Setor VX30-(Conserto)\n");
            printf("4.Setor VX31-(Entrega)\n");
            printf("5.Setor VX32-(Revisao geral)\n");
            printf("6.Encerrar selecao\n");
            printf("----------------------------");
            printf("\n");
            printf("Seleciona um dos setores acima (1-5): \n");
            scanf("%d", &setor);
            switch(setor){
            case 1:
                strcpy(operadores[i].setor_operador, "VX28");
                break;
            case 2:
                strcpy(operadores[i].setor_operador, "VX29");
                break;
            case 3:
                strcpy(operadores[i].setor_operador, "VX30");
                break;
            case 4:
                strcpy(operadores[i].setor_operador, "VX31");
                break;
            case 5:
                strcpy(operadores[i].setor_operador, "VX32");
                break;
            case 6:
                printf("Encerrando seleção...\n");
                break;
            default:
                printf("Erro!! Opcao invalida\n");
                break;


            }
    }

// REGISTRAR NIVEL DO OPERADOR:


}while(setor >6 || setor <1);

do
{
    for(int j = 0; j<n; j++){
    printf("\n--- TABELA DE NiVEIS OPERACIONAIS ---\n");
    printf("1. Basico\n");
    printf("2. Intermediario\n");
    printf("3. Supervisor tecnico\n");
    printf("4. Encerrar selecao\n");
    printf("Selecione o Nivel operacional do cadastrado atual: \n");
    scanf("%d",nivel);
    switch(nivel){
    case 1:
        strcpy(operadores[j].nivel, "Basico");
        break;
    case 2:
        strcpy(operadores[j].nivel, "Intermediario");
        break;
    case 3:
        strcpy(operadores[j].nivel, "Supervisor tecnico");
        break;
    case 4:
        printf("Encerrando selecao...\n");
        break;
    default:
        printf("\nEssa opcao nao existe! erro...");
        break;
     }
   }
}while (nivel> 4 || nivel <1);


//REGISTRAR O STATUS ATUAL DO OPERADOR:

do
{
    for(int i= 0; i<n; i++)
    {
        printf("\n--- STATUS ATUAL DISPONÍVEL ---\n");
    printf("-----------------------------------");
    printf("1.Ativo (disponivel)\n");
    printf("2.Ocupado\n");
    printf("3.Inativo(fora de operacao)\n");
    printf("4.Bloqueado(temporariamente)\n");
    printf("5.Sair da selecao\n");
    printf("------------------------------------");
    printf("\nSelecione seu status atual: ");
    scanf("%d", &nivel);
    switch(nivel){
      case 1:
          strcpy(operadores[i].status, "Ativo(disponivel)");
          break;
      case 2:
        strcpy(operadores[i].status, "Ocupado");
        break;
      case 3:
        strcpy(operadores[i].status, "Inativo(fora de operacao)");
        break;
      case 4:
        strcpy(operadores[i].status, "Bloqueado(temporariamente)");
        break;
      case 5:
        printf("\nSaindo da selecao...\n");
        break;
      default:
        printf("\nOpcao invalida! tente novamente...\n");
    }


    }

}while (nivel>6 || nivel<1);


//CONTADOR DE OPERACOES FEITAS


for (int h =0; h <n; h++){
    printf("\nQuantas operacoes o operador %d ja fez?: \n", h);
    scanf("%d", &operadores[h].Operacoes_feitas);
}

}

void Registrar_Maquinas(Equip maquinas[], int n){
    char ID_maquina[3];
    int tipo_maquina;
    int setor;
    int Estado_Operacional;
    int Operador_da_maquina;
    int prioridade;

    //REGISTRAR ID DA MAQUINA:

    do
    {
        for (int i=0; i<n; i++){
            printf("\nInforme o ID do equipamento(1 letra e 2 dígitos, nessa ordem): \n");
        fgets(ID_maquina,3, stdin);
         ID_maquina[strcspn(ID_maquina, "\n")] = "\0";
      while ((getchar()) != '\n' && getchar() != EOF);
        if (check_ID_maquina(ID_maquina)==1)
        {
            printf("ID válido!\n");
            strcpy(maquinas[i].ID_maquina, ID_maquina);
        }
        else{
            printf("ID invalido! tente novamente no formato de 1 letra e 2 digitos.\n");
        }

        }
    }while(check_ID_maquina(ID_maquina) != 1);

    //REGISTRAR TIPO DA MAQUINA:

    do
    {
        for (int i=0; i<n ; i++){
             printf("\n--- LISTA DOS TIPOS DE MAQUINAS ---\n");
        printf("-------------------------------------------");
        printf("1.Drone\n");
        printf("2.Scanner\n");
        printf("3.Sensor\n");
        printf("4.Esteira\n");
        printf("5.Braco mecanico\n");
        printf("6.Encerrar selecao\n");
        printf("-------------------------------------------");
        printf("\nSelecione sua opcao: \n");
        scanf("%d", tipo_maquina);
        switch(tipo_maquina){
        case 1:
            strcpy(maquinas[i].categoria, "Drone");
            break;
        case 2:
            strcpy(maquinas[i].categoria, "Scanner");
            break;
        case 3:
            strcpy(maquinas[i].categoria, "Sensor");
            break;
        case 4:
            strcpy(maquinas[i].categoria, "Esteira");
            break;
        case 5:
            strcpy(maquinas[i].categoria, "Braco mecanico");
            break;
        case 6:
            printf("Encerrando selecao\n");
            break;
        }

        }


    }while(tipo_maquina >6 || tipo_maquina<1);


    // REGISTRAR SETOR DA MAQUINA:
     do
{
    for (int i = 0; i <n; i++){
            printf("\n--- LISTA DE SETORES ---\n");
            printf("---------------------------");
            printf("\n1.Setor VX28-(Coleta)\n");
            printf("2.Setor VX29-(Montagem)\n");
            printf("3.Setor VX30-(Conserto)\n");
            printf("4.Setor VX31-(Entrega)\n");
            printf("5.Setor VX32-(Revisao geral)\n");
            printf("6.Encerrar selecao\n");
            printf("----------------------------");
            printf("\n");
            printf("Seleciona um dos setores acima (1-5): \n");
            scanf("%d", &setor);
            switch(setor){
            case 1:
                strcpy(maquinas[i].setor_maquina, "VX28");
                break;
            case 2:
                strcpy(maquinas[i].setor_maquina, "VX29");
                break;
            case 3:
                strcpy(maquinas[i].setor_maquina, "VX30");
                break;
            case 4:
                strcpy(maquinas[i].setor_maquina, "VX31");
                break;
            case 5:
                strcpy(maquinas[i].setor_maquina, "VX32");
                break;
            case 6:
                printf("Encerrando seleção...\n");
                break;
            default:
                printf("Erro!! Opcao invalida\n");
                break;


            }
    }

}while(setor >6 || setor <1);


// REGISTRAR ESTADO OPERACIONAL:
int nivel;
    do
{

    for(int j = 0; j<n; j++){
    printf("\n--- TABELA DE ESTADOS OPERACIONAIS ---\n");
    printf("1. Ativo\n");
    printf("2. Inativo\n");
    printf("3. Manutencao\n");
    printf("4. Encerrar selecao\n");
    printf("Selecione o Estado operacional do equipamento atual: \n");
    scanf("%d",nivel);
    switch(nivel){
    case 1:
        strcpy(maquinas[j].Estado, "Ativo");
        break;
    case 2:
        strcpy(maquinas[j].Estado, "Inativo");
        break;
    case 3:
        strcpy(maquinas[j].Estado, "Manutencao");
        break;
    case 4:
        printf("Encerrando selecao...\n");
        break;
    default:
        printf("\nEssa opcao nao existe! erro...");
     }
   }
}while (nivel> 4 || nivel <1);


//REGISTRAR O ID DO OPERADOR DESSE EQUIPAMENTO:
int ID;
int y;
 do
    {
    for (int i=0; i<n; i++){
      printf("\nInforme o ID do operador dessa maquina (4 digitos): " );
      scanf("%d",&ID);
      y = Check_ID_Op(ID);

      if (y == 4)
      {
          maquinas[i].id_operador_responsavel = ID;
      }
      else
      {
          printf("\nFormato incorreto! tente novamente...");
      }

    }
    }while(y!= 4);


//REGISTRAR O NIVEL DE PRIORIDADE DESSA MAQUINA

do
    {
        for (int i=0; i<n ; i++){
             printf("\n--- TABELA DE PRIORIDADES ---\n");
        printf("-------------------------------------------");
        printf("1.Drone (BAIXA)\n");
        printf("2.Scanner (ALTA)\n");
        printf("3.Sensor (MEDIA)\n");
        printf("4.Esteira (BAIXA)\n");
        printf("5.Braco mecanico(MEDIA)\n");
        printf("6.Encerrar selecao\n");
        printf("-------------------------------------------");
        printf("\nSelecione sua opcao: \n");
        scanf("%d", tipo_maquina);
        switch(tipo_maquina){
        case 1:
            strcpy(maquinas[i].Nivel_prioridade, "BAIXA");
            break;
        case 2:
            strcpy(maquinas[i].Nivel_prioridade, "ALTA");
            break;
        case 3:
            strcpy(maquinas[i].Nivel_prioridade, "MEDIA");
            break;
        case 4:
            strcpy(maquinas[i].Nivel_prioridade, "BAIXA");
            break;
        case 5:
            strcpy(maquinas[i].Nivel_prioridade, "MEDIA");
            break;
        case 6:
            printf("Encerrando selecao\n");
            break;
        default:
            printf("Erro!Opcao invalida, tente novamente...");
        }

        }


    }while(tipo_maquina >6 || tipo_maquina<1);

}

// Checa o ID do operador pra ver se tem 4 digitos:

int Check_ID_Op(int num){

    if (num < 10){
        return 1;
    }
    return 1+ Check_ID_Op(num/10);
}

// checa se o ID da maquina corresponde com o formato devido:

void check_ID_maquina(char id[]){

    if (strlen(id)!= 3)
    {
        return 0;
    }
    return isalpha((unsigned char)id[0])
    && isdigit((unsigned char)id[1])
    &&isdigit ((unsigned char)id[2]);

}

// listar todos operadores por nome,id,setor,nivel,status e operacoes feitas
void listar_opr_todos(Opr A[]){
    for(int i=1;i<51;i++)
    {
        printf("=======\n");
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Setor:%s\n",A[i].setor_operador);
        printf("Nivel:%s\n",A[i].nivel);
        printf("Status:%s\n",A[i].status);
        printf("Operacoes feitas:%d\n",A[i].Operacoes_feitas);
        printf("=======\n");

    }
}
// listar operadores,id,nome e status por setor (Rever isso com o Grupo)
void listar_opr_setor(Opr A[]){
        int opt;
        do{
        printf("\n--- LISTA DE SETORES ---\n");
        printf("---------------------------");
        printf("\n1.Setor VX28-(Coleta)\n");
        printf("2.Setor VX29-(Montagem)\n");
        printf("3.Setor VX30-(Conserto)\n");
        printf("4.Setor VX31-(Entrega)\n");
        printf("5.Setor VX32-(Revisao geral)\n");
        printf("6.Encerrar selecao\n");
        printf("----------------------------");
        printf("\n");
        printf("Seleciona um dos setores acima (1-5): \n");
        scanf("%d", &opt);
        switch(opt){
        case 1:
        printf("=======\n");
        printf("Setor: VX28\n");
        for(int i=1;i<51;i++){
        if (A[i].setor_operador=="VX28")
        {
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Status:%s\n",A[i].status);
        }
        }
        printf("=======\n");
        break;
        case 2:
        printf("=======\n");
        printf("Setor: VX29\n");
        for(int i=1;i<51;i++){
        if (A[i].setor_operador=="VX29")
        {
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Status:%s\n",A[i].status);
        }
        }
        printf("=======\n");
        break;
        case 3:
        printf("=======\n");
        printf("Setor: VX30\n");
        for(int i=1;i<51;i++){
        if (A[i].setor_operador=="VX30")
        {
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Status:%s\n",A[i].status);
        }
        }
        printf("=======\n");
        break;
        case 4:
        printf("=======\n");
        printf("Setor: VX31\n");
        for(int i=1;i<51;i++){
        if (A[i].setor_operador=="VX31")
        {
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Status:%s\n",A[i].status);
        }
        }
        printf("=======\n");
        break;
        case 5:
        printf("=======\n");
        printf("Setor: VX32\n");
        for(int i=1;i<51;i++){
        if (A[i].setor_operador=="VX32")
        {
        printf("Nome:%s\n",A[i].nome);
        printf("Id:%d\n",A[i].ID_operador);
        printf("Status:%s\n",A[i].status);
        }
        }
        printf("=======\n");
        break;
        }

        }while(opt>0 && opt<6);
}
//listar equipamento,id,tipo e estado por setor
void listar_maq_setor(Equip A[] ){
        int opt;
        do
        {
        printf("\n--- LISTA DE SETORES ---\n");
        printf("---------------------------");
        printf("\n1.Setor VX28-(Coleta)\n");
        printf("2.Setor VX29-(Montagem)\n");
        printf("3.Setor VX30-(Conserto)\n");
        printf("4.Setor VX31-(Entrega)\n");
        printf("5.Setor VX32-(Revisao geral)\n");
        printf("6.Encerrar selecao\n");
        printf("----------------------------");
        printf("\n");
        printf("Seleciona um dos setores acima (1-5): \n");
        scanf("%d", &opt);
        switch(opt){
        case 1:
        printf("=======\n");
        printf("Setor: VX28\n");
        for(int i=1;i<151;i++){
        if (A[i].setor_maquina=="VX28")
        {
        printf("Id:%s\n",A[i].ID_maquina);
        printf("Tipo:%d\n",A[i].categoria);
        printf("Estado operacional:%s\n",A[i].Estado);
        }
        }
        printf("=======\n");
        break;
        case 2:
        printf("=======\n");
        printf("Setor: VX29\n");
        for(int i=1;i<151;i++){
        if (A[i].setor_maquina=="VX29")
        {
        printf("Id:%s\n",A[i].ID_maquina);
        printf("Tipo:%d\n",A[i].categoria);
        printf("Estado operacional:%s\n",A[i].Estado);
        }
        }
        printf("=======\n");
        break;
        case 3:
        printf("=======\n");
        printf("Setor: VX30\n");
        for(int i=1;i<151;i++){
        if (A[i].setor_maquina=="VX30")
        {
        printf("Id:%s\n",A[i].ID_maquina);
        printf("Tipo:%d\n",A[i].categoria);
        printf("Estado operacional:%s\n",A[i].Estado);
        }
        }
        printf("=======\n");
        break;
        case 4:
        printf("=======\n");
        printf("Setor: VX31\n");
        for(int i=1;i<151;i++){
        if (A[i].setor_maquina=="VX31")
        {
        printf("Id:%s\n",A[i].ID_maquina);
        printf("Tipo:%d\n",A[i].categoria);
        printf("Estado operacional:%s\n",A[i].Estado);
        }
        }
        printf("=======\n");
        break;
        case 5:
        printf("=======\n");
        printf("Setor: VX32\n");
        for(int i=1;i<151;i++){
        if (A[i].setor_maquina=="VX32")
        {
        printf("Id:%s\n",A[i].ID_maquina);
        printf("Tipo:%d\n",A[i].categoria);
        printf("Estado operacional:%s\n",A[i].Estado);
        }
        }
        printf("=======\n");
        break;
        }
        }while(opt>0 && opt<6);
}

void listar_maq_op_setor(Opr op[], Equip maq[]){
int opt;
        do
        {
        printf("\n--- LISTA DE SETORES ---\n");
        printf("---------------------------");
        printf("\n1.Setor VX28-(Coleta)\n");
        printf("2.Setor VX29-(Montagem)\n");
        printf("3.Setor VX30-(Conserto)\n");
        printf("4.Setor VX31-(Entrega)\n");
        printf("5.Setor VX32-(Revisao geral)\n");
        printf("6.Encerrar selecao\n");
        printf("----------------------------");
        printf("\n");
        printf("Seleciona um dos setores acima (1-5): \n");
        scanf("%d", &opt);
        switch(opt){
        case 1:
        printf("=======\n");
        printf("Setor: VX28\n");
        printf("----Maquina----\n");
        for(int i=1;i<151;i++){
        if (maq[i].setor_maquina=="VX28")
        {
        printf("Id:%s\n",maq[i].ID_maquina);
        printf("Tipo:%s\n",maq[i].categoria);
        }
        }
        printf("----Operador----\n");
        for(int i=1;i<51;i++){
        if (op[i].setor_operador=="VX28")
        {
        printf("Id:%s\n",op[i].ID_operador);
        printf("Nome:%s\n",op[i].nome);
        }
        }
        printf("=======\n");
        break;
        case 2:
        printf("=======\n");
        printf("Setor: VX29\n");
        printf("----Maquina----\n");
        for(int i=1;i<151;i++){
        if (maq[i].setor_maquina=="VX29")
        {
        printf("Id:%s\n",maq[i].ID_maquina);
        printf("Tipo:%s\n",maq[i].categoria);
        }
        }
        printf("----Operador----\n");
        for(int i=1;i<51;i++){
        if (op[i].setor_operador=="VX29")
        {
        printf("Id:%s\n",op[i].ID_operador);
        printf("Nome:%s\n",op[i].nome);
        }
        }
        printf("=======\n");
        break;
        case 3:
        printf("=======\n");
        printf("Setor: VX30\n");
        printf("----Maquina----\n");
        for(int i=1;i<151;i++){
        if (maq[i].setor_maquina=="VX30")
        {
        printf("Id:%s\n",maq[i].ID_maquina);
        printf("Tipo:%s\n",maq[i].categoria);
        }
        }
        printf("----Operador----\n");
        for(int i=1;i<51;i++){
        if (op[i].setor_operador=="VX30")
        {
        printf("Id:%s\n",op[i].ID_operador);
        printf("Nome:%s\n",op[i].nome);
        }
        }
        printf("=======\n");
        break;
        case 4:
        printf("=======\n");
        printf("Setor: VX31\n");
        printf("----Maquina----\n");
        for(int i=1;i<151;i++){
        if (maq[i].setor_maquina=="VX31")
        {
        printf("Id:%s\n",maq[i].ID_maquina);
        printf("Tipo:%s\n",maq[i].categoria);
        }
        }
        printf("----Operador----\n");
        for(int i=1;i<51;i++){
        if (op[i].setor_operador=="VX31")
        {
        printf("Id:%s\n",op[i].ID_operador);
        printf("Nome:%s\n",op[i].nome);
        }
        }
        printf("=======\n");
        break;
        case 5:
        printf("=======\n");
        printf("Setor: VX32\n");
        printf("----Maquina----\n");
        for(int i=1;i<151;i++){
        if (maq[i].setor_maquina=="VX32")
        {
        printf("Id:%s\n",maq[i].ID_maquina);
        printf("Tipo:%s\n",maq[i].categoria);
        }
        }
        printf("----Operador----\n");
        for(int i=1;i<51;i++){
        if (op[i].setor_operador=="VX32")
        {
        printf("Id:%s\n",op[i].ID_operador);
        printf("Nome:%s\n",op[i].nome);
        }
        }
        printf("=======\n");
        break;
        }
        }while(opt>0 && opt<6);
}

void listar_op_moperacoes(Opr A[]){
int maior=-1,i;
for(i=1;i<51;i++)
{
    if(maior<A[i].Operacoes_feitas)
    {
        maior=A[i].Operacoes_feitas;
    }
}
printf("O(s) operador(es) com mais operacoes feitas são:\n");
for(i=1;i<51;i++)
{
    if(maior==A[i].Operacoes_feitas)
    {
        printf("Nome:%s Operacoes feitas:%d\n");
    }
}
}

// CASE 4: 

/*
1- dentro dessa função de atualização, preciso criar um mini-menu de seleção das seguintes
opções que ele pode escolher

-vou ter que usar um switch case para cada opção dentro da função atualização
-vou ter que acessar o vetor de struct e alterar conforme a opção que ele pedir (talvez usando ponteiro)

*/

void Atualização_Sistema(opr A[], Equip B[], int num){
    int opt1, opt2;
    int posicao= 0;
    int Existe = 0;
    char ID_maquina[3];

    printf("\n------------- OPCOES DE ATUALIZACAO -----------\n");
    printf("\n-----------------------------------------------\n");
    printf("1.Alterar Estado Operacional do equipamento \n");
    printf("2.Atualize a disponibilidade dos Operadores \n");
    printf("3.Mover equipamentos entre Setores \n");
    printf("4.Registrar ocorrências \n");
    printf("5.Desativar Registros \n");
    printf("6.Sair da selecao \n");
    printf("\n-----------------------------------------------\n");
    printf("Selecione uma opcao (1-6): \n");
    scanf("%d", &opt1);
    switch(opt){
    case 1:
        do
        {
            for(int i = 0; i< num; i++){
                printf("\nInforme o ID do equipamento(1 letra e 2 digitos): \n");
                fgets(ID_maquina, 3, stdin);
                x = check_ID_maquina(ID_maquina);
                if(x == 1){
                    for (int= 0; i<50; i++){
                            if(A[i].ID_maquina == ID_maquina){
                                Existe = 1;
                                posicao = i;
                                printf("\n--- Estados Operacionais ---\n");
                                printf("1.Ativo \n");
                                printf("2.Inativo \n");
                                printf("3.Manutencao \n");
                                printf("4. Sair da selecao \n");
                                printf("Qual o novo estado operacional deste equipamento?: \n");
                                scanf("%d", &opt2);
                                switch(opt2){
                                case 1:
                                    printf("O novo estado desse equipamento eh: 'Ativo'\n");
                                    strcpy(A[pos].Estado, "Ativo");
                                    break;
                                case 2:
                                     printf("O novo estado desse equipamento eh: 'Inativo'\n");
                                    strcpy(A[pos].Estado, "Inativo");
                                    break;
                                case 3:
                                     printf("O novo estado desse equipamento eh: 'Manutencao'\n");
                                    strcpy(A[pos].Estado, "Manutencao");
                                    break;
                                case 4:
                                    printf("\nSaindo da selecao...");
                                    break;
                                default:
                                    printf("Erro! Opcao invalida");

                                }

                            }
                            else
                            {
                                printf("\nEsse ID nao existe!\n");
                            }

                    }
                }
                else
                {
                    printf("\nFormato de ID invalido...\n");
                }

        }while(x!=1);



        }
    }


int main()
{
    int n1, n2, n3, n4, n5, n6, n7, lista;
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
        printf("3.Atualizacao de parametros\n");
        printf("4.Consulta de registros\n");
        printf("5.Relatorios operacionais\n");
        printf("6.Sair do Sistema\n");
        printf("\n--------------------------------------------------------------\n");
        printf("Selecione uma opcao: \n");
        scanf("%d", &opt);
        switch(opt){
        case 1:

            printf("\nQuantos Operadores voce deseja cadastrar?(1-40): \n");
            scanf("%d", &n1);
            Registrar_Operador(operadores, n1);
            break;
        case 2:

            printf("\nQuantos equipamentos voce deseja registrar?(1-40): \n");
            scanf("%d", &n2);
            Registrar_Maquinas(maquinas, n2);
            break;
        case 5:
        printf("\n--- LISTA DE SETORES ---\n");
        printf("---------------------------\n");
        printf("1.Listar todos operadore e suas respectivas informacoes\n");
        printf("2.Lista ID, nome e status dos operadores de um determinado setor\n");
        printf("3.Listar ID, tipo e estado operacional das maquinas de um determinado setor\n");
        printf("4.Listar ID e nome dos operadores e ID e tipo das maquinas de um determinado setor\n");
        printf("5.Listar os operadores, de cada setor, com o maior numero de operacoes realizadas\n");
        printf("6.Encerrar selecao\n");
        printf("----------------------------");
        printf("\n");
        printf("Seleciona uma das listas acima (1-5): \n");
        scanf("%d", &lista);
        switch(lista){
        case 1:
            listar_opr_todos(operadores);
        break;
        case 2:
            listar_opr_setor(operadores);
        break;
        case 3:
            listar_maq_setor(maquinas);
        break;
        case 4:
            listar_maq_op_setor(operadores,maquinas);
        break;
        case 5:
            listar_op_moperacoes(operadores);
        break;
            break;
        }
        }


    }while(opt >3 || opt<1);
    return 0;
}
