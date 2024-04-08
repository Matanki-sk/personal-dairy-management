#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
int password();
void addmemories();
void viewmemories();
void editmemories();
void editpassword();
void delete();
struct memories{
    char time[10];
    char name[30];
    char place[30];
    char duration[10];
    char note[200];
    char spclnote[50];
};
int main(){
    int choice;
    char password1[20];
    while(1){
    printf("\n-----------------------------\n");
    printf("  PERSONAL DAIRY MANAGEMENT\n ");
    printf("-----------------------------\n");
    printf("          CHOICES             \n");
    printf("\t1.ADD A MEMORIES      -   1\n");
    printf("\t2.VIEW A MEMORIES     -   2\n");
    printf("\t3.EDIT THE MEMORIES   -   3\n");
    printf("\t4.DELETE              -   4\n");
    printf("\t5.EDIT THE PASSWORD   -   5\n");
    printf("\t6.EXIT                -   6\n");
    printf("\n ENTER THE TASK TO BE DONE");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        addmemories();
        break;
    case 2:
        viewmemories();
        break;
    case 3:
        editmemories();
        break;
    case 4:
        delete();
        break;
    case 5:
        editpassword();
        break;
    case 6:
        printf(" THANK YOU :)\n");
        exit(0);
        break;
    
    default:
        printf("\nyou entered wrong choice");
        break;
    }
    }
    system("cls");
    return 1;
}
int password(){
    FILE *file4;
    int j;
    char access[20]={0},choice[20]={0},ch;
    printf("\n\t\tPASSWORD VERIFICATON \n ");
    printf("\n\tSECUTIRY PURPOSE ::\n");
    printf("\n\tONLY THREE TRAILS ARE ALLOWED\n");
    for(int i=0;i<3;i++){
        j=0;
        printf("\nENTER THE  PASSWORD\n");
        access[0]=getch();
        while(access[j]!='\r'){
            if(access[j]=='\b'){
                j--;
                printf("\b");
                printf(" ");
                printf("\b");
                access[j]=getch();
            }
            else{
                printf("*");
                j++;
                access[j]=getch();
            }
        }
        access[j]='\0';
        file4=fopen("SE.txt","r");

        if (file4==NULL)
        {
            printf("\n\n\tERROR WITH THE SYSTEM FILE...[FILE MISSING]\n");
            getch();
            return 1;
        }
        else{
            j=0;
        }
        while(1){
            ch=fgetc(file4);
            if(ch==EOF){
                choice[j]='\0';
                break;
            }
            choice[j]=ch;
            j++;
        }
                printf("access:%s",access);

        printf("password:%s",choice);
        if(strcmp(access,choice)==0){
            printf("\n\t ACCESS GRANTED \n");
            printf("\n\t PASSWORD IS VERIFIED\n");
            return 0;
        }
        
        else{
            printf("\nYOU ENTERED WRONG PASSWORD....:( TRY AGAIN...");
            continue;
        }
    }
    return 1;
}
void addmemories(){
    system("cls");
    FILE *file1;
    int exist=0;
    char add = 'Y';
    char spcl;
    struct memories a;
    char date[10],time[10];
    printf("***************************\n");
    printf("ADD YOUR MEMORIES HERE :)\n");
    printf("***************************\n"); 
    printf("ENTER THE DATE ;; \n");
    fflush(stdin);   
    scanf("%s",&date);
    file1=fopen(date,"ab+");
    if(file1== NULL){
        file1=fopen(date,"wb+");
        if(file1== NULL){
            printf("SYSTEM ERROR\n");
            printf("FILE CANT OPEN\n");
            printf("PRESS ANY KEY TO EXIT..!\n");
            getch();
            return ;
        }
        
    }
    while(add =='y' || add =='Y'){
        exist=0;
        fflush(stdin);
        printf("ENTER TIME(hh:mm):\n");
        scanf("%s",&time);
        rewind(file1);
        while(fread(&a,sizeof(a),1,file1)==1){
            if(strcmp(a.time,time)== 0){
                printf("THIS IS ALREADY EXISTS\n");
                exist=1;
                break;
            }      
        }
        if(exist == 0){
            strcpy(a.time,time);
            printf("ENTER NAME ::\n");
            fflush(stdin);
            gets(a.name);
            fflush(stdin);
            printf("ENTER THE PLACE :: \n");
            gets(a.place);
            fflush(stdin);
            printf("ENTER THE DURATION :: \n");
            gets(a.duration);
            fflush(stdin);
            printf(" DO YOU WANT TO ADD SPECIAL NOTES \n?");
            scanf("%c",&spcl);
            fflush(stdin);
            if(spcl=='Y'|| spcl=='y'){
                gets(a.spclnote);
            }
            fflush(stdin);
            printf("ENTER YOUR NOTES :: \n");
            gets(a.note);
            fwrite(&a,sizeof(a),1,file1);
            printf("YOUR MEMORIES IS ADDED\n");

        }
        printf("DO YOU WANT TO ADD ANOTHER MEMORIES(Y/N)?");
        fflush(stdin);
        add=getchar( );
    }
    fclose(file1);
    printf("YOUR MEMORIES ARE ADDED IN YOUR PERSONAL DAIRY \n ");
    printf("PRESS ANY KEY TO RETURN TO CHOICES..");
    getch();
}
void viewmemories(){
    FILE *file2;
    int ch;
    struct memories b;
    char date[20],time[15],choice;
    printf("\n**********************************\n");
    printf("\nYOU CAN VIEW YOUR MEMORIES HERE: )");
    printf("\n**********************************\n");
    fflush(stdin);
    choice=password();
    if(choice!=0){
        return ;
    }
    do{
        printf("\nENTER THE DATE TO BE VIEWED(dd-mm-yyyy)\n");
        fflush(stdin);
        gets(date);
        file2=fopen(date,"rb");
        if(file2 == NULL ){
            printf( "\nTHE MEMORIES DOES NOT EXIST...\n" ) ;
            printf("\nPRESS ANY KEY TO EXIT...");
            getch();
            return ;
        }
        system("cls");
        printf("\n\tHOW WOULD YOU LIKE TO VIEW:\n");
        printf("\n\t1.WHOLE MEMORIES OF THE DAY.");
        printf("\n\t2.MEMORIES OF FIX TIME.");
        printf("\n\t\tENTER YOUR CHOICE:");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            printf("\nTHE MEMORIES OF THE %s IS :",date);
            while(fread(&b,sizeof(b),1,file2)==1)
            {
               printf("\n");
               printf("\nTIME :\t%s",b.time);
               printf("\nPLACE :\t%s",b.place);
               printf("\nNAME :\t%s",b.name);
               printf("\nDURATION :\t%s",b.duration);
               printf("\nSPECIAL NOTE :\t%s",b.spclnote);
               printf("\nnote :\t%s",b.note);
               printf("\n");
            }
            break;
        case 2:
            fflush(stdin);
            printf("\nENTER THE TIME(hh:mm)\n:");
            gets(time);
            while(fread(&b,sizeof(b),1,file2)==1){
                if(strcmp(b.time,time)==0){
                    printf("\n");
                    printf("\nTIME :\t%s",b.time);
                    printf("\nPLACE :\t%s",b.place);
                    printf("\nNAME :\t%s",b.name);
                    printf("\nDURATION :\t%s",b.duration);
                    printf("\nSPECIAL NOTE :\t%s",b.spclnote);
                    printf("\nnote :\t%s",b.note);
                    printf("\n");    

                }
            } 
            break;       
        default:
            printf("\nYOU TYPED SOMETHING WRONG..:(\n)");
            break;
        }
        printf("\n\nWOULD YOU LIKE TO CONTINUE VIEWING...(Y/N):");
        fflush(stdin);
        scanf("%c",&choice);
    }
    while(choice=='Y'||choice=='y');
    fclose(file2);
    return ;    

}
void editmemories(){
    system("cls");
    FILE *file3;
    char date[20],time[15];
    int num,verify,count;
    char choice;
    struct  memories c;
    
    printf("\n****************\n");
    printf("\nEDITING PLACE\n");
    printf("\n*****************\n");
    verify=password();
    if(verify!=0){
        return ;
    }
    do{
        printf("\nENTER THE DATE OF THE MEMORIES TO BE EDITED(dd-mm-yyyy)");
        fflush(stdin);
        gets(date);
        printf("\n\tENTER TIME:(hh:mm):");
        gets(time);
        file3=fopen(date,"rb+");
        if(file3==NULL){
            printf("\nTHERE IS NO  MEMORIES ON THAT DAY\n");
            printf("\nPRESS ANY KEY TO EXIT...");
            getch();
            return ;
        }
        while(fread(&c,sizeof(c),1,file3)==1){
            if(strcmp(c.time,time)==0){
                printf("\n");
                printf("\n\nYOUR EXISITING RECORD IS :");
                printf("\nTIME :\t%s",c.time);
                printf("\nPLACE :\t%s",c.place);
                printf("\nNAME :\t%s",c.name);
                printf("\nDURATION :\t%s",c.duration);
                printf("\nSPECIAL NOTE :\t%s",c.spclnote);
                printf("\nnote :\t%s",c.note);
                printf("\n");
                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");
                printf("\n1.TIME.");
                printf("\n2.NAME.");
                printf("\n3.PLACE.");
                printf("\n4.DURATION.");
                printf("\n5.SPECIAL NOTE.");
                printf("\n6.NOTE.");
                printf("\n7.WHOLE RECORD.");
                printf("\n8.GO BACK TO MAIN MENU.");    
            do{
                printf("\nENTER YOUR CHOICE;");
                fflush(stdin);
                scanf("%d",&num);
                fflush(stdin);
                switch (num)
                {
                case 1:
                    printf("\nENTER THE TIME TO BE CHANGED(hh:mm);");
                    gets(c.time);
                    break;
                case 2:
                    printf("\nENTER THE NEW NAME TO BE CHANGED");
                    gets(c.name);
                    break;
                case 3:
                    printf("\n ENTER THE PLACE TO BE CHANGED ");
                    gets(c.place);
                    break;
                case 4:
                    printf("\nENTER THE DURATION TO BE CHANGED");
                    gets(c.duration);
                    break;
                case 5:
                    printf("\nENTER THE NEW SPECIAL NOTE :");
                    gets(c.spclnote);
                    break;
                case 6:
                    printf("\nENTER THE NEW NOTE");
                    gets(c.note);
                    break;
                case 7:
                    printf("\nENTER THE NEW DATAS");
                    printf("\nNEW NAME ::");
                    gets(c.name);
                    printf("\nNEW TIME ::");
                    gets(c.time);
                    printf("\nNEW PLACE ::");
                    gets(c.place);
                    printf("\nDURATION ::");
                    gets(c.duration);
                    printf("\nSPECIAL NOTE ::");
                    gets(c.spclnote);
                    printf("NOTE ::");
                    gets(c.note);
                    break;
                case 8:
                    printf("\nENTER ANY KEY TO EXIT");
                    getch();
                    return ;
                    break;
                
                default:
                    printf("\nOopps..! YOU ENTERED SOMETHING WRONG TRY AGAIN :(");
                    break;
                }
            }while (num>1 && num <8);
            fseek(file3,-sizeof(c),SEEK_CUR);
            fwrite(&c,sizeof(c),1,file3);
            fseek(file3,-sizeof(c),SEEK_CUR);
            fread(&c,sizeof(c),1,file3);
            choice=5;
            break;   
            }
        }
        if(choice==5){
            system("cls");
            printf("\nTHE MEMORIES ARE MODIFIED");
            printf("\nTHE NEW DATA IS ::");
            printf("\nTIME: %s",c.time);
            printf("\nNAME: %s",c.name);
            printf("\nPLACE: %s",c.place);
            printf("\nDURATION: %s",c.duration);
            printf("\nSPECIAL NOTE:%s",c.spclnote);
            printf("\nNOTE: %s",c.note);
            fclose(file3);
            printf("\nDO YOU WANT TO EDIT ANOTHER MEMORIES(Y/N)");
            scanf("%c",&choice);
            count++;

        }
        else{
            printf("\n\nTHE RECORD DOES NOT EXSIST...:(");
            printf("\n\nWOULD YOU WANT TO TRY AGAIN(Y/N)\n");
            scanf("%s",&choice);
        }
    }while(choice=='Y'||choice=='y');
    fclose(file3);
    if(count>=1){
        printf("\n%d FILES ARE EDITED",count);
    }
    else{
        printf("\nNO FILES ARE EDITED");
    }
    printf("\nPRESS ANY KEY TO EXIT");
    getch();    
}
void delete(){
    system("cls");
    FILE *file4,*file5;
    struct  memories d;
    char filename[20],another='Y',time[20];
    int choice,verify;
    verify=password();
    if(verify!=0){
        return ;
    }
    printf("\nDELETING MENU");
    while( another=='Y'){
        printf("\n\n\tHOW WOULD YOU LIKE TO DELETE.");
        printf("\n\n\t1.#DELETE WHOLE RECORD\t\t\t");
        printf("\n\t2.#DELETE A PARTICULAR RECORD BY TIME\t");
        do
        {
            printf("\n\t\tENTER YOU CHOICE:");
            scanf("%d",&choice);
            switch(choice)
            {
            case 1:
                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
                fflush(stdin);
                gets(filename);
                file4= fopen (filename, "wb" ) ;
                if (file4== NULL )
                {
                    printf("\nTHE FILE DOES NOT EXISTS");
                    printf("\nPRESS ANY KEY TO GO BACK.");
                    getch();
                    return ;
                }
                fclose(file4);
                remove(filename);
                printf("\nDELETED SUCCESFULLY...");
                break;
            case 2:
                printf("\n\tENTER THE DATE OF RECORD:[yyyy-mm-dd]:");
                fflush(stdin);
                gets(filename);
                file4= fopen (filename, "rb" ) ;
                if (file4== NULL )
                {
                    printf("\nTHE FILE DOES NOT EXISTS");
                    printf("\nPRESS ANY KEY TO GO BACK.");
                    getch();
                    return ;
                }
                file5=fopen("temp","wb");
                if(file5==NULL)
                {
                    printf("\nSYSTEM ERROR");
                    printf("\nPRESS ANY KEY TO GO BACK");
                    getch();
                    return ;
                }
                printf("\n\tENTER THE TIME OF RECORD TO BE DELETED:[hh:mm]:");
                fflush(stdin);
                gets(time);
                while(fread(&d,sizeof(d),1,file4)==1)
                {
                    if(strcmp(d.time,time)!=0)
                        fwrite(&d,sizeof(d),1,file5);
                }
                fclose(file4);
                fclose(file5);
                remove(filename);
                rename("temp",filename);
                printf("\nDELETED SUCCESFULLY...");
                break;
            default:
                printf("\n\tYOU ENTERED WRONG CHOICE");
                break;
            }
        }
        while(choice<1||choice>2);
        printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
        scanf("%c",&another);
    }
    printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}
void editpassword(){
   // system("cls");
   
    printf("\n");
    char access[10],confrim[10],ch,str_pw[10]="";
    int j,i,check,choice;
    FILE *file5;
    file5=fopen("SE.txt","rb");
    if(file5== NULL){
        file5=fopen("SE.txt","wb");
        if(file5==NULL)
        {
            printf("\nSYSTEM ERROR...\n");
            getch();
            return ;
        }
        fclose(file5);
        printf("\nSYSTEM RESTORED...\nYOUR PASSWORD IS 'ENTER'\n PRESS ENTER TO CHANGE PASSWORD\n\n");
        getch();
    }
    fclose(file5);
    check=password();
    if(check==1){
        return ;
    }
   do{
        if(check==0)
        {
            i=0;
            choice=0;
            printf("\nENTER THE NEW PASSWORD\n");
            fflush(stdin);
            access[0]=getch();
            while(access[i]!='\r'){
                if(access[i]=='\b'){
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    access[i]=getch();
                }
                else{
                    printf("*");
                    i++;
                    access[i]=getch();
                }
            }
            access[i]='\0';
            i=0;
            printf("\n\nCONFRIM PASSWORD\n");
            confrim[0]=getch();
            while(confrim[i]!='\r'){
                if(confrim[i]=='\b'){
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confrim[i]=getch();
                }
                else{
                    printf("*");
                    i++;
                    confrim[i]=getch();
                }
            }
            confrim[i]='\0';
            if(strcmp(access,confrim)==0){
                file5=fopen("SE.txt","wb");
                if(file5==NULL)
                {
                    printf("\n\t\tSYSTEM ERROR");
                    getch();
                    return ;
                }
                i=0;
                // while(access[i]!='\0')
                // {
                //     ch=access[i];
                //     strcat(str_pw,acces);
                //     i++;
                // }
               // strcat(str_pw,access);
                fprintf(file5,"%s",access);
                
                fclose(file5);
            }
            else{
                printf("THE NEW PASSWORD DOES NOT MATCH\n");
                choice=1;
            }
        }

    }
    while(choice==1);
    printf("\n\n\tPASSWORD CHANGED...\n\n\tPRESS ANY KEY TO GO BACK...");
    getch();
}
