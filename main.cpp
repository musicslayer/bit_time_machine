#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <time.h>
#include <process.h>
#include <share.h>

#include <iostream>

#define NUMBEROFSTATES 100
#define MAXFILESIZE 70000

FILE *fp;
char inputfile[100], outputfile[100], backupfile[100];
int t4, s=0, c1, c2, current, c;
char state[NUMBEROFSTATES][MAXFILESIZE];
int t=0;
int sizeofstate[NUMBEROFSTATES];
char ppp;

char i[10], j[10];

void updatedisplay (void);
void textread (char[1000]);

int main() {
    while(1) {
        std::cout << "\033[2J\033[H"; //_clrscr();
        t4=0;
        s=0;
        c1=0;
        c2=0;
        current=0;
        c=0;
        t=0;

        //memset(backupfile, '\0', 100);
        backupfile[0]='\0';

        while(1) {
            //Choosing input file
            printf("Choose a file to track.");
            scanf("%s",inputfile);
            //fp = fopen(inputfile,"rb");
            fp = _fdopen(_sopen(inputfile,_O_RDONLY ,_SH_DENYNO), "rb");
            //fp = _fdopen(_sopen(inputfile,_O_RDWR ,_SH_DENYNO), "rb");
            std::cout << "\033[2J\033[H"; // _clrscr();
            //printf("%i",fp);
            if (fp!=NULL) {
                fclose(fp);
                break;
            }
        }

        //Opening backup file or creating new backup file
        strcat(backupfile,inputfile);
        strcat(backupfile,".backup");

        //fp = fopen(backupfile,"rb");
        fp = _fdopen(_sopen(backupfile,_O_RDONLY ,_SH_DENYNO), "rb");
        //fp = _fdopen(_open(backupfile,_O_RDONLY ,_O_BINARY), "rb");

        //If the backup file exists
        if (fp!=NULL) {
            fseek(fp, 0, SEEK_SET); 
            for (c1=0;c1<NUMBEROFSTATES;c1++) {
                fscanf(fp,"%i",&sizeofstate[c1]);  
                fread(&state[c1][c2], 1, 1, fp);  
                for (c2=0;c2<sizeofstate[c1];c2++) {
                    fread(&state[c1][c2], 1, 1, fp);  
                }

                if (feof(fp)!=0) {
                    current=s-1;
                    break;
                }

                s++;
            }

            fclose(fp);
        }

        //If the backup file doesn't exist
        else {
            //textread ();
            textread (inputfile);
            s++;
        }

        //Choosing output file
        printf("Choose the output file.");
        scanf("%s",outputfile);

        //Main loop
        while (1) {
            //Display info
            updatedisplay();

            while(1) {
                c=time(NULL);
                while(time(NULL)-c<.1);
                textread (inputfile);
                if (s<NUMBEROFSTATES&&(memcmp(state[s],state[s-1],sizeofstate[s])!=0||sizeofstate[s]!=sizeofstate[s-1])) {
                    //printf("Automatically saved state.");
                    current=s;
                    s++;

                    //Display info
                    updatedisplay ();
                }

                if(_kbhit()) {
                    i[0]=_getch();
                    printf("%c",i[0]);
                    break;
                }
            }
        }

        if (i[0]=='s') {
            if (s<NUMBEROFSTATES) {
                //Save current input file state to first unused spot
                //textread ();
                textread (inputfile);

                //printf("Saved state.");
                current=s;
                s++;

            }
        }

        else if (i[0]=='r') {
            //Restore a saved state to the output file

            while(1) {
                updatedisplay ();
                printf("\nSelect a state to restore.");

                //Select state
                j[0]='\n';
                while(j[0]=='\n') {
                    fgets(j,10,stdin);
                }

                if (j[0]=='0') {
                    //current=0;
                    fp = fopen(outputfile,"wb");
                    //fp = _fdopen(_open(outputfile,_O_WRONLY ,_O_BINARY), "wb");
                    //fwrite(state[current],1,sizeofstate[current],fp);
                    fwrite(state[0],1,sizeofstate[0],fp);
                    fclose(fp);
                    //printf("Restored state.");
                    break;
                }
                else {
                    c1=atoi(j);
                    if (c1<s&&c1>0) {
                        //current=c1;
                        fp = fopen(outputfile,"wb");
                        //fp = _fdopen(_open(outputfile,_O_WRONLY ,_O_BINARY), "wb");
                        //fwrite(state[current],1,sizeofstate[current],fp);
                        fwrite(state[c1],1,sizeofstate[c1],fp);
                        fclose(fp);
                        //printf("Restored state.");
                        break;
                    }
                    else {
                        //printf("Invalid state.");
                    }
                }
            }
        }

        else if (i[0]=='b') {
            //Backup all used states to backup file
            fp = fopen(backupfile,"wb");
            //fp = _fdopen(_open(backupfile,_O_WRONLY ,_O_BINARY), "rb");
            for (c1=0;c1<s;c1++) {
                fprintf(fp,"%i\n",sizeofstate[c1]);  
                for (c2=0;c2<sizeofstate[c1];c2++) {
                    fwrite(&state[c1][c2],1,1,fp);
                }
            }
            fclose(fp);
        }

        else if (i[0]=='q') {
            break;
        }

        else if (i[0]=='z') {
            return 0;
        }

        else {
            //printf("Invalid command.");
        }
    }
}

void textread (char filename[1000] ) {
    //Write contents of file "filename" to the current state
    fp = _fdopen(_sopen(filename,_O_RDONLY ,_SH_DENYNO), "rb");
    fseek(fp, 0, SEEK_SET); 
    t4=0;

    while (t4<MAXFILESIZE) {
        fread(&ppp, 1, 1, fp); 
        if(feof(fp)!=0) {
            break;
        }
        state[s][t4]=ppp;
        t4++;
    }

    sizeofstate[s]=t4;
    fclose(fp);
}

void updatedisplay (void) {
    //Display info
    std::cout << "\033[2J\033[H"; // _clrscr();

    printf("Input file = %s\n",inputfile);
    printf("Output file = %s\n",outputfile);
    printf("Backup file = %s\n",backupfile);
    printf("0");

    for (c1=1;c1<s;c1++) {
        printf(" %i",c1);
    }
    for (c1=s;c1<NUMBEROFSTATES-1;c1++) {
        printf(" X");
    }
    printf("\nCurrent state = %i",current);

    //Ask user what they want to do
    printf("\nPress s to save state, r to restore state, b to backup states, q to reset, z to quit.");
}