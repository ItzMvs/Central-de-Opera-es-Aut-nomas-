#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_CADASTRO 50

typedef struct {
    int ID_operador; // 4 digitos
    char nome[70];
    char setor_operador[5]; // Ex: VX28
    char nivel[50]; // Basico, Intermediario, Supervisor tecnico
    char status[50];  // Ativo(disponivel), Ocupado, Inativo, Bloqueado
    int Operacoes_feitas; // historico 
    int id_maquina_atual; // Rastreia a maquina associada (-1 se nenhuma)
} Opr;

typedef struct {
    char ID_maquina[4];      // 1 letra e 2 digitos + '\0'
    char category[40];       // Drone, Sensor, Esteira, Braco mecanico, Scanner
    char setor_maquina[5]; 
    char Estado[20];         // Ativo, Inativo, Manutencao
    int id_operador_responsavel; // ID do operador atribuido
    char Nivel_prioridade[10]; 
} Equip;

// --- PROTÓTIPOS DAS FUNÇÕES ---
int Check_ID_Op(int num);
int check_ID_maquina(char id[]);
int compativel_nivel(char nivel[], char categoria[]);
void Registrar_Operador(Opr operadores[], int n);
void Registrar_Maquinas(Equip maquinas[], int n);
void Atribuir_Operador_Maquina(Opr A[], Equip B[], int num_op, int num_maq);
void listar_opr_todos(Opr A[], int num);
void listar_opr_setor(Opr A[], int num);
void listar_maq_setor(Equip A[], int num);
void listar_maq_op_setor(Opr op[], Equip maq[], int num_op, int num_maq);
void listar_op_moperacoes(Opr A[], int num);
void Atualizacao_Sistema(Opr A[], Equip B[], int *num_op, int *num_maq);

// Limpa o buffer do teclado de forma segura
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Checa recursivamente se o ID possui exatamente 4 digitos
int Check_ID_Op(int num) {
    if (num < 10) {
        return 1;
    }
    return 1 + Check_ID_Op(num / 10);
}

// Checa formato da maquina (1 letra e 2 digitos)
int check_ID_maquina(char id[]) {
    if (strlen(id) != 3) {
        return 0;
    }
    return isalpha((unsigned char)id[0]) && isdigit((unsigned char)id[1]) && isdigit((unsigned char)id[2]);
}

// Verifica compatibilidade de nivel entre operador e maquina
int compativel_nivel(char nivel[], char categoria[]) {
    if (strcmp(categoria, "Scanner") == 0)
        return strcmp(nivel, "Supervisor tecnico") == 0;

    if (strcmp(categoria, "Sensor") == 0 || strcmp(categoria, "Braco mecanico") == 0)
        return (strcmp(nivel, "Intermediario") == 0 || strcmp(nivel, "Supervisor tecnico") == 0);

    if (strcmp(categoria, "Drone") == 0 || strcmp(categoria, "Esteira") == 0)
        return 1;

    return 0;
}

void Registrar_Operador(Opr operadores[], int n) {
    int ID, setor, nivel, status_opt;
    char nome[70];

    for (int i = 0; i < n; i++) {
        printf("\n=== CADASTRANDO OPERADOR %d ===\n", i + 1);
        operadores[i].id_maquina_atual = -1; 
        operadores[i].Operacoes_feitas = 0;  

        // 1. ID
        do {
            printf("Informe o ID do operador (4 digitos): ");
            scanf("%d", &ID);
            if (Check_ID_Op(ID) != 4) {
                printf("Formato incorreto! O ID precisa ter 4 digitos.\n");
            } else {
                operadores[i].ID_operador = ID;
            }
        } while (Check_ID_Op(ID) != 4);

        // 2. NOME
        limpar_buffer();
        do {
            printf("Informe o nome do operador (1-70 caracteres): ");
            fgets(nome, 70, stdin);
            nome[strcspn(nome, "\n")] = '\0';
            if (strlen(nome) < 1) {
                printf("Nome invalido! Tente novamente.\n");
            } else {
                strcpy(operadores[i].nome, nome);
            }
        } while (strlen(nome) < 1);

        // 3. SETOR
        do {
            printf("\n--- LISTA DE SETORES ---\n");
            printf("1. Setor VX28-(Coleta)\n2. Setor VX29-(Montagem)\n3. Setor VX30-(Conserto)\n");
            printf("4. Setor VX31-(Entrega)\n5. Setor VX32-(Revisao geral)\nSelecione (1-5): ");
            scanf("%d", &setor);
            
            if(setor == 1) strcpy(operadores[i].setor_operador, "VX28");
            else if(setor == 2) strcpy(operadores[i].setor_operador, "VX29");
            else if(setor == 3) strcpy(operadores[i].setor_operador, "VX30");
            else if(setor == 4) strcpy(operadores[i].setor_operador, "VX31");
            else if(setor == 5) strcpy(operadores[i].setor_operador, "VX32");
            else printf("Opcao invalida!\n");
        } while (setor < 1 || setor > 5);

        // 4. NIVEL
        do {
            printf("\n--- TABELA DE NIVEIS OPERACIONAIS ---\n");
            printf("1. Basico\n2. Intermediario\n3. Supervisor tecnico\nSelecione (1-3): ");
            scanf("%d", &nivel);
            
            if(nivel == 1) strcpy(operadores[i].nivel, "Basico");
            else if(nivel == 2) strcpy(operadores[i].nivel, "Intermediario");
            else if(nivel == 3) strcpy(operadores[i].nivel, "Supervisor tecnico");
            else printf("Opcao invalida!\n");
        } while (nivel < 1 || nivel > 3);

        // 5. STATUS
        do {
            printf("\n--- STATUS ATUAL DISPONIVEL ---\n");
            printf("1. Ativo (disponivel)\n2. Ocupado\n3. Inativo\n4. Bloqueado\nSelecione (1-4): ");
            scanf("%d", &status_opt);
            
            if(status_opt == 1) strcpy(operadores[i].status, "Ativo(disponivel)");
            else if(status_opt == 2) strcpy(operadores[i].status, "Ocupado");
            else if(status_opt == 3) strcpy(operadores[i].status, "Inativo");
            else if(status_opt == 4) strcpy(operadores[i].status, "Bloqueado");
            else printf("Opcao invalida!\n");
        } while (status_opt < 1 || status_opt > 4);
    }
}

void Registrar_Maquinas(Equip maquinas[], int n) {
    char ID_maquina[4];
    int tipo_maquina, setor, estado_opt;

    for (int i = 0; i < n; i++) {
        printf("\n=== CADASTRANDO EQUIPAMENTO %d ===\n", i + 1);
        maquinas[i].id_operador_responsavel = -1; 

        // 1. ID MAQUINA
        limpar_buffer();
        do {
            printf("Informe o ID do equipamento (1 letra e 2 digitos, ex: M01): ");
            fgets(ID_maquina, 4, stdin);
            ID_maquina[strcspn(ID_maquina, "\n")] = '\0';
            limpar_buffer();

            if (check_ID_maquina(ID_maquina) == 1) {
                strcpy(maquinas[i].ID_maquina, ID_maquina);
            } else {
                printf("ID invalido! Siga estritamente o formato (Ex: A12).\n");
            }
        } while (check_ID_maquina(ID_maquina) != 1);

        // 2. CATEGORIA E PRIORIDADE
        do {
            printf("\n--- LISTA DOS TIPOS DE MAQUINAS ---\n");
            printf("1. Drone\n2. Scanner\n3. Sensor\n4. Esteira\n5. Braco mecanico\nSelecione (1-5): ");
            scanf("%d", &tipo_maquina);
            
            switch (tipo_maquina) {
                case 1: strcpy(maquinas[i].category, "Drone"); strcpy(maquinas[i].Nivel_prioridade, "BAIXA"); break;
                case 2: strcpy(maquinas[i].category, "Scanner"); strcpy(maquinas[i].Nivel_prioridade, "ALTA"); break;
                case 3: strcpy(maquinas[i].category, "Sensor"); strcpy(maquinas[i].Nivel_prioridade, "MEDIA"); break;
                case 4: strcpy(maquinas[i].category, "Esteira"); strcpy(maquinas[i].Nivel_prioridade, "BAIXA"); break;
                case 5: strcpy(maquinas[i].category, "Braco mecanico"); strcpy(maquinas[i].Nivel_prioridade, "MEDIA"); break;
                default: printf("Opcao invalida!\n"); break;
            }
        } while (tipo_maquina < 1 || tipo_maquina > 5);

        // 3. SETOR
        do {
            printf("\n--- SELECIONE O SETOR DA MAQUINA ---\n");
            printf("1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nSelecione (1-5): ");
            scanf("%d", &setor);
            
            if(setor == 1) strcpy(maquinas[i].setor_maquina, "VX28");
            else if(setor == 2) strcpy(maquinas[i].setor_maquina, "VX29");
            else if(setor == 3) strcpy(maquinas[i].setor_maquina, "VX30");
            else if(setor == 4) strcpy(maquinas[i].setor_maquina, "VX31");
            else if(setor == 5) strcpy(maquinas[i].setor_maquina, "VX32");
            else printf("Opcao invalida!\n");
        } while (setor < 1 || setor > 5);

        // 4. ESTADO OPERACIONAL
        do {
            printf("\n--- TABELA DE ESTADOS OPERACIONAIS ---\n");
            printf("1. Ativo\n2. Inativo\n3. Manutencao\nSelecione (1-3): ");
            scanf("%d", &estado_opt);
            
            if(estado_opt == 1) strcpy(maquinas[i].Estado, "Ativo");
            else if(estado_opt == 2) strcpy(maquinas[i].Estado, "Inativo");
            else if(estado_opt == 3) strcpy(maquinas[i].Estado, "Manutencao");
            else printf("Opcao invalida!\n");
        } while (estado_opt < 1 || estado_opt > 3);
    }
}

void Atribuir_Operador_Maquina(Opr A[], Equip B[], int num_op, int num_maq) {
    char ID_maquina[4];
    int Encontrou = 0, pos1 = -1, count = 0;
    int indices_validos[MAX_CADASTRO];
    int pos_op, escolha;

    limpar_buffer();
    printf("\nInforme o ID da maquina para atribuicao: ");
    fgets(ID_maquina, 4, stdin);
    ID_maquina[strcspn(ID_maquina, "\n")] = '\0';

    for (int i = 0; i < num_maq; i++) {
        if (strcmp(B[i].ID_maquina, ID_maquina) == 0) {
            if (strcmp(B[i].Estado, "Ativo") != 0) {
                printf("\nEssa maquina nao esta ativa! Estado atual: %s\n", B[i].Estado);
                return;
            }
            Encontrou = 1;
            pos1 = i;
            break;
        }
    }

    if (!Encontrou) {
        printf("\nMaquina nao encontrada!\n");
        return;
    }

    for (int i = 0; i < num_op; i++) {
        int mesmo_setor = (strcmp(A[i].setor_operador, B[pos1].setor_maquina) == 0);
        int esta_ativo  = (strcmp(A[i].status, "Ativo(disponivel)") == 0);
        int nivel_ok    = compativel_nivel(A[i].nivel, B[pos1].category);
        int sem_maquina = (A[i].id_maquina_atual == -1);

        if (mesmo_setor && esta_ativo && nivel_ok && sem_maquina) {
            indices_validos[count++] = i;
        }
    }

    if (count == 0) {
        printf("\nNenhum operador compativel, livre e no mesmo setor foi encontrado.\n");
        return;
    }

    printf("\n--- MAQUINA SELECIONADA ---\nID: %s | Categoria: %s | Setor: %s\n", B[pos1].ID_maquina, B[pos1].category, B[pos1].setor_maquina);
    printf("\n--- OPERADORES COMPATIVEIS DISPONIVEIS ---\n");
    for (int i = 0; i < count; i++) {
        pos_op = indices_validos[i];
        printf("%d. Nome: %-20s | ID: %d | Nivel: %s\n", i + 1, A[pos_op].nome, A[pos_op].ID_operador, A[pos_op].nivel);
    }

    do {
        printf("\nEscolha o numero do operador (1-%d): ", count);
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > count);

    pos_op = indices_validos[escolha - 1];
    B[pos1].id_operador_responsavel = A[pos_op].ID_operador;
    A[pos_op].id_maquina_atual = pos1;
    strcpy(A[pos_op].status, "Ocupado");

    printf("\nOperador %s atribuido a maquina %s com sucesso!\n", A[pos_op].nome, B[pos1].ID_maquina);
}

void listar_opr_todos(Opr A[], int num) {
    if(num == 0) { printf("Nenhum operador registrado.\n"); return; }
    for (int i = 0; i < num; i++) {
        printf("\n=============================\n");
        printf("Nome: %s\nID: %d\nSetor: %s\nNivel: %s\nStatus: %s\nOperacoes feitas: %d\n", 
               A[i].nome, A[i].ID_operador, A[i].setor_operador, A[i].nivel, A[i].status, A[i].Operacoes_feitas);
        printf("=============================\n");
    }
}

void listar_opr_setor(Opr A[], int num) {
    int opt;
    char filtro[5];
    printf("\nSelecione o setor para filtrar:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    
    if(opt == 1) strcpy(filtro, "VX28");
    else if(opt == 2) strcpy(filtro, "VX29");
    else if(opt == 3) strcpy(filtro, "VX30");
    else if(opt == 4) strcpy(filtro, "VX31");
    else if(opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao Invalida.\n"); return; }

    printf("\n=== OPERADORES DO SETOR %s ===\n", filtro);
    for (int i = 0; i < num; i++) {
        if (strcmp(A[i].setor_operador, filtro) == 0) {
            printf("Nome: %s | ID: %d | Status: %s\n", A[i].nome, A[i].ID_operador, A[i].status);
        }
    }
}

void listar_maq_setor(Equip A[], int num) {
    int opt;
    char filtro[5];
    printf("\nSelecione o setor para filtrar as maquinas:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    
    if(opt == 1) strcpy(filtro, "VX28");
    else if(opt == 2) strcpy(filtro, "VX29");
    else if(opt == 3) strcpy(filtro, "VX30");
    else if(opt == 4) strcpy(filtro, "VX31");
    else if(opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao Invalida.\n"); return; }

    printf("\n=== MAQUINAS DO SETOR %s ===\n", filtro);
    for (int i = 0; i < num; i++) {
        if (strcmp(A[i].setor_maquina, filtro) == 0) {
            printf("ID: %s | Tipo: %s | Estado: %s\n", A[i].ID_maquina, A[i].category, A[i].Estado);
        }
    }
}

void listar_maq_op_setor(Opr op[], Equip maq[], int num_op, int num_maq) {
    int opt;
    char filtro[5];
    printf("\nFiltrar Geral por Setor:\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\nOpcao: ");
    scanf("%d", &opt);
    
    if(opt == 1) strcpy(filtro, "VX28");
    else if(opt == 2) strcpy(filtro, "VX29");
    else if(opt == 3) strcpy(filtro, "VX30");
    else if(opt == 4) strcpy(filtro, "VX31");
    else if(opt == 5) strcpy(filtro, "VX32");
    else { printf("Opcao Invalida.\n"); return; }

    printf("\n--- MAQUINAS NO SETOR %s ---\n", filtro);
    for (int i = 0; i < num_maq; i++) {
        if (strcmp(maq[i].setor_maquina, filtro) == 0) {
            printf("ID Maquina: %s | Categoria: %s\n", maq[i].ID_maquina, maq[i].category);
        }
    }
    printf("\n--- OPERADORES NO SETOR %s ---\n", filtro);
    for (int i = 0; i < num_op; i++) {
        if (strcmp(op[i].setor_operador, filtro) == 0) {
            printf("ID Operador: %d | Nome: %s\n", op[i].ID_operador, op[i].nome);
        }
    }
}

void listar_op_moperacoes(Opr A[], int num) {
    if(num == 0) return;
    int maior = -1;
    for (int i = 0; i < num; i++) {
        if (maior < A[i].Operacoes_feitas) {
            maior = A[i].Operacoes_feitas;
        }
    }
    printf("\nO(s) operador(es) com mais operacoes feitas (%d operacoes):\n", maior);
    for (int i = 0; i < num; i++) {
        if (maior == A[i].Operacoes_feitas) {
            printf("Nome: %s\n", A[i].nome);
        }
    }
}

void Atualizacao_Sistema(Opr A[], Equip B[], int *num_op, int *num_maq) {
    int opt1, opt2, opt3, opt4, opt6, opt7, opt8, opt9;
    char opt5[4]; 
    int Existe = 0; 
    int y, k, q;
    int pos = 0;
    char ID_maquina[4]; 

    printf("\n------------- OPCOES DE ATUALIZACAO -----------\n");
    printf("1. Alterar Estado Operacional do equipamento\n");
    printf("2. Atualize a disponibilidade dos Operadores\n");
    printf("3. Mover equipamentos entre Setores\n");
    printf("4. Registrar ocorrencias\n");
    printf("5. Desativar Registro de operador\n");
    printf("6. Desativar Registro de Equipamentos\n");
    printf("7. Sair da selecao\n");
    printf("-----------------------------------------------\n");
    printf("Selecione uma opcao (1-7): ");
    scanf("%d", &opt1);

    switch(opt1){
    case 1: // Alterar Estado Operacional do Equipamento
        limpar_buffer();
        printf("\nInforme o ID do equipamento (1 letra e 2 digitos): ");
        fgets(ID_maquina, 4, stdin);
        ID_maquina[strcspn(ID_maquina, "\n")] = '\0';
        
        if (check_ID_maquina(ID_maquina) == 1) {
            for (int j = 0; j < *num_maq; j++) {
                if (strcmp(B[j].ID_maquina, ID_maquina) == 0) {
                    Existe = 1;
                    pos = j;
                    break;
                }
            }
            if (Existe) {
                printf("\n--- Estados Operacionais ---\n1. Ativo\n2. Inativo\n3. Manutencao\n4. Sair\nEscolha: ");
                scanf("%d", &opt2);
                
                if (opt2 == 1) { 
                    strcpy(B[pos].Estado, "Ativo"); 
                    printf("Estado atualizado para Ativo.\n"); 
                }
                else if (opt2 == 2 || opt2 == 3) { 
                    // Se mudar para Inativo ou Manutencao, remove o operador vinculado
                    if (opt2 == 2) strcpy(B[pos].Estado, "Inativo");
                    else strcpy(B[pos].Estado, "Manutencao");
                    
                    int id_op_vinculado = B[pos].id_operador_responsavel;
                    if (id_op_vinculado != -1) {
                        for (int i = 0; i < *num_op; i++) {
                            if (A[i].ID_operador == id_op_vinculado) {
                                A[i].id_maquina_atual = -1;
                                strcpy(A[i].status, "Ativo(disponivel)"); // Libera o operador
                                break;
                            }
                        }
                        B[pos].id_operador_responsavel = -1; // Libera a máquina
                        printf("Aviso: Equipamento nao operacional. Operador responsavel desvinculado automaticamente!\n");
                    }
                    printf("Estado atualizado com sucesso.\n");
                } else {
                    printf("Saindo ou Opcao Invalida.\n");
                }
            } else {
                printf("Equipamento nao encontrado.\n");
            }
        } else {
            printf("Formato de ID invalido.\n");
        }
        break;

    case 2: // Atualizar disponibilidade do Operador
        printf("\nInforme o ID do operador (4 digitos): ");
        scanf("%d", &opt3);
        y = Check_ID_Op(opt3);
        if(y == 4){
            for (int i = 0; i < *num_op; i++){
                if(A[i].ID_operador == opt3){
                    Existe = 1;
                    pos = i;
                    break;
                }
            }
            if (Existe) {
                printf("\n--- STATUS DE DISPONIBILIDADE ---\n1. Ativo\n2. Ocupado\n3. Inativo\n4. Bloqueado\n5. Sair\nEscolha: ");
                scanf("%d", &opt4);
                
                if (opt4 == 1) { 
                    strcpy(A[pos].status, "Ativo(disponivel)"); 
                    printf("Status atualizado.\n"); 
                }
                else if (opt4 == 2) { 
                    strcpy(A[pos].status, "Ocupado"); 
                    printf("Status atualizado.\n"); 
                }
                // Se o operador for para Inativo ou Bloqueado, ele perde o vínculo da máquina que estava operando
                else if (opt4 == 3 || opt4 == 4) { 
                    if (opt4 == 3) strcpy(A[pos].status, "Inativo");
                    else strcpy(A[pos].status, "Bloqueado");
                    
                    int id_maq_vinculada = A[pos].id_maquina_atual;
                    if (id_maq_vinculada != -1) {
                        // Reseta a máquina onde ele trabalhava (id_maquina_atual guarda o índice da máquina no array)
                        B[id_maq_vinculada].id_operador_responsavel = -1;
                        A[pos].id_maquina_atual = -1;
                        printf("Aviso: Operador indisponivel. Desvinculado automaticamente da maquina %s!\n", B[id_maq_vinculada].ID_maquina);
                    }
                    printf("Status atualizado.\n"); 
                }
                else printf("Saindo...\n");
            } else {
                printf("\nEsse ID de operador nao existe!\n");
            }
        } else {
            printf("\nFormato de ID invalido...\n");
        }
        break;

    case 3: // Mover Equipamentos entre Setores
        limpar_buffer();
        printf("\nInforme o ID do equipamento (1 letra e 2 digitos): ");
        fgets(opt5, 4, stdin);
        opt5[strcspn(opt5, "\n")] = '\0';
        
        if(check_ID_maquina(opt5) == 1){
            for (int j = 0; j < *num_maq; j++){
                if(strcmp(B[j].ID_maquina, opt5) == 0){
                    Existe = 1;
                    pos = j;
                    break;
                }
            }
            if (Existe) {
                printf("\n--- LISTA DE SETORES ---\n1. VX28\n2. VX29\n3. VX30\n4. VX31\n5. VX32\n6. Sair\nEscolha: ");
                scanf("%d", &opt6);
                if(opt6 >= 1 && opt6 <= 5) {
                    char setores[5][5] = {"VX28", "VX29", "VX30", "VX31", "VX32"};
                    strcpy(B[pos].setor_maquina, setores[opt6-1]);
                    printf("Equipamento movido para o setor %s.\n", setores[opt6-1]);
                    
                    // Se mudar de setor, quebra a compatibilidade territorial. Remove operador.
                    int id_op_antigo = B[pos].id_operador_responsavel;
                    if (id_op_antigo != -1) {
                        for (int i = 0; i < *num_op; i++) {
                            if (A[i].ID_operador == id_op_antigo) {
                                A[i].id_maquina_atual = -1;
                                strcpy(A[i].status, "Ativo(disponivel)");
                                break;
                            }
                        }
                        B[pos].id_operador_responsavel = -1;
                        printf("Aviso: Maquina mudou de setor! O operador antigo foi desvinculado por estar em setor diferente.\n");
                    }
                } else {
                    printf("Saindo ou Opcao Invalida.\n");
                }
            } else {
                printf("\nEsse ID de equipamento nao existe!\n");
            }
        } else {
            printf("\nFormato de ID invalido...\n");
        }
        break;

    case 4:
        printf("Informe o ID do operador (4 digitos): ");
        scanf("%d", &opt7);
        k = Check_ID_Op(opt7);
        if(k == 4){
            for (int i = 0; i < *num_op; i++){
                if(A[i].ID_operador == opt7){
                    Existe = 1;
                    pos = i;
                    break;
                }
            }
            if (Existe) {
                printf("\nInforme o novo numero de operacoes desse operador: ");
                scanf("%d", &opt8);
                A[pos].Operacoes_feitas = opt8;
                printf("\nO numero de operacoes foi atualizado para: %d \n", opt8);
            } else {
                printf("\nEsse ID nao existe!\n");
            }
        } else {
            printf("\nFormato de ID invalido \n");
        }
        break;

    case 5:
        printf("Informe o ID do operador que perdera o registro (4 digitos): ");
        scanf("%d", &opt9);
        q = Check_ID_Op(opt9);
        if (q == 4) {
            for (int i = 0; i < *num_op; i++) {
                if (A[i].ID_operador == opt9) {
                    Existe = 1;
                    pos = i;
                    break;
                }
            }
            if (Existe == 1) {
                // Antes de deletar o operador, libera a máquina dele se ele estivesse trabalhando
                int id_maq_vinculada = A[pos].id_maquina_atual;
                if (id_maq_vinculada != -1) {
                    B[id_maq_vinculada].id_operador_responsavel = -1;
                }

                for (int i = pos; i < (*num_op) - 1; i++) {
                    A[i] = A[i + 1];
                }
                (*num_op)--; 
                printf("\nRegistro do operador ID %d removido com sucesso!\n", opt9);
            } else {
                printf("\nOperador com ID %d nao encontrado.\n", opt9);
            }
        } else {
            printf("\nFormato de ID invalido! Use 4 digitos.\n");
        }
        break;

    case 6:
        limpar_buffer();
        printf("Informe o ID da maquina que perdera o registro (ex: M01): ");
        fgets(ID_maquina, 4, stdin);
        ID_maquina[strcspn(ID_maquina, "\n")] = '\0';
        
        if (check_ID_maquina(ID_maquina) == 1) {
            for (int i = 0; i < *num_maq; i++) {
                if (strcmp(B[i].ID_maquina, ID_maquina) == 0) {
                    Existe = 1;
                    pos = i;
                    break;
                }
            }
            if (Existe == 1) {
                // Antes de deletar a máquina, libera o operador se houvesse algum trabalhando nela
                int id_op_vinculado = B[pos].id_operador_responsavel;
                if (id_op_vinculado != -1) {
                    for (int i = 0; i < *num_op; i++) {
                        if (A[i].ID_operador == id_op_vinculado) {
                            A[i].id_maquina_atual = -1;
                            strcpy(A[i].status, "Ativo(disponivel)");
                            break;
                        }
                    }
                }

                for (int i = pos; i < (*num_maq) - 1; i++) {
                    B[i] = B[i + 1];
                }
                (*num_maq)--; 
                printf("\nRegistro do equipamento %s removido com sucesso!\n", ID_maquina);
            } else {
                printf("\nEquipamento nao encontrado.\n");
            }
        } else {
            printf("\nFormato de ID invalido!\n");
        }
        break;

    case 7:
        printf("\nSaindo do menu de atualizacao...\n");
        break;

    default:
        printf("\nOpcao invalida.\n");
        break;
    }
}

int main() {
    Opr lista_operadores[MAX_CADASTRO];
    Equip lista_maquinas[MAX_CADASTRO];
    int qtd_op = 0, qtd_maq = 0;
    int opcao;

    do {
        printf("\n================ MENU PRINCIPAL ================\n");
        printf("1. Cadastrar Operadores\n");
        printf("2. Cadastrar Equipamentos\n");
        printf("3. Vincular Operador a uma Maquina\n");
        printf("4. Listar Todos os Operadores\n");
        printf("5. Listar Operadores por Setor\n");
        printf("6. Listar Maquinas por Setor\n");
        printf("7. Listar Relatorio Geral de Setor\n");
        printf("8. Exibir Operador com Mais Operacoes\n");
        printf("9. Menu de Atualizacoes do Sistema\n");
        printf("0. Sair do programa\n");
        printf("================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Quantos operadores deseja cadastrar? ");
                scanf("%d", &qtd_op);
                if(qtd_op > MAX_CADASTRO) qtd_op = MAX_CADASTRO;
                Registrar_Operador(lista_operadores, qtd_op);
                break;
            case 2:
                printf("Quantos equipamentos deseja cadastrar? ");
                scanf("%d", &qtd_maq);
                if(qtd_maq > MAX_CADASTRO) qtd_maq = MAX_CADASTRO;
                Registrar_Maquinas(lista_maquinas, qtd_maq);
                break;
            case 3:
                if(qtd_op == 0 || qtd_maq == 0) printf("Cadastre operadores e maquinas primeiro.\n");
                else Atribuir_Operador_Maquina(lista_operadores, lista_maquinas, qtd_op, qtd_maq);
                break;
            case 4: listar_opr_todos(lista_operadores, qtd_op); break;
            case 5: listar_opr_setor(lista_operadores, qtd_op); break;
            case 6: listar_maq_setor(lista_maquinas, qtd_maq); break;
            case 7: listar_maq_op_setor(lista_operadores, lista_maquinas, qtd_op, qtd_maq); break;
            case 8: listar_op_moperacoes(lista_operadores, qtd_op); break;
            case 9: 
                // Passa por referencia para que os cases 5 e 6 possam reduzir a quantidade real se deletarem algo
                Atualizacao_Sistema(lista_operadores, lista_maquinas, &qtd_op, &qtd_maq); 
                break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida, tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
