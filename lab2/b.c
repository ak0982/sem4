#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>

#define INPUT_SIZE 510 
#define CUTTING_WORD " \n"
#define ENDING_WORD "exit"
#define RESET 0



void  DisplayPrompt();
char** execFunction(char *input,char **argv,int *sizeOfArray); 
void garbageCollector(char** argv,int size);


int main() {
  
    int sizeOfArray=RESET;

    char input[INPUT_SIZE]="";
    DisplayPrompt();
    pid_t id; 
    char **argv;
    while (strcmp(input,ENDING_WORD)!=RESET)
    {
        if(fgets(input,INPUT_SIZE,stdin)==RESET)
            printf(" ");       

        argv=execFunction(input,argv,&sizeOfArray);

        if (strcmp("cd",argv[RESET])==RESET)
        {
            struct passwd *pwd;
            char* path=argv[1];

            if(path==NULL)
            {
                pwd=getpwuid(getuid());
                path=pwd->pw_dir;
            }
            if(path[0]=='/')
    //            (path)+(path);
            errno=chdir(path);
            DisplayPrompt();
            if(errno!=RESET)
                printf("error changing dircatory");

        }

        else
        {
            id=fork();
            if (id<RESET)
            {
                printf("fork faild");
                exit(RESET);
            }
            else if(id==RESET) {
                execvp(argv[RESET],argv);
                garbageCollector(argv,sizeOfArray);
                if(strcmp(input,ENDING_WORD)!=RESET)
	printf("command not found\n");
                    exit(1);
            }else {
                wait(&id);
                if (strcmp(input,ENDING_WORD) != RESET)
                {
                    DisplayPrompt();
                }                else {
                    printf("Bye !\n");
                }
            }

        }
    }
    return RESET;
}
void garbageCollector(char** argv,int size)
{
    int i=RESET;
    for (i = RESET; i < size; ++i) {
        free(argv[i]);
    }
    free(argv);
    argv=NULL;
}
char** execFunction(char *input,char **argv,int *sizeOfArray)
{
    int i=RESET,counter=RESET;
    char inputCopy[INPUT_SIZE];
    strcpy(inputCopy,input);

    char* ptr= strtok(input,CUTTING_WORD);
    while(ptr!=NULL)
    {
        ptr=strtok(NULL,CUTTING_WORD);
        counter++;
    }
    argv = (char**)malloc((counter+1)*(sizeof(char*)));
    if(argv==NULL)
    {
        printf("error allocated");
        exit(RESET);
    }
	int j;
    char* ptrCopy= strtok(inputCopy,CUTTING_WORD);
    while(ptrCopy!=NULL)
    {
      argv[i]=(char*)malloc((sizeof(char)+1)*strlen(ptrCopy));
        if(argv[i]==NULL)
        {
            printf("error allocated");
            for ( j = i-1; j >-1 ; j--) {
                free(argv[j]);
            }
            free(argv);
            exit(RESET);
        }
        strcpy(argv[i],ptrCopy);
        argv[i][strlen(ptrCopy)]='\0';
        ptrCopy=strtok(NULL,CUTTING_WORD );
        i++;
    }
    argv[counter]=NULL;
    (*sizeOfArray)=counter;
    return argv;

}

void DisplayPrompt()
{


    long size;
    char *buf;
    char *ptr;

    size = pathconf(".", _PC_PATH_MAX);

    if ((buf = (char *)malloc((size_t)size)) != NULL)
        ptr = getcwd(buf, (size_t)size);
    struct passwd *getpwuid(uid_t uid);
    struct passwd *p;
    uid_t uid=0;
    if ((p = getpwuid(uid)) == NULL)
        perror("getpwuid() error");
    else {
        printf("%s@%s>", p->pw_name, ptr);
    }
    free(buf);
}
