#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>



#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64 
#define CUTTING_WORD " \n"
char **tokenize(char *line);
void print() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\n%s$#@!", cwd); 
}

int main() 
{  

	
	pid_t id; 
	char str1[1024]="";
	char **ns; 
	int i,j,ctr;
	int sizeOfArray=0;
	print();
	while (strcmp(str1,"exit\n") != 0) {
	scanf("%[^\n]", str1);
//fgets(str1,1024,stdin);

		getchar();
		str1[strlen(str1)]='\n';
		ns=tokenize(str1);	
		if(strcmp("exit\n",ns[0]) == 0)
		{
	
		 for(i=0;ns[i]!=NULL;i++){
                                free(ns[i]);
		//		break;
                                }
                                free(ns);
			exit(0);
		}

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
			print();
			if(errno!=0)
				printf("error in changing dircatory");
                        for(i=0;ns[i]!=NULL;i++){
                                free(ns[i]);
                                }
                                free(ns);

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
				for(i=0;ns[i]!=NULL;i++){
				free(ns[i]);
				}
				free(ns);

	
				if(strcmp(str1,"exit\n") !=0)
				{	printf("command not found\n");
				
				//	printf("%s ",str1);
				}exit(1);
			}
			else
			{wait(&id);
				if(strcmp(str1,"exit\n") !=0)
				{
					print();
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


char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

