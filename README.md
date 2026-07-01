# Central de Operações Autônomas

Sistema em linguagem C para gestão de operadores e equipamentos industriais, desenvolvido como projeto acadêmico. O sistema controla o cadastro, a alocação e o monitoramento de operadores e máquinas distribuídos em 5 setores de uma planta industrial, aplicando regras de compatibilidade entre o nível técnico do operador e o tipo de equipamento.

## Funcionalidades

- **Cadastro de operadores**: nome, ID (4 dígitos, validado), setor, nível operacional (Básico, Intermediário, Supervisor Técnico) e status (Ativo, Ocupado, Inativo, Bloqueado).
- **Cadastro de equipamentos**: ID (1 letra + 2 dígitos), tipo (Drone, Scanner, Sensor, Esteira, Braço mecânico), setor, estado (Ativo, Inativo, Manutenção) e nível de prioridade.
- **Vinculação operador-máquina**: associa automaticamente operadores compatíveis (mesmo setor, nível técnico adequado ao tipo de equipamento e disponibilidade) a uma máquina ativa.
- **Listagens e relatórios**:
  - Todos os operadores cadastrados
  - Operadores por setor
  - Máquinas por setor
  - Relatório geral (operadores + máquinas) por setor
  - Operador com mais operações realizadas, por setor
- **Atualização do sistema**:
  - Alterar estado operacional de um equipamento
  - Atualizar disponibilidade/status de um operador
  - Mover equipamento entre setores
  - Registrar número de operações realizadas
  - Remover cadastro de operador ou equipamento (com desvinculação automática de máquinas/operadores associados)
- **Consulta de registros**:
  - Verificar disponibilidade de um operador (por nome ou ID)
  - Consultar estado operacional de um equipamento
  - Listar operadores livres e compatíveis com um equipamento/setor

## Estrutura de dados

O sistema é organizado em torno de duas structs principais:

```c
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
```

Os registros são mantidos em vetores estáticos (`MAX_OPERADORES = 50`, `MAX_EQUIPAMENTOS = 150`), sem uso de alocação dinâmica ou bibliotecas externas — apenas `stdio.h`, `string.h`, `ctype.h` e `stdlib.h`.

## Regras de compatibilidade

A vinculação entre operador e máquina só ocorre se, simultaneamente:

- o operador estiver no **mesmo setor** da máquina;
- o operador estiver **Ativo (disponível)**, sem máquina atribuída;
- o **nível técnico** do operador for compatível com o tipo de equipamento:
  - **Scanner** → exige Supervisor Técnico
  - **Sensor** / **Braço mecânico** → exige Intermediário ou Supervisor Técnico
  - **Drone** / **Esteira** → qualquer nível

## Setores disponíveis

| Código | Setor            |
|--------|------------------|
| VX28   | Coleta           |
| VX29   | Montagem         |
| VX30   | Conserto         |
| VX31   | Entrega          |
| VX32   | Revisão geral    |

## Como compilar e executar

```bash
gcc proj2.c -o central_operacoes
./central_operacoes
```

No Windows (Code::Blocks/MinGW), basta abrir o `proj2.c` no projeto e compilar normalmente (Build and Run).

### Dados de teste

Digitando a opção **99** no menu principal, o sistema carrega automaticamente 10 operadores e 10 equipamentos pré-cadastrados, cobrindo todos os setores, níveis e estados — útil para testar rapidamente as funcionalidades sem precisar cadastrar tudo manualmente.

## Menu principal

```
1.  Cadastrar Operadores
2.  Cadastrar Equipamentos
3.  Vincular Operador a uma Maquina
4.  Listar Todos os Operadores
5.  Listar Operadores por Setor
6.  Listar Maquinas por Setor
7.  Listar Relatorio Geral de Setor
8.  Operador com Mais Operacoes (por Setor)
9.  Menu de Atualizacoes do Sistema
10. Consulta de Registros
0.  Sair do programa
```

## Tecnologias utilizadas

- **Linguagem**: C
- **Ambiente de desenvolvimento**: Code::Blocks + MinGW

## Autores

Projeto desenvolvido em grupo, como trabalho acadêmico do curso de Engenharia de Computação — PUC Campinas.
