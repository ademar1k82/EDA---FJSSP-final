/*
Descrição:           Ficheiro com funções relativas às máquinas
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

#pragma region FuncoesMaquinas

/**
 * Verifica se a maquina existe
 * @param [in] maquinasHeader
 * @param [in] id
 * @param [out] bool //Retorna se encontrou um jogo existente ou não
*/
bool MachineCheck(MachineList* machinesHeader, int id) 
{
    if (machinesHeader == NULL) return false;

    MachineList* aux = machinesHeader;
    while (aux != NULL) 
    {
        if (aux->machine.id == id)
            return true;
        aux = aux->nextMachines;
    }

    return false;
}

/**
 * Cria uma máquina
 * @param [in] id
 * @param [in] time
 * @param [out] newMachine	//Retorna a máquina aqui criada
*/
Machine* CreateMachine(int id, int time) 
{
    Machine* newMachine = (Machine*)malloc(sizeof(Machine));
    if (newMachine == NULL) return NULL; // Se não há memória

    newMachine->id = id;
    newMachine->time = time;

    return newMachine;
}

/**
* Cria novo nó para a lista de Maquinas
* @param [in] newMachine
* @param [out] newList //Retorna uma nova lista para nó criado
*/
MachineList* CreateMachineListNode(Machine* newMachine) 
{
    MachineList* newList = (MachineList*)calloc(1, sizeof(MachineList));

    newList->machine.id = newMachine->id;
    newList->machine.time = newMachine->time;
    newList->nextMachines = NULL;

    return newList;
}

/**
 * Insere uma máquina
 * @param [in] machinesHeader
 * @param [in] newMachine
 * @param [out] machinesHeader	//Retorna o header da lista de máquinas com a nova máquina inserida
*/
MachineList* InsertMachinesList(MachineList* machinesHeader, Machine* newMachine)
{
    MachineList* newMachineCreated = CreateMachineListNode(newMachine);

    if (machinesHeader == NULL) 
    {
        machinesHeader = newMachineCreated;
    }
    else {
        MachineList* auxMachines = machinesHeader;
        MachineList* auxAnt = NULL;
        while (auxMachines && auxMachines->machine.id < newMachineCreated->machine.id) 
        {
            auxAnt = auxMachines;
            auxMachines = auxMachines->nextMachines;
        }
        if (auxAnt == NULL) {
            newMachineCreated->nextMachines = machinesHeader;
            machinesHeader = newMachineCreated;
        }
        else 
        {
            auxAnt->nextMachines = newMachineCreated;
            newMachineCreated->nextMachines = auxMachines;
        }
    }

    return machinesHeader;
}

/**
 * Procura a máquina pretendida
 * @param [in] machinesHeader
 * @param [in] id
 * @param [out] newMachine	//Retorna a cópia de uma nova máquina que estava a procura
*/
Machine* MachineSearch(MachineList* machinesHeader, int id) 
{
    if (machinesHeader == NULL) return NULL; //Lista vazia

    MachineList* auxMachines = machinesHeader;
    while (auxMachines != NULL) 
    {
        if (auxMachines->machine.id == id) 
        {
            Machine* newMachine = CreateMachine(auxMachines->machine.id, auxMachines->machine.time);
            return newMachine;
        }
        auxMachines = auxMachines->nextMachines;
    }

    return NULL;
}

/**
 * Tempo mínimo de cada máquina em cada operação
 * @param [in] machinesHeader
 * @param [out] MinTime	//Retorna o tempo mínimo
*/
int MinMachineTime(MachineList* machinesHeader) 
{
    if (machinesHeader == NULL) return -1; //Lista vazia

    MachineList* auxMachines = machinesHeader;
    int MinTime = 100;
    while (auxMachines != NULL) 
    {
        if (auxMachines->machine.time < MinTime) 
        {
            MinTime = auxMachines->machine.time;
        }
        auxMachines = auxMachines->nextMachines;
    }

    return MinTime;
}

/**
 * Tempo maximo de cada máquina em cada operação
 * @param [in] machinesHeader
 * @param [out] MaxTime	//Retorna o tempo maximo
*/
int MaxMachineTime(MachineList* machinesHeader)
{
    if (machinesHeader == NULL) return -1; //Lista vazia
    int id = 0;

    MachineList* auxMachines = machinesHeader;
    int MaxTime = 0;
    while (auxMachines != NULL)
    {
        if (auxMachines->machine.time > MaxTime) 
        {
            MaxTime = auxMachines->machine.time;
            id = auxMachines->machine.id;
        }
        auxMachines = auxMachines->nextMachines;
    }

    return MaxTime;
}

/**
 * Mostra todas as máquinas
 * @param [in] machinesHeader
*/
void ShowMachineList(MachineList* machinesHeader)
{
    setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)
    MachineList* auxMachines = machinesHeader;
    printf("Máquinas:\n");
    while (auxMachines != NULL) 
    {
        printf("ID: %d - Tempo: %d\n", auxMachines->machine.id, auxMachines->machine.time);
        auxMachines = auxMachines->nextMachines;
    }
}

#pragma endregion