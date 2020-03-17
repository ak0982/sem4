#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>



char** execFunction(char *input,char **argv,int *sizeOfArray);
void garbageCollector(char** argv,int size);

 
#define CUTTING_WORD " \n"

void printDir() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\n%s >!", cwd); 
}

int main() 
{  

	char cwd[1024];
	pid_t id; 
	char str1[100]="";
	char **ns; 
	int i,j,ctr;
	int sizeOfArray=0;
	printDir();
	while (strcmp(str1,"exit") != 0) { 

//		printDir(); 

		fgets(str1, sizeof str1, stdin);	
	//	printf(" %s \n",str1);

		ns=execFunction(str1,ns,&sizeOfArray);
		if(strcmp("cd",ns[0])==0)
		{
		//	printf("inside cd\n");
			struct passwd *pwd;
			char *path=ns[1];
			if(path == NULL)
			{
				pwd=getpwuid(getuid());
				path=pwd->pw_dir;


			}

			if(path[0] == '/')
				(path)=++(path);
			errno=chdir(path);
			printDir();
			if(errno!=0)
				printf("error in changing dircatory");

		}
		else
		{
			id=fork();
			if (id<0)
			{
				printf("fork faild");
				exit(0);
			}
			else if(id==0) {
				execvp(ns[0],ns);
				garbageCollector(ns,sizeOfArray);	
				if(strcmp(str1,"exit") !=0)
					printf("command not found\n");
				exit(1);
			}
			else
			{wait(&id);
				if(strcmp(str1,"exit") !=0)
				{
					printDir();
				}
				else
				{
					printf("exit");
				}
			}
		}



	} 
	return 0; 
}

void garbageCollector(char** argv,int size)
{
	int i=0;
	for (i = 0; i < size; ++i) {
		free(argv[i]);
	}
	free(argv);
	argv=NULL;
}



char** execFunction(char *input,char **argv,int *sizeOfArray)
{
	int i=0,counter=0;
	char inputCopy[200];
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
		exit(0);
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
			exit(0);
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








