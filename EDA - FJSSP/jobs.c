/*
Descrição:           Ficheiro com funções relativas aos trabalhos
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
#include"header.h"

#pragma region jobs

/**
 * Cria um job
 * @param [in] id
 * @param [in] operations
 * @param [out] newJob	//Retorna o job aqui criado
*/
Job* CreateJob(int id) {
    Job* newJob = (Job*)malloc(sizeof(Job));
    if (newJob == NULL) return NULL; // Se não há memória

    newJob->id = id;
    newJob->operations = NULL;
    newJob->nextJob = NULL;

    return newJob;
}

/**
 * Insere um job
 * @param [in] jobsHeader
 * @param [in] newJob
 * @param [out] jobsHeader	//Retorna o header job
*/
Job* InsertJob(Job* jobsHeader, Job* newJob) {
    if (jobsHeader == NULL) {
        jobsHeader = newJob;
    }
    else {
        Job* auxJobs = jobsHeader;
        Job* auxAnt = NULL;
        while (auxJobs && auxJobs->id < newJob->id) {
            auxAnt = auxJobs;
            auxJobs = auxJobs->nextJob;
        }
        if (auxAnt == NULL) {
            newJob->nextJob = jobsHeader;
            jobsHeader = newJob;
        }
        else {
            auxAnt->nextJob = newJob;
            newJob->nextJob = auxJobs;
        }
    }

    return jobsHeader;
}

/**
 * Mostra a lista de jobs e operações e máquinas
 * @param [in] jobsHeader
*/
void ShowJobsList(Job* jobsHeader) {
    Job* auxJobs = jobsHeader;
    printf("Jobs:\n");
    while (auxJobs != NULL) {
        printf("ID: %d\n", auxJobs->id);
        ShowOperationList(jobsHeader->operations);
        auxJobs = auxJobs->nextJob;
    }
}

#pragma endregion