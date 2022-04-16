#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "structs.h"

#define elemDedic 4

typedef data_structure *Tdata_structure;
typedef head *Thead;

int add_last(void **arr, int *len, data_structure *data)
{
	int lungime_totala = 0 , contor = 0;
	while (*arr != NULL && contor < *len/elemDedic)
	{
		lungime_totala += (sizeof(head)+*(unsigned int *)(*arr+lungime_totala+sizeof(int)));
		contor++;
	}
	if (*arr == NULL) {
		*arr = malloc(sizeof(head) + data->header->len);
		memcpy((*arr) , &data->header->type , sizeof(int));
		memcpy((*arr+sizeof(int)) , &data->header->len , sizeof(int));
		memcpy(((*arr+sizeof(head))) , data->data , data->header->len);
	} else {
		*arr = realloc(*arr , lungime_totala+sizeof(head)+data->header->len);
		memcpy((*arr+lungime_totala) , &data->header->type , sizeof(int));
		memcpy((*arr+sizeof(int)+lungime_totala) , &data->header->len , sizeof(int));
		memcpy(((*arr+sizeof(head)+lungime_totala)) , data->data , data->header->len);
	}
	*len += 4;
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
	if (index < 0) return -1;
	if (index > *len) add_last(&(*arr) , &(*len) , data);
	if (index>=0 && index <*len) {

	int nr_dedicatii = *len/elemDedic , contort=0 , contort1=0;
	int lungime = 0 , lungime_totala = 0;
	void * aux;

	while (arr != NULL && contort1<nr_dedicatii)
	{
		lungime_totala += (sizeof(head)+*(unsigned int *)(*arr+lungime_totala+sizeof(int)));
		contort1++;
	}
	
	while (arr != NULL && contort<nr_dedicatii) {
			if (contort == index) {
				aux = malloc(lungime_totala-lungime);
				memcpy(aux , *arr+lungime , lungime_totala-lungime);
				break;
			}
			lungime += (sizeof(head)+*(unsigned int *)(arr+lungime+sizeof(int)));
			contort++;
		}

	*arr = realloc(*arr , lungime_totala+sizeof(head)+data->header->len);
	memcpy((*arr+lungime) , &data->header->type , sizeof(int));
	memcpy((*arr+sizeof(int)+lungime) , &data->header->len , sizeof(int));
	memcpy(((*arr+sizeof(head)+lungime)) , data->data , data->header->len);

	memcpy((*arr+lungime+sizeof(head)+data->header->len) , aux , lungime_totala - lungime);
	free(aux);
	*len += 4;
	return 0;
	}
}

void find(void *data_block, int len, int index) 
{
	int nr_dedicatii = len/elemDedic , contort=0;
	int lungime = 0;
	int tip;
	if (index < 0 || index > len) return;
	while (data_block != NULL && contort<nr_dedicatii) 
	{
		if (contort == index) {
			printf("Tipul %c\n" , *(unsigned char *)(data_block+lungime));
			tip = *(unsigned int *)(data_block+lungime) - 48;
			if (tip == 1) {
				char * dedicator = (char *)(data_block+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("%s pentru" , (char *)(data_block+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(data_block+sizeof(head)+sizeof(int8_t)+sizeof(int8_t)+lungime_dedicator+lungime));
				printf("%"PRId8"\n" , *((int8_t *)(data_block+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId8"\n" , *((int8_t *)(data_block+sizeof(head)+lungime_dedicator+lungime+sizeof(int8_t))));
				printf("\n");
			} else if (tip == 2){
				char * dedicator = (char *)(data_block+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("%s pentru" , (char *)(data_block+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(data_block+sizeof(head)+sizeof(int16_t)+sizeof(int32_t)+lungime_dedicator+lungime));
				printf("%"PRId16"\n" , *((int16_t *)(data_block+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId32"\n" , *((int32_t *)(data_block+sizeof(head)+lungime_dedicator+lungime+sizeof(int16_t))));
				printf("\n");
			} else if (tip == 3) {
				char * dedicator = (char *)(data_block+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("%s pentru" , (char *)(data_block+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(data_block+sizeof(head)+sizeof(int32_t)+sizeof(int32_t)+lungime_dedicator+lungime));
				printf("%"PRId32"\n" , *((int32_t *)(data_block+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId32"\n" , *((int32_t *)(data_block+sizeof(head)+lungime_dedicator+lungime+sizeof(int32_t))));
				printf("\n");
			}
			break;
		}
		lungime += (sizeof(head)+*(unsigned int *)(data_block+lungime+sizeof(int)));
		contort++;
	}
}

int delete_at(void **arr, int *len, int index)
{
	int nr_dedicatii = *len/elemDedic , contort=0 , contort1=0;
	int lungime = 0 , lungime_totala = 0 , lungime_de_elim;
	void * aux2;
	if (index < 0 || index > *len/elemDedic) return;
	while (*arr != NULL &&contort1<nr_dedicatii)
	{
		lungime_totala += (sizeof(head)+*(unsigned int *)(*arr+lungime_totala+sizeof(int)));
		contort1++;
	}
	
	while (*arr != NULL && contort<nr_dedicatii) 
	{
		if (index == nr_dedicatii-1) {
			if (contort == index) {
				*arr = realloc(*arr , lungime);
				*len -= 4;
				break;
			}
			lungime += (sizeof(head)+*(unsigned int *)(*arr+lungime+sizeof(int)));
			contort++;
		}
		if (index == 0) {
		lungime_de_elim = (sizeof(head)+*(unsigned int *)(*arr+sizeof(int)));
			if (contort == index) {
			aux2 = (*arr+lungime_de_elim);
			memcpy((*arr) , aux2 , lungime_totala - lungime_de_elim);
			*arr = realloc((*arr) , lungime_totala - lungime_de_elim);
			*len -= 4;
			break;
		}
		contort++;
		}
		if (index > 0 && index < nr_dedicatii-1){
			if (contort == index) {
			aux2 = (*arr+lungime+sizeof(head)+*(unsigned int *)(*arr+lungime+sizeof(int)));
			lungime_de_elim = sizeof(head)+*(unsigned int *)(*arr+lungime+sizeof(int));
			memcpy((*arr+lungime) , aux2 , lungime_totala - lungime - lungime_de_elim);
			*arr = realloc(*arr , lungime_totala - lungime_de_elim);
			*len -= 4;
			break;
		}
		lungime += (sizeof(head)+*(unsigned int *)(*arr+lungime+sizeof(int)));
		contort++;
		}
	}
	return 0;
}

void print(void *arr, int len) 
{
	void *helper = arr;
	int nr_dedicatii = len/elemDedic , contort=0;
	int lungime = 0;
	int tip = 0;
	if (helper != NULL) {
		while (contort<nr_dedicatii) {
			tip = *(unsigned int *)(arr+lungime) - 48;
			if (tip == 1) {
				char * dedicator = (char *)(arr+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("Tipul %c\n" , *(unsigned char *)(arr+lungime));
				printf("%s pentru" , (char *)(arr+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(arr+sizeof(head)+sizeof(int8_t)+sizeof(int8_t)+lungime_dedicator+lungime));
				printf("%"PRId8"\n" , *((int8_t *)(arr+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId8"\n" , *((int8_t *)(arr+sizeof(head)+lungime_dedicator+lungime+sizeof(int8_t))));
				printf("\n");
			} else if (tip == 2){
				char * dedicator = (char *)(arr+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("Tipul %c\n" , *(unsigned char *)(arr+lungime));
				printf("%s pentru" , (char *)(arr+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(arr+sizeof(head)+sizeof(int16_t)+sizeof(int32_t)+lungime_dedicator+lungime));
				printf("%"PRId16"\n" , *((int16_t *)(arr+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId32"\n" , *((int32_t *)(arr+sizeof(head)+lungime_dedicator+lungime+sizeof(int16_t))));
				printf("\n");
			} else if (tip == 3) {
				char * dedicator = (char *)(arr+sizeof(head)+lungime);
				int lungime_dedicator = strlen(dedicator)+1;
				printf("Tipul %c\n" , *(unsigned char *)(arr+lungime));
				printf("%s pentru" , (char *)(arr+sizeof(head)+lungime));
				printf(" %s\n" , (char *)(arr+sizeof(head)+sizeof(int32_t)+sizeof(int32_t)+lungime_dedicator+lungime));
				printf("%"PRId32"\n" , *((int32_t *)(arr+sizeof(head)+lungime_dedicator+lungime)));
				printf("%"PRId32"\n" , *((int32_t *)(arr+sizeof(head)+lungime_dedicator+lungime+sizeof(int32_t))));
				printf("\n");
			}
			lungime += (sizeof(head)+*(unsigned int *)(arr+lungime+sizeof(int)));
			contort++;
		}
	} else if (helper == NULL){
		printf("\n");
	}
}

int main() {
	// the vector of bytes u have to work with
	// good luck :) //
	void *arr = NULL;
	int len = 0 ;
	int caz = 0 , tip = -1 , suma1 = -1 , suma2 = -1 , index = -1;
	int8_t suma1_8 , suma2_8;
	int16_t suma1_16 ;
	int32_t suma1_32 , suma2_32;
	char buffer [256];
	char *token , *comanda = NULL , *dedicator = NULL , *dedicatul = NULL;
	while(fgets(buffer , sizeof(buffer) , stdin) != NULL){
		token = strtok(buffer , " \n");
		caz = 0;
		comanda = NULL;
		tip = -1;
		suma1 = -1;
		suma2 = -1;
		index = -1;
		dedicator = NULL;
		dedicatul = NULL;
		while (token != NULL) {

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (comanda != NULL && caz == 1) {
				if ((strcmp(comanda , "insert") == 0) && tip != -1 && dedicator != NULL && suma1 != -1 && suma2 != -1 && dedicatul == NULL) {
					dedicatul = token;
					dedicatul[strlen(dedicatul)-1]='\0';
				}
				if ((strcmp(comanda , "insert") == 0) && tip != -1 && dedicator != NULL && suma1 != -1 && suma2 == -1) {
					suma2 = atoi(token);
					if (tip == 1) {
						suma2_8 = suma2;
					} else if (tip == 2){
						suma2_32 = suma2;
					} else if (tip == 3){
						suma2_32 = suma2;
					}
				}
				if ((strcmp(comanda , "insert") == 0) && tip != -1 && dedicator != NULL && suma1 == -1) {
					suma1 = atoi(token);
					if (tip == 1) {
						suma1_8 = suma1;
					} else if (tip == 2) {
						suma1_16 = suma1;
					} else if (tip == 3){
						suma1_32 = suma1;
					}
				}
				if ((strcmp(comanda , "insert") == 0) && tip != -1 && dedicator == NULL) {
					dedicator = token;
				}
				if ((strcmp(comanda , "insert") == 0) && tip == -1) {
					tip = atoi(token);
				}
			}
			if (strcmp(token , "insert") == 0) {
				comanda = token;
				caz = 1;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (comanda != NULL && caz == 2) {
				if ((strcmp(comanda , "insert_at") == 0) && index != -1 && tip != -1 && dedicator != NULL && suma1 != -1 && suma2 != -1 && dedicatul == NULL) {
				dedicatul = token;
				dedicatul[strlen(dedicatul)-1]='\0';
				}
				if ((strcmp(comanda , "insert_at") == 0) && index != -1 && tip != -1 && dedicator != NULL && suma1 != -1 && suma2 == -1) {
				suma2 = atoi(token);
					if (tip == 1) {
						suma2_8 = suma2;
					} else if (tip == 2){
						suma2_32 = suma2;
					} else if (tip == 3){
						suma1_32 = suma2;
					}
				}
				if ((strcmp(comanda , "insert_at") == 0) && index != -1 && tip != -1 && dedicator != NULL && suma1 == -1) {
				suma1 = atoi(token);
					if (tip == 1) {
						suma1_8 = suma1;
					} else if (tip == 2) {
						suma1_16 = suma1;
					} else if (tip == 3){
						suma1_32 = suma1;
					}
				}
				if ((strcmp(comanda , "insert_at") == 0) && index != -1 && tip != -1 && dedicator == NULL) {
				dedicator = token;
				}
				if ((strcmp(comanda , "insert_at") == 0) && index != -1 && tip == -1) {
				tip = atoi(token);
				}
				if ((strcmp(comanda , "insert_at") == 0) && index == -1) {
				index = atoi(token);
				}
			}
			if (strcmp(token , "insert_at") == 0) {
				comanda = token;
				caz = 2;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (comanda != NULL && caz == 3) {
				if (strcmp(comanda , "delete_at") == 0 && index ==-1) {
					index = atoi(token);
				}
			}
			if (strcmp(token , "delete_at") == 0) {
				comanda = token;
				caz = 3;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (comanda != NULL && caz == 4) {
				if (strcmp(comanda , "find") == 0 && index ==-1) {
					index = atoi(token);
				}
			}
			if (strcmp(token , "find") == 0) {
				comanda = token;
				caz = 4;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (strcmp(token , "print") == 0) {
				comanda = token;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------

			if (strcmp(token , "exit") == 0) {
				comanda = token;
				}

//-------------------------------------------------------------------------------------------------------------------------------------------


			token = strtok(NULL , " ");
		}

		if (strcmp(comanda , "insert") == 0) {
			int lungime_dedidcator = strlen(dedicator) , lungime_dedicat = strlen(dedicatul);
			Tdata_structure data_struct = (Tdata_structure)malloc(sizeof(data_structure));
			data_struct->header = malloc(sizeof(head));
		
			if (tip == 1) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int8_t)+sizeof(int8_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_8 , sizeof(int8_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int8_t) , &suma2_8 , sizeof(int8_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int8_t)+sizeof(int8_t) , dedicatul , lungime_dedicat+1);
			} else if (tip == 2) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int16_t)+sizeof(int32_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_16 , sizeof(int16_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int16_t) , &suma2_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int16_t)+sizeof(int32_t) , dedicatul , lungime_dedicat+1);
			} else if (tip == 3) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int32_t)+sizeof(int32_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int32_t) , &suma2_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int32_t)+sizeof(int32_t) , dedicatul , lungime_dedicat+1);
			}
			add_last(&arr , &len , data_struct);
			free(data_struct->header);
			free(data_struct->data);
			free(data_struct);
			}
		if (strcmp(comanda , "insert_at") == 0) {
			int lungime_dedidcator = strlen(dedicator) , lungime_dedicat = strlen(dedicatul);
			Tdata_structure data_struct = (Tdata_structure)malloc(sizeof(data_structure));
			data_struct->header = malloc(sizeof(head));
		
			if (tip == 1) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int8_t)+sizeof(int8_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_8 , sizeof(int8_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int8_t) , &suma2_8 , sizeof(int8_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int8_t)+sizeof(int8_t) , dedicatul , lungime_dedicat+1);
			} else if (tip == 2) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int16_t)+sizeof(int32_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_16 , sizeof(int16_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int16_t) , &suma2_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int16_t)+sizeof(int32_t) , dedicatul , lungime_dedicat+1);
			} else if (tip == 3) {
				data_struct->header->type = tip+48;
				data_struct->header->len = (lungime_dedidcator+1)+sizeof(int32_t)+sizeof(int32_t)+(lungime_dedicat+1);
				data_struct->data = malloc(data_struct->header->len);
				memcpy(data_struct->data , dedicator , lungime_dedidcator+1);
				memcpy(data_struct->data+lungime_dedidcator+1 , &suma1_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int32_t) , &suma2_32 , sizeof(int32_t));
				memcpy(data_struct->data+lungime_dedidcator+1+sizeof(int32_t)+sizeof(int32_t) , dedicatul , lungime_dedicat+1);
			}
			add_at(&arr , &len , data_struct , index);
			free(data_struct->header);
			free(data_struct->data);
			free(data_struct);
			}
		if (strcmp(comanda , "delete_at") == 0) {
			delete_at(&arr , &len , index);
			}
		if (strcmp(comanda , "find") == 0) {
			find(arr , len , index);
			}
		if (strcmp(comanda , "print") == 0) {
			print(arr , len);
			}
		if (strcmp(comanda , "exit") == 0) {
			free(arr);
			break;
			}
		}
	return 0;
}
