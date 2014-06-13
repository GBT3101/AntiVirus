#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus virus;

int virusesCounter=0;

struct virus {
        int length;
        char *signature;
        char *name;
        virus *next;
};

void detect_virus(char *buffer, virus *virus_list, unsigned int size){
	int ret;
	int i;
	while(virus_list != NULL){
		for(i=0; i<size; i++){
			ret = memcmp(virus_list->signature, &buffer[i], virus_list->length);
			if(ret==0){
				printf("Virus detected: %s \n", virus_list->name);
				printf("Location in suspectedFile: %i \n", i);
				printf("Virus size: %i \n", virus_list->length);
			}
		}
		virus_list = virus_list->next;
	}

}

void printHex(char* buffer, int i){
	printf("%02hhX ", buffer[i]);
}

void list_print(virus *virus_list){
	int i;
	while(virus_list != NULL){
			printf("Virus Name: %s \n", virus_list->name);
			printf("Virus Size: %i \n", virus_list->length);
			printf("Virus Signature: \n");
			fflush(stdout);
			for(i=0; i<virus_list->length; i++){
				printHex(virus_list->signature, i);
			}
			printf("\n");
			virus_list = virus_list->next;
		}
}

virus *list_append(virus *virus_list, virus data){
	virusesCounter++;
	virus *first = virus_list;
	virus *newVirus = malloc(sizeof(virus));
		newVirus->name = data.name;
		newVirus->length = data.length;
		newVirus->signature = data.signature;
		newVirus->next = NULL;
	if(virus_list == NULL){
		return newVirus;
	} else {
		while(virus_list->next !=NULL){
			virus_list = virus_list->next;
		}
		virus_list->next = newVirus;
	}
	return first;
}

void list_free(virus *virus_list){
	virus *passVirus;
	while(virus_list->next!=NULL){
		passVirus=virus_list;
		virus_list = virus_list->next;
		free(passVirus->name);
		free(passVirus->signature);
		free(passVirus);
	}
}

int main(int argc, char **argv){
	int i;
	virus *firstVirus;
	virus currentVirus;
	int counter;
	int flag=0;
	int j;
	int signatureLength;
	char buffer[1024];
	char signature[1024];
	char virusName[255];
	char * temp;
	char fullSuspectedFile[10000];
	int suspectSize;
	FILE *fp = fopen("signatures","r");
	FILE *suspected = fopen("suspect","r");

		while(fread(buffer,1,1,fp)!=0){
			signatureLength = buffer[0];
			fread(signature,1,signatureLength,fp);
			j=0;
			while(buffer[0] != 0){
				fread(buffer,1,1,fp);
				virusName[j]=buffer[0];
				j++;
			}
			virusName[j]='\0';

			temp = (char*)malloc(strlen(virusName) * sizeof(char));
			for(i=0; i<strlen(virusName); i++){
				temp[i] = virusName[i];
			}
			currentVirus.name = temp;
			currentVirus.length = signatureLength;

			temp = (char*)malloc(signatureLength * sizeof(char));
			for(i=0; i<signatureLength; i++){
				temp[i] = signature[i];
			}

			currentVirus.signature = temp;
			firstVirus = list_append(firstVirus,currentVirus);

			//printHex(buffer,1);
		}

		fread(fullSuspectedFile, 10000, 1, suspected);
		suspectSize = ftell(suspected);
		printf("%s \n", firstVirus->name);
		fflush(stdout);
		detect_virus(fullSuspectedFile, firstVirus, suspectSize);






		//list_print(firstVirus);
		list_free(firstVirus);
		//printf("\n");
	
	
}