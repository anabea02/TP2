#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <locale.h>

/*Trabalho realizado por: Ana Carvalho, nº23544
EIM 1ºano
Estrutura de dados avançadas*/

typedef struct Jobs
{
	int numJob;
	int numOp;
	int numMachine;
	int time;
	struct Jobs* next;
} job;

//Protótipos
void pressToContinue();
int menu();
void writeFile(job* new);
job* readFile();
int listOp(job* operations);
job* insertJob(job* operations, int nJob, int nOp, int nMachine, int t);
job* insertJobs(job* operations);
int removeAsk();
job* removeJob(job* operations, int removedOp);
/*Op* insertChanged(Op* operations, int changedOp);
job* changeOp(job* operations);
/*int getNextOpId(int oldOpId, Op* operations);
int getLowestOpId(Op* operations);*/

int main() {
	setlocale(LC_ALL, "Portuguese");
	int option = 0;
	job* operations = readFile(); //Leitura do ficheiro no inicio para recuperar as operações guardadas
	while (true) {
		system("cls");
		printf("Trabalho realizado por: Ana Carvalho, nº23544\n");
		printf("EIM 1ºano\nEstrutura de dados avançadas\n");
		printf("\t\t\t\t-------------MENU-------------\n\n");
		option = menu();
		int removedJob = 0;
		switch (option) {
		case 0:
			writeFile(operations);
			exit(EXIT_SUCCESS);
			break;
		case 1:
			system("cls");
			listOp(operations);
			pressToContinue();
			break;
		case 2:
			system("cls");
			printf("\t\t\t\t-------------INSERIR JOB-------------\n\n");
			operations = insertJobs(operations);
			pressToContinue();
			break;
		case 3:
			system("cls");
			printf("\t\t\t\t-------------REMOVER JOB-------------\n\n");
			listOp(operations);
			removedJob = removeAsk();
			operations = removeJob(operations, removedJob);
			pressToContinue();
			break;
		case 4:
			system("cls");
			printf("\t\t\t\t-------------INSERIR UMA NOVA OPERAÇÃO NUM JOB-------------\n\n");
			pressToContinue();
			break;
		case 5:
			system("cls");
			printf("\t\t\t\t-------------REMOÇÃO DE UMA OPERAÇÃO NUM JOB-------------\n\n");
			pressToContinue();
			break;
		case 6:
			system("cls");
			printf("\t\t\t\t-------------ALTERAÇÃO DE UMA OPERAÇÃO-------------\n\n");
			listOp(operations);
			//operations = changeOp(operations);
			pressToContinue();
			break;
		default:
			printf("Opção inválida\n");
			break;
		}

	}

}

void pressToContinue() {
	printf("\nPrima qualquer tecla para continuar.\n");
	getch();
}

int menu() {

	int option = 0;

	printf("1. Listar jobs\n");
	printf("2. Inserir um job\n");
	printf("3. Remoção de um job\n");
	printf("4. Inserir uma nova operação num job\n");
	printf("5. Remoção de uma operação num job\n");
	printf("6. Alteração de uma operação\n");
	printf("0. SAIR E GUARDAR\n\n");
	printf("Escolha uma opção: \n");

	scanf("%d", &option);

	return option;
}

void writeFile(job* new)
{
	FILE* infile;
	infile = fopen("jobs_data.txt", "w");

	for (; new != NULL; new = new->next) {

		fprintf(infile, "Job: %d Operação: %d  Máquina(s): %d  Tempo(respetivamente): %d\n", new->numJob, new->numOp, new->numMachine, new->time);
	}

	if (fprintf != 0)
		printf("Dados guardados com sucesso!\n");
	else
		printf("Erro a escrever para ficheiro!\n");

	fclose(infile);

}

job* readFile() { //Função para ler o ficheiro
	int numOp, numMachine, time, numJob;
	job* operations = NULL;
	FILE* outfile = fopen("jobs_data.txt", "r");

	if (outfile != NULL) {
		while (!feof(outfile)) { //Enquanto não chegar ao fim do ficheiro
			fscanf(outfile, "Job: %d Operação: %d  Máquina(s): %d  Tempo(respetivamente): %d\n", &numJob, &numOp, &numMachine, &time);
			operations = insertJob(operations, numJob, numOp, numMachine, time); //Cada vez que uma linha é lida, é inserida a respetiva operação lida à lista ligada
		}
	}
	else {
		printf("Ficheiro vazio\n");
	}
	fclose(outfile);
	return (operations);
}

int listOp(job* operations)
{
	job* list = operations;
	printf("|  Job  |  Operação  |  Máquina  |  Tempo  |\n");
	while (list != NULL) //Percorre os elementos da lista ligada
	{
		printf("|   %d   |      %d     |     %d     |    %d    |\n", list->numJob, list->numOp, list->numMachine, list->time);
		list = list->next;
	}
}


job* insertJob(job* operations,int nJob, int nOp, int nMachine, int t) {

	job* new = malloc(sizeof(job));

	if (new != NULL) {
		new->numJob = nJob;
		new->numOp = nOp;
		new->numMachine = nMachine;
		new->time = t;
		new->next = operations;
		return(new);

	}
	else return(operations);
}

int getnextOId(job* operations) { //Esta é usada para procurar o numero de operação maior, ou seja, a primeira operação, mas não necessariamente o primeiro elemnto da lista ligada

	int currentOpId = 1;

	for (int opId = 1; opId < 7; opId = opId++) {
		for (job* opLoop = operations; opLoop != NULL; opLoop = opLoop->next) { //Vai percorrer a lista ligada
			if (opId != opLoop->numOp) {
				currentOpId = opId;
			}

		}
	}

	return currentOpId;
}

job* insertJobs(job* operations) {

	int insNumMachine = 0, insTime = 0, insNumJob = 0, insNumOp = 0;
	char moreMachines = 0;

	printf("Inserir no job (1-8): \n");
	scanf("%d", &insNumJob);

	do {
		moreMachines = 0;

		printf("Inserir na operação (1-7): \n");
		scanf("%d", &insNumOp);
		printf("Inserir uma máquina(1-8): \n");
		scanf("%d", &insNumMachine);
		printf("Inserir o seu respetivo tempo: \n");
		scanf("%d", &insTime);

		operations = insertJob(operations, insNumJob, insNumOp, insNumMachine, insTime);

		printf("Deseja adicionar mais máquinas? [S/N]\n");
		scanf(" %c", &moreMachines);

	} while (moreMachines == 'S' || moreMachines == 's');

	return (operations);
}

job* insertOpJob(job* operations) {

	int insNumMachine = 0, insTime = 0, insNumJob = 0, insNumOp = 0;
	char moreMachines = 0;

	printf("Inserir no job (1-8): \n");
	scanf("%d", &insNumJob);

	do {
		moreMachines = 0;

		printf("Inserir na operação (1-7): \n");
		scanf("%d", &insNumOp);
		printf("Inserir uma máquina(1-8): \n");
		scanf("%d", &insNumMachine);
		printf("Inserir o seu respetivo tempo: \n");
		scanf("%d", &insTime);

		operations = insertJob(operations, insNumJob, insNumOp, insNumMachine, insTime);

		printf("Deseja adicionar mais máquinas? [S/N]\n");
		scanf(" %c", &moreMachines);

	} while (moreMachines == 'S' || moreMachines == 's');

	return (operations);
}

int removeAsk() {
	int removedJob = 0;

	printf("\nInsira o job que deseja remover: \n");
	scanf("%d", &removedJob);

	return removedJob;
}

job* removeJob(job* operations, int removedJob) {
	job* opPrevious;
	job* opCurrent = 0;
	opCurrent = operations;

	while (opCurrent != NULL) {
		opCurrent = operations;
		if (removedJob == operations->numJob) { //Remove a primeira ocurrência
			operations = opCurrent->next;
			free(opCurrent); //Vai liberar espaço onde essa operação está alocada

		}
		else { //Remove as seguintes ocurrências
			opPrevious = operations;
			opCurrent = opPrevious->next;

			while ((opCurrent != NULL) && (opCurrent->numJob != removedJob)) {
				opPrevious = opCurrent;
				opCurrent = opCurrent->next;
			}

			if (opCurrent != NULL) {
				opPrevious->next = opCurrent->next;
				free(opCurrent);

			}
		}
	}

	return(operations);
}



/*job* insertChanged(job* operations, int changedOp) { //Função de inserção mas sem a pergunta de inserir o número de operação
	int insNumMachine = 0, insTime = 0;
	char moreMachines = 0;

	do {
		moreMachines = 0;

		printf("Inserir uma máquina: \n");
		scanf("%d", &insNumMachine);
		printf("Inserir o seu respetivo tempo: \n");
		scanf("%d", &insTime);

		for (job* opLoop = operations; opLoop != NULL; opLoop = opLoop = opLoop->next) { //verifica se já tem a msm combinação na lista ligada
			if ((changedOp == opLoop->numOp) && (insNumMachine == opLoop->numMachine)) {
				printf("Essa combinação de operação, máquina e tempo já existe.\n");
				break;

			}
			else if ((changedOp != opLoop->numOp) && (insNumMachine != opLoop->numMachine)) {
				operations = insertOp(operations, changedOp, insNumMachine, insTime);
				break;
			}
		}

		printf("Deseja adicionar mais máquinas? [S/N]\n");
		scanf(" %c", &moreMachines);

	} while (moreMachines == 'S' || moreMachines == 's');

	return (operations);
}

job* changeOp(job* operations) { //Para a função de alterar apenas chamei a função de remover e a de inserir 

	int changedOp = 0;

	printf("\nInsira a operação que deseja alterar: \n");
	scanf("%d", &changedOp);

	operations = removeJob(operations, changedOp);
	operations = insertChanged(operations, changedOp);

	return (operations);

}*/

int getNextOpId(int oldOpId, job* operations) { //Esta função serve para ir buscar o número de operação seguinte
	int nextOpId = INT_MAX;

	for (; operations != NULL; operations = operations->next) { //Vai percorrer a lista ligada 

		if (operations->numOp > oldOpId && operations->numOp < nextOpId) { //Verifica qual é o número maior que o número de operação anterior e menor que o seguinte
			nextOpId = operations->numOp;
		}
	}

	if (nextOpId == INT_MAX) return -1;

	return nextOpId; //retorna o numero de operação seguinte
}

int getLowestOpId(job* operations) { //Esta é usada para procurar o numero de operação menor, ou seja, a primeira operação, mas não necessariamente o primeiro elemnto da lista ligada

	int minOpId = INT_MAX;

	while (operations != NULL) { //Vai percorrer a lista ligada
		if (minOpId >= operations->numOp) {
			minOpId = operations->numOp;

		}
		operations = operations->next;
	}
	return minOpId;
}

/*int verificarOpExistente(job* lista, int numJob, int numOp)
{
	int sim = 0;
	while (lista != NULL && sim != 1)
	{
		if (lista->nmrJob == numJob && lista->nmrOperacao == numOp)
		{
			sim = 1;
		}
		else lista = lista->seguinte;
	}
	return sim;
}
for (Op* opLoop = operations; opLoop != NULL; opLoop = opLoop = opLoop->next) { //Verifica se a mesma combinação já existe na lista ligada
	if ((currentOpId == opLoop->numOp) && (insNumMachine == opLoop->numMachine)) {
		printf("Essa combinação de operação, máquina e tempo já existe.\n");
		break;

	}
	else if ((currentOpId != opLoop->numOp) && (insNumMachine != opLoop->numMachine)) {
		operations = insertOp(operations, currentOpId, insNumMachine, insTime);
		break;
	}
}*/