#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "gracenote.h"
#include <errno.h>
int main(int argc, char* argv[])
{
    int retour = 1;
    while(retour)
    {
    printf("### WELCOME TO OUR MUSIC VIDEO FINDER ###\n\n ## Here you will be able to find the original soundtrack of a video or  discover in which videos of our database you can find a track. ##\n\n # If you want to discover the music in one of your videos, type : discover.\nIf you want to dicover the OST of a video type in our database: movie.\nIf you would like to discover in which video(s) you can find a certain track, type : track #\n\n");
    char scan1[100] = "";
    char scan2[100];
    char cmd[256];
    int i,j;
    int point;
    int slash = 0;
    retour = 0;
    fgets(scan1,10,stdin);
    if ((strlen(scan1)>0) && scan1[strlen(scan1)-1]=='\n')
	{
		scan1[strlen(scan1)-1] = '\0';
	}
    if(strcmp(scan1, "discover")!=0&&strcmp(scan1, "movie")!=0&&strcmp(scan1,"track")!=0)
    {
        printf("Wrong parameter.");
        retour = 1;
    }
    if (strcmp(scan1,"discover") == 0)
    {
            
        printf("# Type the path to the video you would like us to analyse. #\n\n ");
        scanf("%s", &scan2);
        for (i=strlen(scan2);i>0;i--)
        {
            if (scan2[i] == '.')
            {
                point = i;
            }
            if (scan2[i] == '/')
            {
                slash = i;
                break;
            }
        }
        char* name = malloc((point-slash+1) * sizeof(char));
        for (i=0; i<(point-slash); i++)
        {
            name[i] = scan2[i+slash];
        }
        printf("%s",name);
        printf("\n%s\n", scan2);
        FILE* database2 = fopen("database.txt", "a+");
        if (database2 == NULL) {perror("Erreur : ");}
        else
        {
            fprintf(database2, "\n_%s\n", name);
            fclose(database2);
        }
        
        //fgets(scan2, 10, stdin);
        //if ((strlen(scan2)>0) && scan2[strlen(scan2)-1]=='\n')
        //{
        //    scan2[strlen(scan2)-1] = '\0';
        //}
        snprintf(cmd, 256, "/home/sayuko/ENSIIE/S4/BDM/GNSDK/samples/audio_recognizer/mp3split.sh %s", scan2);
        system(cmd);
        identification();
    }
    else if (strcmp(scan1,"movie") == 0)
    {
    	printf("# Type the name of the video you wish to find the OST. #\n\n");
    	fgets(scan2, 100, stdin);
    	if ((strlen(scan2)>0) && scan2[strlen(scan2)-1]=='\n')
    	{
    		scan2[strlen(scan2)-1] = '\0';
    	}
    	movieSearch(scan2);
    }
    else if (strcmp(scan1,"track") == 0)
    {
    	printf("# Type the name of the track you would like to search for. #\n\n ");
    	fgets(scan2, 100, stdin);
    	if ((strlen(scan2)>0) && scan2[strlen(scan2)-1]=='\n')
    	{
    		scan2[strlen(scan2)-1] = '\0';
    	}
    	trackSearch(scan2);
    }
    FILE* database = fopen("database.txt", "a+");
    fprintf(database, "\n");
    system("rm *.wav");
    
    }
    return 0;
}