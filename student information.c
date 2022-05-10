#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define Student struct Stud

void add(FILE * fp);
FILE * del(FILE * fp);
void displayList(FILE * fp);
void searchRecord(FILE *fp);
void printChar(char ch,int n);
void printHead();

struct Stud
{
    char name[100];
    char branch[50];
    int roll;
    float sgpa[8];
    float cgpa;
};


int main()
{
 FILE * fp;
 Student s;
int option;
char another;

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    if((fp=fopen("studentInfo.txt","wb+"))==NULL)
       {
           printf("can't open file");
           return 0;
       }
}

while(1)
{
    printHead();
    printf("\n\t");
    printChar('-',64);

    printf("\n\n\t\t\t1. ADD Student");
    printf("\n\n\t\t\t2. DELETE Student");
    printf("\n\n\t\t\t3. DISPLAY Student LIST");
    printf("\n\n\t\t\t4. Search Record");
    printf("\n\n\t\t\t0. EXIT");

    printf("\n\n\t\tEnter Your Option : ");
    scanf("%d",&option);

    switch(option)
    {
        case 0: return 1;
                break;
        case 1: add(fp);
                break;
        case 2: fp=del(fp);
                break;
        case 3: displayList(fp);
                break;
        case 4: searchRecord(fp);
                break;
        default: printf("\n\t\tYou Pressed wrong key");
                  printf("\n\t\tProgram terminated");
                  getch();
                  exit(0);

    }
}
return 1;

}

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void printHead()
{ system("cls");

printf("\n\n\t");
printChar('=',16);
printf("[STUDENT] [INFORMATION] [SYSTEM]");
printChar('=',16);
printf("\n");
}

void add(FILE * fp)
{
printHead();

char a='y';
Student s;
int i;
float cgpa;

fseek(fp,0,SEEK_END);
while(a=='y')
{

    printf("\n\n\t\tEnter Full Name of Student\t");
    fflush(stdin);
    fgets(s.name,100,stdin);
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Branch\t");
    fflush(stdin);
    fgets(s.branch,50,stdin);
    s.branch[strlen(s.branch)-1]='\0';

    printf("\n\n\t\tEnter Roll number \t");
    scanf("%d",&s.roll);

    printf("\n\n\tEnter SGPA for 3 semesters\n\t");
    for(i=0,cgpa=0;i<3;i++)
    {scanf("%f",&s.sgpa[i]);
    cgpa+=s.sgpa[i];

    }

    cgpa/=3.0;
    s.cgpa=cgpa;

    fwrite(&s,sizeof(s),1,fp);

    printf("\n\n\t\tWant to enter another student info (Y/N)\t");
    fflush(stdin);
    a=getchar();
}
}

FILE * del(FILE * fp)
{
 printHead();

Student s;
int flag=0,tempRoll,siz=sizeof(s);
FILE *ft;

if((ft=fopen("temp.txt","wb+"))==NULL)
{
    printf("\n\n\t\t\t\\t!!! ERROR !!!\n\t\t");
    system("pause");
     return fp;
}

printf("\n\n\tEnter Roll number of Student to Delete the Record");
printf("\n\n\t\t\tRoll No. : ");
scanf("%d",&tempRoll);

rewind(fp);


while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
    { flag=1;
    printf("\n\tRecord Deleted for");
    printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.branch,s.roll);
    continue;
    }

    fwrite(&s,siz,1,ft);
}


fclose(fp);
fclose(ft);

remove("studentInfo.txt");
rename("temp.txt","studentInfo.txt");

if((fp=fopen("studentInfo.txt","rb+"))==NULL)
{
    printf("ERROR");
    return  NULL;
}

if(flag==0) printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");

printChar('-',65);
printf("\n\t");
system("pause");
return fp;
}

void displayList(FILE * fp)
{   printHead();
    Student s;
    int i,siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tBRANCH : %s",s.branch);
        printf("\n\n\t\tROLL : %d",s.roll);
        printf("\n\n\tSGPA: ");

        for(i=0;i<3;i++)
            printf("| %.2f |",s.sgpa[i]);
        printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
        printChar('-',65);
    }
    printf("\n\n\n\t");
     printChar('*',65);
    printf("\n\n\t");
    system("pause");
}

void searchRecord(FILE *fp)
{printHead();

int tempRoll,flag,siz,i;
Student s;
char a='y';

siz=sizeof(s);

while(a=='y')
{
printf("\n\n\tEnter Roll Number of Student to search the record : ");
scanf("%d",&tempRoll);

rewind(fp);

while((fread(&s,siz,1,fp))==1)
{
    if(s.roll==tempRoll)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tBRANCH : %s",s.branch);
        printf("\n\n\t\tROLL : %d",s.roll);
        printf("\n\n\tSGPA: ");

        for(i=0;i<3;i++)
            printf("| %.2f |",s.sgpa[i]);
        printf("\n\n\t\tCGPA : %.2f\n\t",s.cgpa);
        printChar('-',65);

}
else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");


printf("\n\n\t\tWant to enter another search (Y/N)");
fflush(stdin);
a=getchar();
}
}
