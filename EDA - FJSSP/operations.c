/*
Descrição:           Ficheiro com funções relativas às operações
                     FJSSP - parte 1
Desenvolvedor(es):   Ademar Valente (23155)
e-mail: a23155@alunos.ipca.pt
github: ademar1k82
Última atualização:  01/04/2022
Criação:             25/03/2022
*/

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include"header.h"

#pragma region FuncoesOperacoes

/**
 * Verifica se a operação existe
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] bool //Retorna se encontrou um jogo existente ou não
*/
bool OperationCheck(OperationList* operationsHeader, int id) 
{
    if (operationsHeader == NULL) return false;

    OperationList* auxOperations = operationsHeader;
    while (auxOperations != NULL) 
    {
        if (auxOperations->operation.id == id)
            return true;
        auxOperations = auxOperations->nextOperations;
    }

    return false;
}

/**
 * Cria uma operacao
 * @param [in] id
 * @param [in] machinesHeader
 * @param [out] newOperation	//Retorna a máquina aqui criada
*/
Operation* CreateOperation(int id) 
{
    Operation* newOperation = (Operation*)malloc(sizeof(Operation));
    if (newOperation == NULL) return NULL; // Se não há memória

    newOperation->id = id;
    newOperation->machines = NULL;

    return newOperation;
}

/**
* Cria novo nó para a lista de Operações
* @param [in] newOperation
* @param [out] newList para nó criado
*/
OperationList* CreateOperationListNode(Operation* newOperation)
{
    OperationList* newList = (OperationList*)calloc(1, sizeof(OperationList));

    newList->operation.id = newOperation->id;
    newList->operation.machines = newOperation->machines;
    newList->nextOperations = NULL;

    return newList;
}

/**
 * Insere uma operação
 * @param [in] operationsHeader
 * @param [in] newOperation
 * @param [out] operationsHeader	//Retorna a máquina aqui criada
*/
OperationList* InsertOperationList(OperationList* operationsHeader, Operation* newOperation)
{
    OperationList* newOperationCreated = CreateOperationListNode(newOperation);

    if (operationsHeader == NULL) 
    {
        operationsHeader = newOperationCreated;
    }
    else 
    {
        OperationList* auxOperations = operationsHeader;
        OperationList* auxAnt = NULL;
        while (auxOperations && auxOperations->operation.id < newOperationCreated->operation.id) 
        {
            auxAnt = auxOperations;
            auxOperations = auxOperations->nextOperations;
        }
        if (auxAnt == NULL) 
        {
            newOperationCreated->nextOperations = operationsHeader;
            operationsHeader = newOperationCreated;
        }
        else 
        {
            auxAnt->nextOperations = newOperationCreated;
            newOperationCreated->nextOperations = auxOperations;
        }
    }

    return operationsHeader;
}

/**
 * Procura a operação pretendida
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] aux	//Retorna a operação que era procurada
*/
Operation* OperationSearch(OperationList* operationsHeader, int id)
{
    if (operationsHeader == NULL) return NULL; //Lista vazia

    OperationList* auxOperations = operationsHeader;
    while (auxOperations != NULL) 
    {
        if (auxOperations->operation.id == id) 
        {
            Operation* newOperation = CreateOperation(auxOperations->operation.id);
            return newOperation;
        }
    }

    return NULL;
}

/**
 * Remover a operação
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] operationsHeader	//Retorna o header da lista de operações, mas com a operação já removida
*/

OperationList* RemoveOperation(OperationList* operationsHeader, int id) 
{
    if (operationsHeader == NULL) return NULL; //Lista vazia
    //if (!OperationExist(operationsHeader, id)) return NULL; // Se não existir a operação

    if (operationsHeader->operation.id == id) 
    {		//remove no inicio da lista
        OperationList* auxOperations = operationsHeader;
        operationsHeader = operationsHeader->nextOperations;
        free(auxOperations);
    }
    else 
    {
        OperationList* auxOperations = operationsHeader;
        OperationList* auxAnt = auxOperations;
        while (auxOperations && auxOperations->operation.id != id) 
        {	//procura para remover
            auxAnt = auxOperations;
            auxOperations = auxOperations->nextOperations;
        }
        if (auxOperations != NULL) {					//se encontrou, remove
            auxAnt->nextOperations = auxOperations->nextOperations;
            free(auxOperations);
        }
    }

    return operationsHeader;
}

/**
 * Alterar operações
 * @param [in] operationsHeader
 * @param [in] id
 * @param [in] changeTime
 * @param [in] Machineid
 * @param [out] operationsHeader	//Retorna o header daa lista de operações alterada
*/

OperationList* ChangeOperation(OperationList* operationsHeader, int Operationid, int Machineid, int changeTime) 
{
    if (operationsHeader == NULL) return NULL; //Lista vazia
    OperationList* auxOperations = operationsHeader;

    while (auxOperations != NULL) 
    {
        if (auxOperations->operation.id == Operationid) 
        {
            MachineList* auxMachines = auxOperations->operation.machines;
            while (auxMachines != NULL) 
            {
                if (auxMachines->machine.id == Machineid) 
                {
                    auxMachines->machine.time = changeTime;
                }
                auxMachines = auxMachines->nextMachines;
            }
        }
        auxOperations = auxOperations->nextOperations;
    }

    return operationsHeader;
}

/**
 * Tempo mínimo da operação
 * @param [in] operationsHeader
 * @param [out] operationsHeader	//Retorna a soma do tempos minimos
*/
int MinOperationTime(OperationList* operationsHeader)
{
    if (operationsHeader == NULL) return -1;
    int  sum = 0;

    OperationList* auxOperations = operationsHeader;
    while (auxOperations != NULL) 
    {
        sum += MinMachineTime(auxOperations->operation.machines);
        auxOperations = auxOperations->nextOperations;
    }

    return sum;
}

/**
 * Tempo máximo da operação
 * @param [in] operationsHeader
 * @param [out] operationsHeader	//Retorna a soma do tempos máximos
*/
int MaxOperationTime(OperationList* operationsHeader) 
{
    if (operationsHeader == NULL) return -1;
    int  sum = 0;

    OperationList* auxOperations = operationsHeader;
    while (auxOperations != NULL) 
    {
        sum += MaxMachineTime(auxOperations->operation.machines);
        auxOperations = auxOperations->nextOperations;
    }

    return sum;
}

/**
 * Contador de máquinas para cada operação
 * @param [in] operationsHeader
 * @param [out] operationsHeader	//Retorna quantas máquinas tem todas as operações
*/
int CountOperationMachines(OperationList* operationsHeader)
{
    if (operationsHeader == NULL) return 0;
    int count = 0;

    OperationList* auxOperations = operationsHeader;
    MachineList* auxMachines = auxOperations->operation.machines;
    while (auxMachines != NULL) 
    {
        count++;
        auxMachines = auxMachines->nextMachines;
    }

    return count;
}

/**
 * Tempo médio da operação
 * @param [in] operationsHeader
 * @param [out] average	//Retorna o tempo médio do tempo das máquinas
*/
float AverageOperationTime(OperationList* operationsHeader) 
{
    if (operationsHeader == NULL) return 0;
    int sum = 0;
    float count = CountOperationMachines(operationsHeader);

    OperationList* auxOperations = operationsHeader;
    MachineList* auxMachines = auxOperations->operation.machines;
    while (auxMachines != NULL) 
    {
        sum += auxMachines->machine.time;
        auxMachines = auxMachines->nextMachines;
    }
    auxOperations = auxOperations->nextOperations;

    return sum / count;
}

/**
 * Mostra a lista de operações e máquinas
 * @param [in] operationsHeader
*/
void ShowOperationList(OperationList* operationsHeader) 
{
    setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)
    OperationList* auxOperations = operationsHeader;
    printf("Operações:\n");
    while (auxOperations != NULL) 
    {
        printf("ID: %d\n", auxOperations->operation.id);
        ShowMachineList(operationsHeader->operation.machines);
        auxOperations = auxOperations->nextOperations;
    }
}

#pragma endregion