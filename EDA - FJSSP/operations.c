/*
Descri��o:           Ficheiro com fun��es relativas �s opera��es
                     FJSSP - parte 1
Desenvolvedor(es):   Ademar Valente (23155)
e-mail: a23155@alunos.ipca.pt
github: ademar1k82
�ltima atualiza��o:  01/04/2022
Cria��o:             25/03/2022
*/

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include"header.h"

#pragma region FuncoesOperacoes

/**
 * Verifica se a opera��o existe
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] bool //Retorna se encontrou um jogo existente ou n�o
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
 * @param [out] newOperation	//Retorna a m�quina aqui criada
*/
Operation* CreateOperation(int id) 
{
    Operation* newOperation = (Operation*)malloc(sizeof(Operation));
    if (newOperation == NULL) return NULL; // Se n�o h� mem�ria

    newOperation->id = id;
    newOperation->machines = NULL;

    return newOperation;
}

/**
* Cria novo n� para a lista de Opera��es
* @param [in] newOperation
* @param [out] newList para n� criado
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
 * Insere uma opera��o
 * @param [in] operationsHeader
 * @param [in] newOperation
 * @param [out] operationsHeader	//Retorna a m�quina aqui criada
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
 * Procura a opera��o pretendida
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] aux	//Retorna a opera��o que era procurada
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
 * Remover a opera��o
 * @param [in] operationsHeader
 * @param [in] id
 * @param [out] operationsHeader	//Retorna o header da lista de opera��es, mas com a opera��o j� removida
*/

OperationList* RemoveOperation(OperationList* operationsHeader, int id) 
{
    if (operationsHeader == NULL) return NULL; //Lista vazia
    //if (!OperationExist(operationsHeader, id)) return NULL; // Se n�o existir a opera��o

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
 * Alterar opera��es
 * @param [in] operationsHeader
 * @param [in] id
 * @param [in] changeTime
 * @param [in] Machineid
 * @param [out] operationsHeader	//Retorna o header daa lista de opera��es alterada
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
 * Tempo m�nimo da opera��o
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
 * Tempo m�ximo da opera��o
 * @param [in] operationsHeader
 * @param [out] operationsHeader	//Retorna a soma do tempos m�ximos
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
 * Contador de m�quinas para cada opera��o
 * @param [in] operationsHeader
 * @param [out] operationsHeader	//Retorna quantas m�quinas tem todas as opera��es
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
 * Tempo m�dio da opera��o
 * @param [in] operationsHeader
 * @param [out] average	//Retorna o tempo m�dio do tempo das m�quinas
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
 * Mostra a lista de opera��es e m�quinas
 * @param [in] operationsHeader
*/
void ShowOperationList(OperationList* operationsHeader) 
{
    setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)
    OperationList* auxOperations = operationsHeader;
    printf("Opera��es:\n");
    while (auxOperations != NULL) 
    {
        printf("ID: %d\n", auxOperations->operation.id);
        ShowMachineList(operationsHeader->operation.machines);
        auxOperations = auxOperations->nextOperations;
    }
}

#pragma endregion