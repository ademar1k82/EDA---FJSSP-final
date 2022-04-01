/*
Descrição:           Ficheiro aplicativo - Programa principal
                     FJSSP - parte 1
Desenvolvedor(es):   Ademar Valente (23155)
e-mail: a23155@alunos.ipca.pt
github: ademar1k82
Última atualização:  01/04/2022
Criação:             25/03/2022
*/

#include "header.h"
#include<locale.h>

void main() {

#pragma region VariableCreation

    Job* jobsHeader = NULL;

    // Maquinas
    Machine* m1 = CreateMachine(1, 4);
    Machine* m2 = CreateMachine(3, 5);
      
    //Operações
    Operation* o1 = CreateOperation(1);
      
    o1->machines = InsertMachinesList(o1->machines, m1);
    o1->machines = InsertMachinesList(o1->machines, m2);
    
    //Jobs
    Job* j1 = CreateJob(1);
    Job* j2 = CreateJob(2);

    j1->operations = InsertOperationList(j1->operations, o1);
    
    jobsHeader = InsertJob(jobsHeader, j1);

    // bool ficheiro = saveBinary("Data.bin", jobsHeader);

    // jobsHeader = readBinary("Data.bin");

#pragma endregion

#pragma region Printfs
    setlocale(LC_ALL, "Portuguese"); // permitir caracteres especiais (portugueses)

    //Mostrar
    printf("\n\n--------Flexible Job Shop Problem--------\n\n");
    ShowJobsList(jobsHeader);
    printf("\n\n------Dados carregados com sucesso!------\n");
    

    //Funções
    //Alterar
    printf("\n\n--------Flexible Job Shop Problem--------\n\n");
    jobsHeader->operations = ChangeOperation(jobsHeader->operations, 1, 3, 15);
    ShowJobsList(jobsHeader, j1);
    printf("\n\n------Dados alterados com sucesso!-------\n\n");

    //Minimo
    printf("\n\n-----------------------------------------\n\n");
    printf("Tempo Mínimo: %d", MinOperationTime(jobsHeader->operations));
    printf("\n\n-----------------------------------------\n\n");

    //Maximo
    printf("\n\n-----------------------------------------\n\n");
    printf("Tempo Máximo: %d", MaxOperationTime(jobsHeader->operations));
    printf("\n\n-----------------------------------------\n\n");

    //Media
    printf("\n\n-----------------------------------------\n\n");
    printf("Tempo Médio: %.2f", AverageOperationTime(jobsHeader->operations));
    printf("\n\n-----------------------------------------\n\n");

    //Remover
    printf("\n\n--------Flexible Job Shop Problem--------\n\n");
    jobsHeader->operations = RemoveOperation(jobsHeader->operations, 1);
    ShowJobsList(jobsHeader);
    printf("\n\n-----Operação removida com sucesso!------\n\n");

#pragma endregion

}