#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_OPERADORES   50
#define MAX_EQUIPAMENTOS 150

typedef struct {
    int  ID_operador;
    char nome[70];
    char setor_operador[5];
    char nivel[50];
    char status[50];
    int  Operacoes_feitas;
    char id_maquina_atual[4];
} Opr;

typedef struct {
    char ID_maquina[4];
    char category[40];
    char setor_maquina[5];
    char Estado[20];
    int  id_operador_responsavel;
    char Nivel_prioridade[10];
} Equip;

int  Check_ID_Op(int num);
int  check_ID_maquina(char id[]);
int  compativel_nivel(char nivel[], char categoria[]);
int  id_op_existe(Opr A[], int num, int id);
int  encontrar_maquina(Equip B[], int num, char id[]);
void Registrar_Operador(Opr operadores[], int *num_op);
void Registrar_Maquinas(Equip maquinas[], int *num_maq);
void Atribuir_Operador_Maquina(Opr A[], Equip B[], int num_op, int num_maq);
void listar_opr_todos(Opr A[], int num);
void listar_opr_setor(Opr A[], int num);
void listar_maq_setor(Equip A[], int num);
void listar_maq_op_setor(Opr op[], Equip maq[], int num_op, int num_maq);
void listar_op_moperacoes(Opr A[], int num);
void Atualizacao_Sistema(Opr A[], Equip B[], int *num_op, int *num_maq);
void menu_consultas(Opr A[], Equip B[], int num_op, int num_maq);
void carregar_dados_teste(Opr A[], Equip B[], int *num_op, int *num_maq);

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Check_ID_Op(int num) {
    if (num < 10) return 1;
    return 1 + Check_ID_Op(num / 10);
}

int check_ID_maquina(char id[]) {
    if (strlen(id) != 3) return 0;
    return isalpha((unsigned char)id[0]) &&
           isdigit((unsigned char)id[1]) &&
           isdigit((unsigned char)id[2]);
}

int compativel_nivel(char nivel[], char categoria[]) {
    if (strcmp(categoria, "Scanner") == 0)
        return strcmp(nivel, "Supervisor tecnico") == 0;
    if (strcmp(categoria, "Sensor") == 0 || strcmp(categoria, "Braco mecanico") == 0)
        return (strcmp(nivel, "Intermediario") == 0 || strcmp(nivel, "Supervisor tecnico") == 0);
    if (strcmp(categoria, "Drone") == 0 || strcmp(categoria, "Esteira") == 0)
        return 1;
    return 0;
}

int id_op_existe(Opr A[], int num, int id) {
    for (int i = 0; i < num; i++)
        if (A[i].ID_operador == id) return 1;
    return 0;
}

int encontrar_maquina(Equip B[], int num, char id[]) {
    for (int i = 0; i < num; i++)
        if (strcmp(B[i].ID_maquina, id) == 0) return i;
    return -1;
}

void Registrar_Operador(Opr operadores[], int *num_op) {
    int novos, ID, setor, nivel, status_opt;
    char nome[70];

    printf("Quantos operadores deseja cadastrar? ");
    scanf("%d", &novos);

    if (*num_op + novos > MAX_OPERADORES) {
        novos = MAX_OPERADORES - *num_op;
        printf("Ajustado para %d (limite de %d operadores).\n", novos, MAX_OPERADORES);
    }
    if (novos <= 0) { printf("Capacidade maxima de operadores ja atingida.\n"); return; }

    for (int i = 0; i < novos; i++) {
        int pos = *num_op;
        printf("\n=== CADASTRANDO OPERADOR %d ===\n", pos + 1);
        operadores[pos].id_maquina_atual[0] = '\0';
        operadores[pos].Operacoes_feitas = 0;

        do {
            printf("Informe o ID do operador (4 digitos): ");
            scanf("%d", &ID);
            if (Check_ID_Op(ID) != 4)
                printf("Formato incorreto! O ID precisa ter exatamente 4 digitos.\n");
            else if (id_op_existe(operadores, *num_op, ID))
                printf("ID %d ja cadastrado! Informe outro.\n", ID);
            else
                break;
        } while (1);
        operadores[pos].ID_operador = ID;

        limpar_buffer();
        do {
            printf("Informe o nome do operador (1-70 caracteres): ");
            fgets(nome, 70, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            if (strlen(nome) < 1) printf("Nome invalido! Tente novamente.\n");
        } while (strlen(nome) < 1);
        strcpy(operadores[pos].nome, nome);

        do {
            printf("\n--- LISTA DE SETORES ---\n");
            printf("1. Setor VX28-(Coleta)\n2. Setor VX29-(Montagem)\n3. Setor VX30-(Conserto)\n");
            printf("4. Setor VX31-(Entrega)\n5. Setor VX32-(Revisao geral)\nSelecione (1-5): ");
            scanf("%d", &setor);
            if      (setor == 1) strcpy(operadores[pos].setor_operador, "VX28");
            else if (setor == 2) strcpy(operadores[pos].setor_operador, "VX29");
            else if (setor == 3) strcpy(operadores[pos].setor_operador, "VX30");
            else if (setor == 4) strcpy(operadores[pos].setor_operador, "VX31");
            else if (setor == 5) strcpy(operadores[pos].setor_operador, "VX32");
            else printf("Opcao invalida!\n");
        } while (setor < 1 || setor > 5);

        do {
            printf("\n--- NIVEIS OPERACIONAIS ---\n");
            printf("1. Basico\n2. Intermediario\n3. Supervisor tecnico\nSelecione (1-3): ");
            scanf("%d", &nivel);
            if      (nivel == 1) strcpy(operadores[pos].nivel, "Basico");
            else if (nivel == 2) strcpy(operadores[pos].nivel, "Intermediario");
            else if (nivel == 3) strcpy(operadores[pos].nivel, "Supervisor tecnico");
            else printf("Opcao invalida!\n");
        } while (nivel < 1 || nivel > 3);

        do {
            printf("\n--- STATUS ---\n");
            printf("1. Ativo (disponivel)\n2. Ocupado\n3. Inativo\n4. Bloqueado\nSelecione (1-4): ");
            scanf("%d", &status_opt);
            if      (status_opt == 1) strcpy(operadores[pos].status, "Ativo(disponivel)");
            else if (status_opt == 2) strcpy(operadores[pos].status, "Ocupado");
            else if (status_opt == 3) strcpy(operadores[pos].status, "Inativo");
            else if (status_opt == 4) strcpy(operadores[pos].status, "Bloqueado");
            else printf("Opcao invalida!\n");
        } while (status_opt < 1 || status_opt > 4);

        (*num_op)++;
    }
}

void Registrar_Maquinas(Equip maquinas[], int *num_maq) {
    int novos, tipo_maquina, setor, estado_opt;
    char ID_maquina[4];

    printf("Quantos equipamentos deseja cadastrar? ");
    scanf("%d", &novos);

    if (*num_maq + novos > MAX_EQUIPAMENTOS) {
        novos = MAX_EQUIPAMENTOS - *num_maq;
        printf("Ajustado para %d (limite de %d equipamentos).\n", novos, MAX_EQUIPAMENTOS);
    }
    if (novos <= 0) { printf("Capacidade maxima de equipamentos ja atingida.\n"); return; }

    for (int i = 0; i < novos; i++) {
        int pos = *num_maq;
        printf("\n=== CADASTRANDO EQUIPAMENTO %d ===\n", pos + 1);
        maquinas[pos].id_operador_responsavel = -1;

        limpar_buffer();
        do {
            printf("Informe o ID do equipamento (1 letra e 2 digitos, ex: M01): ");
            fgets(ID_maquina, 4, stdin);
            ID_maquina[strcspn(ID_maquina, "\n")] = '\0';
            limpar_buffer();
            if (check_ID_maquina(ID_maquina) != 1)
                printf("ID invalido! Siga o formato (Ex: A12).\n");
            else if (encontrar_maquina(maquinas, *num_maq, ID_maquina) != -1)
                printf("ID %s ja cadastrado! Use outro.\n", ID_maquina);
            else
                break;
        } while (1);
        strcpy(maquinas[pos].ID_maquina, ID_maquina);

        do {
            printf("\n--- TIPOS DE MAQUINAS ---\n");
            printf("1. Drone\n2. Scanner\n3. Sensor\n4. Esteira\n5. Braco mecanico\nSelecione (1-5): ");
            scanf("%d", &tipo_maquina);
            switch (tipo_maquina) {
                case 1: strcpy(maquinas[pos].category, "Drone");         strcpy(maquinas[pos].Nivel_prioridade, "BAIXA"); break;
                case 2: strcpy(maquinas[pos].category, "Scanner");       strcpy(maquinas[pos].Nivel_prioridade, "ALTA");  break;
                case 3: strcpy(maquinas[pos].category, "Sensor");        strcpy(maquinas[pos].Nivel_prioridade, "MEDIA"); break;
                case 4: strcpy(maquinas[pos].category, "Esteira");       strcpy(maquinas[pos].Nivel_prioridade, "BAIXA"); break;
                case 5: strcpy(maquinas[pos].category, "Braco mecanico");strcpy(maquinas[pos].Nivel_prioridade, "MEDIA"); break;
                default: printf("Opcao invalida!\n"); break;
            }
        } while (tipo_maquina < 1 || tipo_maquina > 5);

        do {
            printf("\n--- SETOR DA MAQUINA ---\n");
            printf("1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nSelecione (1-5): ");
            scanf("%d", &setor);
            if      (setor == 1) strcpy(maquinas[pos].setor_maquina, "VX28");
            else if (setor == 2) strcpy(maquinas[pos].setor_maquina, "VX29");
            else if (setor == 3) strcpy(maquinas[pos].setor_maquina, "VX30");
            else if (setor == 4) strcpy(maquinas[pos].setor_maquina, "VX31");
            else if (setor == 5) strcpy(maquinas[pos].setor_maquina, "VX32");
            else printf("Opcao invalida!\n");
        } while (setor < 1 || setor > 5);

        do {
            printf("\n--- ESTADOS OPERACIONAIS ---\n");
            printf("1. Ativo\n2. Inativo\n3. Manutencao\nSelecione (1-3): ");
            scanf("%d", &estado_opt);
            if      (estado_opt == 1) strcpy(maquinas[pos].Estado, "Ativo");
            else if (estado_opt == 2) strcpy(maquinas[pos].Estado, "Inativo");
            else if (estado_opt == 3) strcpy(maquinas[pos].Estado, "Manutencao");
            else printf("Opcao invalida!\n");
        } while (estado_opt < 1 || estado_opt > 3);

        (*num_maq)++;
    }
}

void Atribuir_Operador_Maquina(Opr A[], Equip B[], int num_op, int num_maq) {
    char ID_maquina[4];
    int count = 0, pos1 = -1;
    int indices_validos[MAX_OPERADORES];
    int pos_op, escolha;

    limpar_buffer();
    printf("\nInforme o ID da maquina para atribuicao: ");
    fgets(ID_maquina, 4, stdin);
    ID_maquina[strcspn(ID_maquina, "\n")] = '\0';

    pos1 = encontrar_maquina(B, num_maq, ID_maquina);
    if (pos1 == -1) { printf("\nMaquina nao encontrada!\n"); return; }
    if (strcmp(B[pos1].Estado, "Ativo") != 0) {
        printf("\nEssa maquina nao esta ativa! Estado atual: %s\n", B[pos1].Estado);
        return;
    }

    for (int i = 0; i < num_op; i++) {
        int mesmo_setor = (strcmp(A[i].setor_operador, B[pos1].setor_maquina) == 0);
        int esta_ativo  = (strcmp(A[i].status, "Ativo(disponivel)") == 0);
        int nivel_ok    = compativel_nivel(A[i].nivel, B[pos1].category);
        int sem_maquina = (A[i].id_maquina_atual[0] == '\0');
        if (mesmo_setor && esta_ativo && nivel_ok && sem_maquina)
            indices_validos[count++] = i;
    }

    if (count == 0) { printf("\nNenhum operador compativel, livre e no mesmo setor encontrado.\n"); return; }

    printf("\n--- MAQUINA: %s | %s | Setor: %s ---\n", B[pos1].ID_maquina, B[pos1].category, B[pos1].setor_maquina);
    printf("\n--- OPERADORES DISPONIVEIS ---\n");
    for (int i = 0; i < count; i++) {
        pos_op = indices_validos[i];
        printf("%d. %-30s | ID: %d | Nivel: %s\n", i+1, A[pos_op].nome, A[pos_op].ID_operador, A[pos_op].nivel);
    }

    do {
        printf("\nEscolha o operador (1-%d): ", count);
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > count);

    pos_op = indices_validos[escolha - 1];
    B[pos1].id_operador_responsavel = A[pos_op].ID_operador;
    strcpy(A[pos_op].id_maquina_atual, B[pos1].ID_maquina);
    strcpy(A[pos_op].status, "Ocupado");
    printf("\nOperador %s atribuido a maquina %s com sucesso!\n", A[pos_op].nome, B[pos1].ID_maquina);
}

void listar_opr_todos(Opr A[], int num) {
    if (num == 0) { printf("Nenhum operador registrado.\n"); return; }
    for (int i = 0; i < num; i++) {
        printf("\n=============================\n");
        printf("Nome: %s\nID: %d\nSetor: %s\nNivel: %s\nStatus: %s\nOperacoes feitas: %d\n",
               A[i].nome, A[i].ID_operador, A[i].setor_operador,
               A[i].nivel, A[i].status, A[i].Operacoes_feitas);
        printf("=============================\n");
    }
}

void listar_opr_setor(Opr A[], int num) {
    int opt; char filtro[5];
    printf("\nSetor:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    if      (opt == 1) strcpy(filtro, "VX28");
    else if (opt == 2) strcpy(filtro, "VX29");
    else if (opt == 3) strcpy(filtro, "VX30");
    else if (opt == 4) strcpy(filtro, "VX31");
    else if (opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao invalida.\n"); return; }

    printf("\n=== OPERADORES DO SETOR %s ===\n", filtro);
    for (int i = 0; i < num; i++)
        if (strcmp(A[i].setor_operador, filtro) == 0)
            printf("Nome: %-30s | ID: %d | Status: %s\n", A[i].nome, A[i].ID_operador, A[i].status);
}

void listar_maq_setor(Equip A[], int num) {
    int opt; char filtro[5];
    printf("\nSetor:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    if      (opt == 1) strcpy(filtro, "VX28");
    else if (opt == 2) strcpy(filtro, "VX29");
    else if (opt == 3) strcpy(filtro, "VX30");
    else if (opt == 4) strcpy(filtro, "VX31");
    else if (opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao invalida.\n"); return; }

    printf("\n=== MAQUINAS DO SETOR %s ===\n", filtro);
    for (int i = 0; i < num; i++)
        if (strcmp(A[i].setor_maquina, filtro) == 0)
            printf("ID: %s | Tipo: %-16s | Estado: %s\n", A[i].ID_maquina, A[i].category, A[i].Estado);
}

void listar_maq_op_setor(Opr op[], Equip maq[], int num_op, int num_maq) {
    int opt; char filtro[5];
    printf("\nSetor:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    if      (opt == 1) strcpy(filtro, "VX28");
    else if (opt == 2) strcpy(filtro, "VX29");
    else if (opt == 3) strcpy(filtro, "VX30");
    else if (opt == 4) strcpy(filtro, "VX31");
    else if (opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao invalida.\n"); return; }

    printf("\n--- MAQUINAS NO SETOR %s ---\n", filtro);
    for (int i = 0; i < num_maq; i++)
        if (strcmp(maq[i].setor_maquina, filtro) == 0)
            printf("ID: %s | Tipo: %s\n", maq[i].ID_maquina, maq[i].category);

    printf("\n--- OPERADORES NO SETOR %s ---\n", filtro);
    for (int i = 0; i < num_op; i++)
        if (strcmp(op[i].setor_operador, filtro) == 0)
            printf("ID: %d | Nome: %s\n", op[i].ID_operador, op[i].nome);
}

void listar_op_moperacoes(Opr A[], int num) {
    char setores[5][5] = {"VX28", "VX29", "VX30", "VX31", "VX32"};
    if (num == 0) { printf("Nenhum operador registrado.\n"); return; }

    for (int s = 0; s < 5; s++) {
        int maior = -1, encontrou = 0;
        for (int i = 0; i < num; i++) {
            if (strcmp(A[i].setor_operador, setores[s]) == 0) {
                encontrou = 1;
                if (A[i].Operacoes_feitas > maior) maior = A[i].Operacoes_feitas;
            }
        }
        if (!encontrou) continue;

        printf("\n=== SETOR %s | Maior: %d operacoes ===\n", setores[s], maior);
        for (int i = 0; i < num; i++)
            if (strcmp(A[i].setor_operador, setores[s]) == 0 && A[i].Operacoes_feitas == maior)
                printf("  Nome: %-30s | ID: %d\n", A[i].nome, A[i].ID_operador);
    }
}

void consultar_operador_livre(Opr A[], int num) {
    char entrada[70];
    int achou = 0;

    limpar_buffer();
    printf("Digite o nome (ou parte) ou o ID do operador: ");
    fgets(entrada, 70, stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    if (strlen(entrada) == 0) { printf("Entrada vazia.\n"); return; }

    int so_digitos = 1;
    for (int i = 0; entrada[i] != '\0'; i++)
        if (!isdigit((unsigned char)entrada[i])) { so_digitos = 0; break; }

    printf("\n=== RESULTADO ===\n");
    if (so_digitos && strlen(entrada) == 4) {
        int id_busca = atoi(entrada);
        for (int i = 0; i < num; i++) {
            if (A[i].ID_operador == id_busca) {
                achou = 1;
                char *livre = (strcmp(A[i].status, "Ativo(disponivel)") == 0) ? "LIVRE" : "NAO LIVRE";
                printf("Nome: %-30s | ID: %d | Status: %-20s [%s]\n",
                       A[i].nome, A[i].ID_operador, A[i].status, livre);
                break;
            }
        }
    } else {
        for (int i = 0; i < num; i++) {
            if (strstr(A[i].nome, entrada) != NULL) {
                achou = 1;
                char *livre = (strcmp(A[i].status, "Ativo(disponivel)") == 0) ? "LIVRE" : "NAO LIVRE";
                printf("Nome: %-30s | ID: %d | Status: %-20s [%s]\n",
                       A[i].nome, A[i].ID_operador, A[i].status, livre);
            }
        }
    }
    if (!achou) printf("Nenhum operador encontrado.\n");
}

void consultar_estado_equipamento(Equip B[], int num) {
    char id_busca[4];
    limpar_buffer();
    printf("Informe o ID do equipamento (ex: A01): ");
    fgets(id_busca, 4, stdin);
    id_busca[strcspn(id_busca, "\n")] = '\0';
    limpar_buffer();

    int pos = encontrar_maquina(B, num, id_busca);
    if (pos == -1) { printf("Equipamento nao encontrado.\n"); return; }

    printf("\n=== EQUIPAMENTO %s ===\n", B[pos].ID_maquina);
    printf("Tipo      : %s\n", B[pos].category);
    printf("Setor     : %s\n", B[pos].setor_maquina);
    printf("Estado    : %s\n", B[pos].Estado);
    printf("Prioridade: %s\n", B[pos].Nivel_prioridade);
    if (B[pos].id_operador_responsavel != -1)
        printf("Operador  : ID %d\n", B[pos].id_operador_responsavel);
    else
        printf("Operador  : Nenhum atribuido\n");
}

void consultar_operadores_livres_setor(Opr A[], Equip B[], int num_op, int num_maq) {
    char id_maq[4];
    int achou = 0;

    limpar_buffer();
    printf("Informe o ID do equipamento (ex: A01): ");
    fgets(id_maq, 4, stdin);
    id_maq[strcspn(id_maq, "\n")] = '\0';
    limpar_buffer();

    int pos_maq = encontrar_maquina(B, num_maq, id_maq);
    if (pos_maq == -1) { printf("Equipamento nao encontrado.\n"); return; }

    printf("\n=== OPERADORES LIVRES PARA %s (%s) | SETOR %s ===\n",
           B[pos_maq].ID_maquina, B[pos_maq].category, B[pos_maq].setor_maquina);

    for (int i = 0; i < num_op; i++) {
        int mesmo_setor = (strcmp(A[i].setor_operador, B[pos_maq].setor_maquina) == 0);
        int esta_livre  = (strcmp(A[i].status, "Ativo(disponivel)") == 0);
        int nivel_ok    = compativel_nivel(A[i].nivel, B[pos_maq].category);
        int sem_maquina = (A[i].id_maquina_atual[0] == '\0');
        if (mesmo_setor && esta_livre && nivel_ok && sem_maquina) {
            printf("Nome: %-30s | ID: %d | Nivel: %s\n", A[i].nome, A[i].ID_operador, A[i].nivel);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum operador disponivel e compativel encontrado.\n");
}

void menu_consultas(Opr A[], Equip B[], int num_op, int num_maq) {
    int opt;
    printf("\n---------- CONSULTA DE REGISTROS ----------\n");
    printf("1. Verificar disponibilidade de operador (nome ou ID)\n");
    printf("2. Consultar estado operacional de um equipamento\n");
    printf("3. Listar operadores livres para um equipamento/setor\n");
    printf("4. Voltar\n");
    printf("-------------------------------------------\n");
    printf("Selecione: ");
    scanf("%d", &opt);

    switch (opt) {
        case 1: consultar_operador_livre(A, num_op); break;
        case 2: consultar_estado_equipamento(B, num_maq); break;
        case 3: consultar_operadores_livres_setor(A, B, num_op, num_maq); break;
        case 4: break;
        default: printf("Opcao invalida.\n");
    }
}

void Atualizacao_Sistema(Opr A[], Equip B[], int *num_op, int *num_maq) {
    int opt1, opt2, opt3, opt4, opt6, opt7, opt8, opt9;
    char opt5[4], ID_maquina[4];
    int Existe = 0, y, k, q, pos = 0;

    printf("\n------------- OPCOES DE ATUALIZACAO -----------\n");
    printf("1. Alterar Estado Operacional do equipamento\n");
    printf("2. Atualizar disponibilidade do Operador\n");
    printf("3. Mover equipamento entre Setores\n");
    printf("4. Registrar ocorrencias\n");
    printf("5. Desativar Registro de Operador\n");
    printf("6. Desativar Registro de Equipamento\n");
    printf("7. Sair\n");
    printf("-----------------------------------------------\n");
    printf("Selecione (1-7): ");
    scanf("%d", &opt1);

    switch(opt1) {

    case 1:
        limpar_buffer();
        printf("\nInforme o ID do equipamento: ");
        fgets(ID_maquina, 4, stdin);
        ID_maquina[strcspn(ID_maquina, "\n")] = '\0';

        if (check_ID_maquina(ID_maquina)) {
            pos = encontrar_maquina(B, *num_maq, ID_maquina);
            if (pos != -1) {
                printf("\n1. Ativo\n2. Inativo\n3. Manutencao\n4. Sair\nEscolha: ");
                scanf("%d", &opt2);
                if (opt2 == 1) {
                    strcpy(B[pos].Estado, "Ativo");
                    printf("Estado atualizado para Ativo.\n");
                } else if (opt2 == 2 || opt2 == 3) {
                    if (opt2 == 2) strcpy(B[pos].Estado, "Inativo");
                    else           strcpy(B[pos].Estado, "Manutencao");

                    if (B[pos].id_operador_responsavel != -1) {
                        for (int i = 0; i < *num_op; i++) {
                            if (A[i].ID_operador == B[pos].id_operador_responsavel) {
                                A[i].id_maquina_atual[0] = '\0';
                                strcpy(A[i].status, "Ativo(disponivel)");
                                break;
                            }
                        }
                        B[pos].id_operador_responsavel = -1;
                        printf("Aviso: Operador desvinculado automaticamente.\n");
                    }
                    printf("Estado atualizado.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
            } else {
                printf("Equipamento nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 2:
        printf("\nInforme o ID do operador (4 digitos): ");
        scanf("%d", &opt3);
        if (Check_ID_Op(opt3) == 4) {
            for (int i = 0; i < *num_op; i++)
                if (A[i].ID_operador == opt3) { Existe = 1; pos = i; break; }

            if (Existe) {
                printf("\n1. Ativo\n2. Ocupado\n3. Inativo\n4. Bloqueado\n5. Sair\nEscolha: ");
                scanf("%d", &opt4);
                if (opt4 == 1) {
                    strcpy(A[pos].status, "Ativo(disponivel)");
                    printf("Status atualizado.\n");
                } else if (opt4 == 2) {
                    strcpy(A[pos].status, "Ocupado");
                    printf("Status atualizado.\n");
                } else if (opt4 == 3 || opt4 == 4) {
                    if (opt4 == 3) strcpy(A[pos].status, "Inativo");
                    else           strcpy(A[pos].status, "Bloqueado");

                    if (A[pos].id_maquina_atual[0] != '\0') {
                        int pm = encontrar_maquina(B, *num_maq, A[pos].id_maquina_atual);
                        if (pm != -1) {
                            B[pm].id_operador_responsavel = -1;
                            printf("Aviso: Desvinculado da maquina %s.\n", B[pm].ID_maquina);
                        }
                        A[pos].id_maquina_atual[0] = '\0';
                    }
                    printf("Status atualizado.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
            } else {
                printf("Operador nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 3:
        limpar_buffer();
        printf("\nInforme o ID do equipamento: ");
        fgets(opt5, 4, stdin);
        opt5[strcspn(opt5, "\n")] = '\0';

        if (check_ID_maquina(opt5)) {
            pos = encontrar_maquina(B, *num_maq, opt5);
            if (pos != -1) {
                printf("\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\n6. Sair\nSetor destino: ");
                scanf("%d", &opt6);
                if (opt6 >= 1 && opt6 <= 5) {
                    char setores[5][5] = {"VX28","VX29","VX30","VX31","VX32"};
                    strcpy(B[pos].setor_maquina, setores[opt6-1]);
                    printf("Equipamento movido para %s.\n", setores[opt6-1]);

                    if (B[pos].id_operador_responsavel != -1) {
                        for (int i = 0; i < *num_op; i++) {
                            if (A[i].ID_operador == B[pos].id_operador_responsavel) {
                                A[i].id_maquina_atual[0] = '\0';
                                strcpy(A[i].status, "Ativo(disponivel)");
                                break;
                            }
                        }
                        B[pos].id_operador_responsavel = -1;
                        printf("Aviso: Operador desvinculado por mudanca de setor.\n");
                    }
                } else {
                    printf("Opcao invalida.\n");
                }
            } else {
                printf("Equipamento nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 4:
        printf("Informe o ID do operador (4 digitos): ");
        scanf("%d", &opt7);
        if (Check_ID_Op(opt7) == 4) {
            for (int i = 0; i < *num_op; i++)
                if (A[i].ID_operador == opt7) { Existe = 1; pos = i; break; }
            if (Existe) {
                printf("Informe o novo numero de operacoes: ");
                scanf("%d", &opt8);
                A[pos].Operacoes_feitas = opt8;
                printf("Operacoes atualizadas para %d.\n", opt8);
            } else {
                printf("Operador nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 5:
        printf("Informe o ID do operador a remover (4 digitos): ");
        scanf("%d", &opt9);
        if (Check_ID_Op(opt9) == 4) {
            for (int i = 0; i < *num_op; i++)
                if (A[i].ID_operador == opt9) { Existe = 1; pos = i; break; }
            if (Existe) {
                if (A[pos].id_maquina_atual[0] != '\0') {
                    int pm = encontrar_maquina(B, *num_maq, A[pos].id_maquina_atual);
                    if (pm != -1) B[pm].id_operador_responsavel = -1;
                }
                for (int i = pos; i < (*num_op) - 1; i++) A[i] = A[i+1];
                (*num_op)--;
                printf("Registro do operador ID %d removido.\n", opt9);
            } else {
                printf("Operador nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 6:
        limpar_buffer();
        printf("Informe o ID do equipamento a remover (ex: M01): ");
        fgets(ID_maquina, 4, stdin);
        ID_maquina[strcspn(ID_maquina, "\n")] = '\0';

        if (check_ID_maquina(ID_maquina)) {
            pos = encontrar_maquina(B, *num_maq, ID_maquina);
            if (pos != -1) {
                if (B[pos].id_operador_responsavel != -1) {
                    for (int i = 0; i < *num_op; i++) {
                        if (A[i].ID_operador == B[pos].id_operador_responsavel) {
                            A[i].id_maquina_atual[0] = '\0';
                            strcpy(A[i].status, "Ativo(disponivel)");
                            break;
                        }
                    }
                }
                for (int i = pos; i < (*num_maq) - 1; i++) B[i] = B[i+1];
                (*num_maq)--;
                printf("Registro do equipamento %s removido.\n", ID_maquina);
            } else {
                printf("Equipamento nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 7:
        printf("Saindo do menu de atualizacao...\n");
        break;

    default:
        printf("Opcao invalida.\n");
        break;
    }
}

void carregar_dados_teste(Opr A[], Equip B[], int *num_op, int *num_maq) {
    /* --- 10 OPERADORES: todos os setores, niveis e status --- */
    A[0].ID_operador = 1001; strcpy(A[0].nome, "Ana");
    strcpy(A[0].setor_operador, "VX28"); strcpy(A[0].nivel, "Supervisor tecnico");
    strcpy(A[0].status, "Ocupado"); A[0].Operacoes_feitas = 15;
    strcpy(A[0].id_maquina_atual, "A01");

    A[1].ID_operador = 2002; strcpy(A[1].nome, "Beto");
    strcpy(A[1].setor_operador, "VX28"); strcpy(A[1].nivel, "Intermediario");
    strcpy(A[1].status, "Ativo(disponivel)"); A[1].Operacoes_feitas = 8;
    A[1].id_maquina_atual[0] = '\0';

    A[2].ID_operador = 3003; strcpy(A[2].nome, "Cleo");
    strcpy(A[2].setor_operador, "VX29"); strcpy(A[2].nivel, "Basico");
    strcpy(A[2].status, "Ativo(disponivel)"); A[2].Operacoes_feitas = 5;
    A[2].id_maquina_atual[0] = '\0';

    A[3].ID_operador = 4004; strcpy(A[3].nome, "Davi");
    strcpy(A[3].setor_operador, "VX29"); strcpy(A[3].nivel, "Supervisor tecnico");
    strcpy(A[3].status, "Ocupado"); A[3].Operacoes_feitas = 20;
    strcpy(A[3].id_maquina_atual, "D04");

    A[4].ID_operador = 5005; strcpy(A[4].nome, "Eva");
    strcpy(A[4].setor_operador, "VX30"); strcpy(A[4].nivel, "Intermediario");
    strcpy(A[4].status, "Ocupado"); A[4].Operacoes_feitas = 12;
    strcpy(A[4].id_maquina_atual, "E01");

    A[5].ID_operador = 6006; strcpy(A[5].nome, "Fabi");
    strcpy(A[5].setor_operador, "VX30"); strcpy(A[5].nivel, "Basico");
    strcpy(A[5].status, "Inativo"); A[5].Operacoes_feitas = 2;
    A[5].id_maquina_atual[0] = '\0';

    A[6].ID_operador = 7007; strcpy(A[6].nome, "Gabi");
    strcpy(A[6].setor_operador, "VX31"); strcpy(A[6].nivel, "Supervisor tecnico");
    strcpy(A[6].status, "Ativo(disponivel)"); A[6].Operacoes_feitas = 18;
    A[6].id_maquina_atual[0] = '\0';

    A[7].ID_operador = 8008; strcpy(A[7].nome, "Hugo");
    strcpy(A[7].setor_operador, "VX31"); strcpy(A[7].nivel, "Basico");
    strcpy(A[7].status, "Bloqueado"); A[7].Operacoes_feitas = 1;
    A[7].id_maquina_atual[0] = '\0';

    A[8].ID_operador = 9009; strcpy(A[8].nome, "Iris");
    strcpy(A[8].setor_operador, "VX32"); strcpy(A[8].nivel, "Intermediario");
    strcpy(A[8].status, "Ativo(disponivel)"); A[8].Operacoes_feitas = 9;
    A[8].id_maquina_atual[0] = '\0';

    A[9].ID_operador = 1010; strcpy(A[9].nome, "Joao");
    strcpy(A[9].setor_operador, "VX32"); strcpy(A[9].nivel, "Basico");
    strcpy(A[9].status, "Ativo(disponivel)"); A[9].Operacoes_feitas = 3;
    A[9].id_maquina_atual[0] = '\0';

    *num_op = 10;

    /* --- 10 EQUIPAMENTOS: todos os tipos, setores e estados --- */
    strcpy(B[0].ID_maquina, "A01"); strcpy(B[0].category, "Scanner");
    strcpy(B[0].setor_maquina, "VX28"); strcpy(B[0].Estado, "Ativo");
    strcpy(B[0].Nivel_prioridade, "ALTA"); B[0].id_operador_responsavel = 1001;

    strcpy(B[1].ID_maquina, "B02"); strcpy(B[1].category, "Sensor");
    strcpy(B[1].setor_maquina, "VX28"); strcpy(B[1].Estado, "Ativo");
    strcpy(B[1].Nivel_prioridade, "MEDIA"); B[1].id_operador_responsavel = -1;

    strcpy(B[2].ID_maquina, "C03"); strcpy(B[2].category, "Drone");
    strcpy(B[2].setor_maquina, "VX29"); strcpy(B[2].Estado, "Ativo");
    strcpy(B[2].Nivel_prioridade, "BAIXA"); B[2].id_operador_responsavel = -1;

    strcpy(B[3].ID_maquina, "D04"); strcpy(B[3].category, "Esteira");
    strcpy(B[3].setor_maquina, "VX29"); strcpy(B[3].Estado, "Ativo");
    strcpy(B[3].Nivel_prioridade, "BAIXA"); B[3].id_operador_responsavel = 4004;

    strcpy(B[4].ID_maquina, "E01"); strcpy(B[4].category, "Braco mecanico");
    strcpy(B[4].setor_maquina, "VX30"); strcpy(B[4].Estado, "Ativo");
    strcpy(B[4].Nivel_prioridade, "MEDIA"); B[4].id_operador_responsavel = 5005;

    strcpy(B[5].ID_maquina, "F02"); strcpy(B[5].category, "Scanner");
    strcpy(B[5].setor_maquina, "VX30"); strcpy(B[5].Estado, "Inativo");
    strcpy(B[5].Nivel_prioridade, "ALTA"); B[5].id_operador_responsavel = -1;

    strcpy(B[6].ID_maquina, "G03"); strcpy(B[6].category, "Drone");
    strcpy(B[6].setor_maquina, "VX31"); strcpy(B[6].Estado, "Ativo");
    strcpy(B[6].Nivel_prioridade, "BAIXA"); B[6].id_operador_responsavel = -1;

    strcpy(B[7].ID_maquina, "H04"); strcpy(B[7].category, "Sensor");
    strcpy(B[7].setor_maquina, "VX31"); strcpy(B[7].Estado, "Manutencao");
    strcpy(B[7].Nivel_prioridade, "MEDIA"); B[7].id_operador_responsavel = -1;

    strcpy(B[8].ID_maquina, "I01"); strcpy(B[8].category, "Esteira");
    strcpy(B[8].setor_maquina, "VX32"); strcpy(B[8].Estado, "Ativo");
    strcpy(B[8].Nivel_prioridade, "BAIXA"); B[8].id_operador_responsavel = -1;

    strcpy(B[9].ID_maquina, "J02"); strcpy(B[9].category, "Braco mecanico");
    strcpy(B[9].setor_maquina, "VX32"); strcpy(B[9].Estado, "Ativo");
    strcpy(B[9].Nivel_prioridade, "MEDIA"); B[9].id_operador_responsavel = -1;

    *num_maq = 10;

    printf("\n[TESTE] 10 operadores e 10 equipamentos carregados!\n");
    printf("\n--- VINCULOS ATIVOS ---\n");
    printf("  Ana  (1001) -> A01 (Scanner/VX28)\n");
    printf("  Davi (4004) -> D04 (Esteira/VX29)\n");
    printf("  Eva  (5005) -> E01 (Braco mecanico/VX30)\n");
    printf("\n--- VINCULOS DISPONIVEIS PARA TESTAR (op.3) ---\n");
    printf("  B02 (Sensor/VX28)        <- Beto (2002, Intermediario)\n");
    printf("  C03 (Drone/VX29)         <- Cleo (3003, Basico)\n");
    printf("  G03 (Drone/VX31)         <- Gabi (7007, Supervisor tecnico)\n");
    printf("  I01 (Esteira/VX32)       <- Iris (9009) ou Joao (1010)\n");
    printf("  J02 (Braco mecanico/VX32)<- Iris (9009, Intermediario)\n");
    printf("\n--- CASOS ESPECIAIS ---\n");
    printf("  F02=Inativo, H04=Manutencao | Fabi=Inativo, Hugo=Bloqueado\n");
    printf("  Maior ops por setor: Ana(15)/VX28 Davi(20)/VX29 Eva(12)/VX30 Gabi(18)/VX31 Iris(9)/VX32\n");
}

int main() {
    Opr   lista_operadores[MAX_OPERADORES];
    Equip lista_maquinas[MAX_EQUIPAMENTOS];
    int   qtd_op = 0, qtd_maq = 0, opcao;

    do {
        printf("\n================ MENU PRINCIPAL ================\n");
        printf("1.  Cadastrar Operadores\n");
        printf("2.  Cadastrar Equipamentos\n");
        printf("3.  Vincular Operador a uma Maquina\n");
        printf("4.  Listar Todos os Operadores\n");
        printf("5.  Listar Operadores por Setor\n");
        printf("6.  Listar Maquinas por Setor\n");
        printf("7.  Listar Relatorio Geral de Setor\n");
        printf("8.  Operador com Mais Operacoes (por Setor)\n");
        printf("9.  Menu de Atualizacoes do Sistema\n");
        printf("10. Consulta de Registros\n");
        printf("0.  Sair do programa\n");
        printf("================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:  Registrar_Operador(lista_operadores, &qtd_op); break;
            case 2:  Registrar_Maquinas(lista_maquinas, &qtd_maq); break;
            case 3:
                if (qtd_op == 0 || qtd_maq == 0) printf("Cadastre operadores e maquinas primeiro.\n");
                else Atribuir_Operador_Maquina(lista_operadores, lista_maquinas, qtd_op, qtd_maq);
                break;
            case 4:  listar_opr_todos(lista_operadores, qtd_op); break;
            case 5:  listar_opr_setor(lista_operadores, qtd_op); break;
            case 6:  listar_maq_setor(lista_maquinas, qtd_maq); break;
            case 7:  listar_maq_op_setor(lista_operadores, lista_maquinas, qtd_op, qtd_maq); break;
            case 8:  listar_op_moperacoes(lista_operadores, qtd_op); break;
            case 9:  Atualizacao_Sistema(lista_operadores, lista_maquinas, &qtd_op, &qtd_maq); break;
            case 10: menu_consultas(lista_operadores, lista_maquinas, qtd_op, qtd_maq); break;
            case 99: carregar_dados_teste(lista_operadores, lista_maquinas, &qtd_op, &qtd_maq); break;
            case 0:  printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
