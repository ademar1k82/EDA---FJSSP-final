/*
Descri��o:           Ficheiro com a fun��o de carregar dados
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
#include"header.h"

bool saveBinary(char* nameFile, Job* headJob) {
	if (headJob == NULL) return false;
	FILE* fp;
	if ((fp = fopen(nameFile, "wb")) == NULL) return false;

	Job* auxJob = headJob;
	JobFile auxFileJob;

	while (auxJob != NULL) {
		auxFileJob.id = auxJob->id;
		fwrite(&auxFileJob, sizeof(JobFile), 1, fp);
		auxJob = auxJob->nextJob;
	}
	fclose(fp);

	return true;
}

Job* readBinary(char* nameFile) {
	FILE* fp;
	Job* headJob = NULL;
	Job* auxJob;

	if ((fp = fopen(nameFile, "rb")) == NULL) return NULL;
	JobFile auxFileJob;
	while (fread(&auxFileJob, sizeof(Job), 1, fp)) {
		auxJob = CreateJob(auxFileJob.id);
		headJob = InsertJob(headJob, auxJob);
	}
	fclose(fp);

	return headJob;
}