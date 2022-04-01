/*
Descrição:           Declarações necessárias para aplicação
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
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS

/*
NOTAS:
    Job -> Várias Operações -> Várias Máquinas
    Cada Job tem:
        Uma ou mais operações.
    Cada Operação tem:
        Um id da operação;
        Uma ou mais máquinas.
    Cada Máquina tem:
        Um id da máquina;
        Um tempo que a máquina demora a efetuar uma operação.
*/

#ifndef HEADER
#define HEADER 1

#pragma region Structs

typedef struct Machine 
{
    int id;
    int time;
    struct Machine* nextMachine;
}Machine;

typedef struct MachineList 
{
    struct Machine machine;
    struct MachineList* nextMachines;
}MachineList;

extern MachineList* machinesHeader;

typedef struct Operation 
{
    int id;
    struct MachineList* machines;
    struct Operation* nextOperation;
}Operation;

typedef struct OperationList 
{
    struct Operation operation;
    struct OperationList* nextOperations;
}OperationList;

extern OperationList* operationsHeader;

typedef struct Job
{
    int id;
    struct OperationList* operations;
    struct Job* nextJob;
}Job;

extern Job* jobsHeader;

typedef struct JobFile 
{
    int id;
}JobFile;

#pragma endregion

#pragma region AssinaturaDeFuncoes

//Assinatura de funções data
bool saveBinary(char* nameFile, Job* headJob);
Job* readBinary(char* nameFile);

//Assinatura de funções job
Job* CreateJob(int id);
Job* InsertJob(Job* jobHeader, Job* newJob);
void ShowJobsList(Job* jobsHeader);

//Assinatura de funções machines
bool MachineCheck(MachineList* machinesHeader, int id);
Machine* CreateMachine(int id, int time);
MachineList* CreateMachineListNode(Machine* newMachine);
MachineList* InsertMachinesList(MachineList* machinesHeader, Machine* newMachine);
Machine* MachineSearch(MachineList* machineHeader, int id);
int MinMachineTime(MachineList* machineHeader);
int MaxMachineTime(MachineList* machineHeader);
void ShowMachineList(MachineList* machineHeader);

//Assinatura de funções operações
bool OperationCheck(OperationList* operationsHeader, int id);
Operation* CreateOperation(int id);
OperationList* CreateOperationListNode(Operation* newOperation);
OperationList* InsertOperationList(OperationList* operationsHeader, Operation* newOperation);
Operation* OperationSearch(OperationList* operationsHeader, int id);
OperationList* RemoveOperation(OperationList* operationsHeader, int id);
OperationList* ChangeOperation(OperationList* operationsHeader, int Operationid, int Machineid, int changeTime);
int MinOperationTime(OperationList* operationsHeader);
int MaxOperationTime(OperationList* operationsHeader);
int CountOperationMachines(OperationList* operationHeader);
float AverageOperationTime(OperationList* operationHeader);
void ShowOperationList(OperationList* operationsHeader);

#pragma endregion

#endif
