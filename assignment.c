//Linumiz assignment:Implement  pushd and  popd linux commands in c program.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define stack_size 100
#define path 4096
char *directory_stack[stack_size];
int top=-1;
void pushd(const char *dir)
{
	        if(top >= stack_size -1)
		{
			printf("stack full\n");
		        fprintf(stderr,"stack overflow\n");
		        return;
	        }
	        char *cur_dir=malloc(path);
	        if(cur_dir ==NULL)//checking the wheather the memory is allocated or not.
	         {  
	       		 perror("ERROR: memory allocation failed");
			 return;
		 }
		if(getcwd(cur_dir,path)==NULL)//get the current working directory, this function returns pointer on success and failure it returns NULL.
		{
		       	perror("getcwd fails");
			free(cur_dir);
		         return;
	       } 
		if(chdir(dir)!=0)//on success it returns 0 and on failure it return -1
	        {
			perror("chdir fails");
			free(cur_dir);
			return; 
		}		                                                                                                                                             
	       	directory_stack[++top]=cur_dir;                
   		printf("current directory:%s\n",dir);      

}
void popd()
{
	        if(top<0)
	  	{
		 fprintf(stderr,"stack underflow\n");
	       	 return;
		}
		 char *dir=directory_stack[top--];
	         if(chdir(dir)!=0)
		 {
		       	 perror("chdir fails");
				 free(dir);
				 return;
	     	 }
		  printf("current directory:%s\n",dir);
		   free(dir);


}
int main(int argc,char *argv[])
{
       	if(argc < 2)
       {
	       fprintf(stderr,"not enough arguments for push fun\n");
	       exit(EXIT_FAILURE);
       }
        if(strcmp(argv[1],"pushd")==0)
       	{
	       	if(argc != 3)
		{
			fprintf(stderr,"argument insufficiency for push fun\n");
		       	exit(1);
		}
		 pushd(argv[2]);
	}
       	else if (strcmp(argv[1],"popd")==0)
	{
		if(argc !=2)
	       	{
		      	fprintf(stderr,"not enough argument for pop function");
		       exit(1);
		 }  popd();
         }
         else
         {
	    fprintf(stderr,"commonds are not valid for this program");
	    exit(1);
	}
           return 0;

}
