#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include <sys/types.h>
#include <sys/stat.h>
int taille(char* mot)
{
	int i =0;
	while(mot[i] != '\0')
	{
		i++;
	}
	return i;
}

void movieSearch(char* search)
{
	char car;
	char buffer[100] = "";
	printf("# Searching the OST of '%s'... #\n\n", search);
	FILE* fichier = fopen("database.txt", "r+");
	if (fichier)
	{
		if (fgetc(fichier) != '_')
		{
			fseek(fichier, -1, SEEK_CUR);
		}
		fgets(buffer, 100, fichier);
		while(buffer != NULL)
		{
			buffer[taille(buffer)-1] = '\0';
			if(strcmp(buffer, search) == 0)
			{
				fseek(fichier, -(taille(buffer)+3), SEEK_CUR);
				if (fgetc(fichier) == '\n')
				{
					fseek(fichier, taille(buffer)+1, SEEK_CUR);
					while(fgetc(fichier) != EOF)
					{
						fseek(fichier, -1, SEEK_CUR);
						if ((fgetc(fichier) == '\n' && car == '\n') || car == EOF)
						{
							return;
						}
						fseek(fichier, -1, SEEK_CUR);
						car = fgetc(fichier);
						printf("%c", car);
					}
					return;
				}
				else
				{
					fseek(fichier, taille(buffer)+3, SEEK_CUR);
				}
			}
			if (fgetc(fichier) != '_')
			{
				fseek(fichier, -1, SEEK_CUR);
			}
			fgets(buffer, 100, fichier);
		}
		fclose(fichier);
		printf("TITRE NON TROUVE\n");
	}
}

void trackSearch(char* search)
{
	int curseur = 0;
	char buffer[100] = "";
	printf("Searching '%s' in our movie database...\n\n", search);
	FILE* fichier = fopen("database.txt", "r+");
	if (fichier)
	{
		while(fgets(buffer, 100, fichier) != NULL)
		{
			buffer[taille(buffer)-1] = '\0';
			if(strcmp(buffer, search) == 0)
			{
				curseur = ftell(fichier);
				while(fgetc(fichier)!= '_')
				{
					fseek(fichier, -2, SEEK_CUR);
				}
				fgets(buffer, 100, fichier);
				printf("%s\n", buffer);
				fseek(fichier, curseur-1, SEEK_SET);
			}
		}
	}
	printf("End of search\n");
}

int file_exist (char *filename)
{
  struct stat  buffer;   
  return (stat (filename, &buffer) == 0);
}