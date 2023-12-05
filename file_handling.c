#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct STUDENT
{
    int semester,ID;
    char name[50],branch[50],address[50];
};
typedef struct STUDENT student;

void empty_string(char string[])
{
   int i=0;
   while( i!=50 )
   { string[i++]='\0'; }
}

void insert_student()
{
    student S;
    FILE * fp = fopen("student.txt","a");
    if( fp==NULL )
    { printf("File can't opened!!"); return; }

    printf("Enter student's ID :  ");
    scanf("%d",&S.ID);
    printf("Enter student's name(ONLY IN UPPER CASES) :  ");
    scanf("%s",S.name);
    printf("Enter student's semester :  ");
    scanf("%d",&S.semester);
    printf("Enter student's branch :  ");
    scanf("%s",S.branch);
    printf("Enter student's address :  ");
    scanf("%s",S.address);

    fprintf(fp,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    fclose(fp);
}

void show_student_data()
{
    FILE *fp = fopen("student.txt","r");
    if( fp==NULL )
    { printf("File can't opened!!"); return; }

    printf("SID    Name    Semester     Branch    Address\n");
    while( !feof(fp) )
    {
        student S;
        fscanf(fp,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        printf("%d    %s         %d         %s         %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp);
}

void delete_student(int SID)
{
    FILE *fp2 = fopen("student.txt","r");
    FILE *fp1 = fopen("temp.txt","w");
    int flag=0; 

    while( !feof(fp2) )
    {
        student S;
        fscanf(fp2,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        if( S.ID==SID )
          { 
            flag = 1; 
            continue;  
          }
        fprintf(fp1,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp1);
    fclose(fp2);
    if( flag==0 )
    {
        printf("Student ID-%d not found in data !!\n Check data below\n",SID);
        return;
    }
    remove("student.txt");
    rename("temp.txt","student.txt");
}

void modify_student(int id)
{
    FILE *fp2 = fopen("student.txt","r");
    FILE *fp1 = fopen("temp.txt","w");
    int flag=0; 
    char new_address[50];

    while( !feof(fp2) )
    {
        student S;
        fscanf(fp2,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        if( S.ID==id )
          { 
            flag = 1; 
            printf("Enter new address :  ");  scanf("%s",new_address);
            empty_string(S.address);
            strcpy(S.address,new_address);
          }
        fprintf(fp1,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp1);
    fclose(fp2);
    if( flag==0 )
    {
        printf("Student ID-%d not found in data !!\n Check data below\n",id);
        return;
    }
    remove("student.txt");
    rename("temp.txt","student.txt");
}

void list_by_branch(char branch[])
{
    FILE *fp = fopen("student.txt","r");
    if( fp==NULL )
    { printf("File can't opened!!"); return; }

    printf("SID    Name    Semester     Branch    Address\n");
    while( !feof(fp) )
    {
        student S;
        fscanf(fp,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        if( strcmp(S.branch,branch)==0 )
            printf("%d    %s         %d         %s         %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp);
}

void list_by_branch_address(char branch[],char address[])
{
    FILE *fp = fopen("student.txt","r");
    if( fp==NULL )
    { printf("File can't opened!!"); return; }

    printf("SID    Name    Semester     Branch    Address\n");
    while( !feof(fp) )
    {
        student S;
        fscanf(fp,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        if( (strcmp(S.branch,branch)==0) && (strcmp(S.address,address)==0) )
            printf("%d    %s         %d         %s         %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp);
}

int search(char name[])
{
    FILE *fp = fopen("sorted.txt","r");
    int position=1;
    while( !feof(fp) )
    {
        student S;
        fscanf(fp,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        if( strcmp(name,S.name)<0 )
           { 
             fclose(fp); 
             return position; 
           }
        position++;
    }
    fclose(fp);
    return position;
}

void display_sort()
{
    FILE *fp = fopen("sorted.txt","r");
    if( fp==NULL )
    { printf("File can't opened!!"); return; }

    printf("SID    Name    Semester     Branch    Address\n");
    while( !feof(fp) )
    {
        student S;
        fscanf(fp,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        printf("%d    %s         %d         %s         %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    }
    fclose(fp);
}

void sort_by_names()
{
    FILE *fp1 = fopen("student.txt","r");
    FILE *fp2 = fopen("sorted.txt","w");
    int position,i;
    char ch;

    student S;
    fscanf(fp1,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
    fprintf(fp2,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
    fclose(fp2);

    while( !feof(fp1) )
    {
        student S;
        fscanf(fp1,"%d %s %d %s %s ",&S.ID,S.name,&S.semester,S.branch,S.address);
        position = search(S.name);
        i=1;
        FILE *fp2 = fopen("sorted.txt","r");
        FILE *fp3 = fopen("temp.txt","w");
        while( !feof(fp2) )
        {
            student stu;
            fscanf(fp2,"%d %s %d %s %s ",&stu.ID,stu.name,&stu.semester,stu.branch,stu.address);
            if( position==i )
                fprintf(fp3,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
            fprintf(fp3,"%d %s %d %s %s\n",stu.ID,stu.name,stu.semester,stu.branch,stu.address);  
            i++;
        }
        if( position==i )
           fprintf(fp3,"%d %s %d %s %s\n",S.ID,S.name,S.semester,S.branch,S.address);
        fclose(fp2);
        fclose(fp3);
        remove("sorted.txt");
        rename("temp.txt","sorted.txt");
    }
    fclose(fp1);
    display_sort();
}

void main()
{
    int choice,SID,semester;
    char name[50],branch[50],address[50];

    while(1)
    {
        printf("\n\n0.Exit\n");
        printf("1.Insert new student\n");
        printf("2.Show data base table\n");
        printf("3.Delete student\n");
        printf("4.Modify address\n");
        printf("5.List students of specific branch\n");
        printf("6.List students by branch and address\n");
        printf("7.Sort Names in alphabetical order\n");
        printf("Enter choice :  ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 0 : printf("Exiting out\n"); return;
            case 1 : insert_student(); break;
            case 2 : show_student_data(); break;
            case 3 : printf("Enter student SID to delete :  ");  scanf("%d",&SID);
                     delete_student(SID); break;
            case 4 : printf("Enter student SID to modify address : "); scanf("%d",&SID);
                     modify_student(SID); break;
            case 5 : printf("Enter specific branch :  "); empty_string(branch); scanf("%s",branch); 
                     list_by_branch(branch); break;
            case 6 : printf("Enter specific branch :  "); empty_string(branch); scanf("%s",branch);
                     printf("Enter specific address :  "); empty_string(address); scanf("%s",address);
                     list_by_branch_address(branch,address); break;
            case 7 : sort_by_names(); break;
            default : printf("Wrong choice\nTry Again\n"); 
        }
    }
}