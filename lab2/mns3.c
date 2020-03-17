#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>




#define MAXCOM 1000 
#define MAXLIST 100 

void printDir() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\n%s >>$", cwd); 
}

int main() 
{  

	char cwd[1024];
	pid_t id; 
	char str1[100];
	char ns[100][100]; 
	int i,j,ctr;

	while (1) { 

		printDir(); 

		fgets(str1, sizeof str1, stdin);	
		printf(" %s \n",str1);
		j=0; ctr=0;
		for(i=0;i<(strlen(str1));i++)
		{

			if(str1[i]==' '||str1[i]=='\0')
			{
				ns[ctr][j]='\0';
				ctr++;
				j=0;
			}
			else
			{
				ns[ctr][j]=str1[i];
				j++;
			}
		}
	//	ns[i]=NULL;
		printf(" this is ns %s \n",ns[0]);
		printf(" the diff is bw ls and ls %d",strcmp(ns[0],"ls"));
		if(strcmp("cd",ns[0])==0)
		{
		printf("inside cd\n");
			struct passwd *pwd;
			char *path=ns[1];
			if(path == NULL)
			{
				pwd=getpwuid(getuid());
				path=pwd->pw_dir;


			}

	//		if(path[0] == '/')
	//			(path)+(path);
			errno=chdir(path);
			printDir();
			if(errno!=0)
				printf("error changing dircatory");

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
				if(strcmp(ns[0],"exit") !=0)
					printf("command not found\n");
				exit(1);
			}
			else
			{wait(&id);
				if(strcmp(ns[0],"exit") !=0)
				{
					printDir();
				}
				else
				{
					printf("bye");
				}
			}
		}



	} 
	return 0; 
}
