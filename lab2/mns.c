#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<dirent.h> 



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
    char inputString[MAXCOM], *parsedArgs[MAXLIST]; 
    char* parsedArgsPiped[MAXLIST]; 
    int execFlag = 0; 
   
char cwd[1024];
 
	char str1[100];
    char newString[10][10]; 
    int i,j,ctr;

    while (1) { 
        
//        printDir(); 
//char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\n%s>>$", cwd);

		
	fgets(str1, sizeof str1, stdin);	
 
    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++)
    {

 if(str1[i]==' '||str1[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;
	 j=0;
}
        else
        {
            newString[ctr][j]=str1[i];
            j++;
        }
    }
//     for(i=0;i < ctr;i++)
  //      printf(" %s\n",newString[i]);
char *c;
c=newString[0];
//printf("%s \n",c);
printf("%d \n",strcmp("ls",c));
if(strcmp("ls",c) == 0)
{


DIR*p;

struct dirent *d;
p=opendir(cwd);
if(p==NULL)
  {
  perror("Cannot find directory");
  exit(-1);
  }
while(d=readdir(p))
{  printf("%s ",d->d_name);
}

}



	    } 
    return 0; 
}
