#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "conio2.h"
#include "rlyres.h"
int enterchoice()
{
    int choice,i;
    gotoxy(27,2);
    textcolor(YELLOW);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1; i<=80; i++)
        printf("-");
    printf("\n\nSelect an option\n\n");
    printf("1->View Trains\n2->Book Ticket\n3->View Ticket\n4->Search Ticket No\n5->View All Bookings\n6->View Train Bookings\n7->Cancel Ticket\n8->Cancel Train\n9->Quit\n\nEnter Choice:");
    scanf("%d",&choice);
    fflush(stdin);
    return choice;
}

void add_trains()
{
    FILE *fp=fopen("alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]= {{"123","BPL","GWA",2100,1500},
            {"546","BPL","DEL",3500,2240},
            {"345","HBJ","AGR",1560,1135},
            {"896","HBJ","MUM",4500,3360}
        };
        fp=fopen("alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File Saved Successfully\n");
        fclose(fp);
    }
    else
    {
    //    printf("File Already present!!!!");
        fclose(fp);
    }
}


//definition of view trains   case 1
void view_trains()
{
    int i;
    printf("TRAIN_NO\tFROM\tTO\tFIRST_AC_FARE\tSECOND_AC_FARE\n");
    for(i=1; i<80; i++)
               printf("-");
    FILE *fp=fopen("alltrains.dat","rb");
    Train tr;
    textcolor(LIGHTBLUE);
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
               printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac,tr.sac);
    }
        printf("\n\n\n\n");
        fclose(fp);
        textcolor(WHITE);
        printf("press any key to go to home screen!!!");
}

// definition of check_train_no()  used in book_ticket()  case 2
int check_train_no(char *trainno)
{
    FILE *fp=fopen("alltrains.dat","rb");
   Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
       if(strcmp(tr.train_no,trainno)==0)
       {
              fclose(fp);
             return 1;
       }
    }
    fclose(fp);
    return 0;
}


//definition for validate mobile number
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
        {
            return 0;
        }
        p_mob++;
    }
    return 1;
}

//definition of get_passenger_details()  case 2

Passenger* get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");

    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("Enter Passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
        if(strcmp(psn.p_name,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }
    int valid;
    printf("Enter Gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }
        if(psn.gender!='M' && psn.gender!='F')
            {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \t\t\t\t");
            gotoxy(19,2);
            textcolor(YELLOW);
            }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,3);
    printf("Enter Train number:");
    do
    {
        fflush(stdin);
        scanf(" %s",psn.train_no);
         if(strcmp(psn.train_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }

         valid=check_train_no(psn.train_no);

         if(valid==0)
         {
             textcolor(LIGHTRED);
             gotoxy(1,25);
             printf("error!! Invalid train number");
             getch();
             gotoxy(20,3);
             printf("\t\t\t\t\t");
             gotoxy(20,3);
             textcolor(YELLOW);
         }
    }while(valid==0);

    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,4);
    printf("Enter Travelling class(First AC:F,Second AC:S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
            {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Travelling class should be S or F (in uppercase)");
            valid=0;
            getch();
            gotoxy(48,4);
            printf(" \t\t\t\t");
            gotoxy(48,4);
            textcolor(YELLOW);
            }
    }while(valid==0);

    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,5);
    printf("Enter Address:");
    fflush(stdin);
    fgets(psn.p_address,30,stdin);
    pos=strchr(psn.p_address,'\n');
    *pos='\0';
        if(strcmp(psn.p_address,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
            }

    printf("Enter Age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation Cancelled!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }
        if(psn.age<0 || psn.age>125)
        {
            textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Error! Age should be positive and valid");
                valid=0;
                getch();
                gotoxy(11,6);
                printf("\t\t\t");
                textcolor(YELLOW);
                gotoxy(11,6);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t\t");
    gotoxy(1,7);

    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');

        if(pos!=NULL)
        {
        *pos='\0';
        }

        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Reservation cancelled!!!");

                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }

        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid mobile number...");

            getch();
            gotoxy(21,7);
            printf(" \t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);

    printf("\n\n%d %c %s %s %c %s %s",psn.age,psn.gender,psn.mob_no,psn.p_address,psn.p_class,psn.p_name,psn.train_no);
    getch();
    return &psn;
}


//  code for get_booked_ticket_count()
int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0&&pr.p_class==tc)
        {
            ++count;
        }
    }
    fclose(fp);
    return count;
}

//  code for last_ticket_no()

int last_ticket_no()
{
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    if(fread(&pr,sizeof(pr),1,fp)==0)
    {
        fclose(fp);
        return 0;
    }
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
 //   printf("%d is last ticket no \n%s is name\n %s is train no \n",pr.ticketno,pr.p_name,pr.train_no);
    getch();
    return pr.ticketno;
}


// code for book_ticket()

int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==2)
    {
        textcolor(LIGHTRED);
        printf("All seats in train number %s in class %c are full ",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp=fopen("allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!!! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}

int accept_ticket_no()
{
    int ticket_no,valid;
    gotoxy(60,1);
    textcolor(GREEN);
    printf("Press 0 to Exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter a valid Ticket No:");
    do
    {
        valid=1;
        fflush(stdin);
     scanf("%d",&ticket_no);
     if(ticket_no==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,25);
         printf("Cancelling process........!!!!!!");
         getch();
         textcolor(YELLOW);
         clrscr();
         return 0;
     }
     if(ticket_no<0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,25);
         printf("\t\t\t\t\t\t\t\t");
         gotoxy(1,25);
         printf("Error !!  ticket number should be positive number");
         getch();
         valid=0;
         gotoxy(25,1);
         printf("\t\t\t\t\t");
         gotoxy(25,1);
         textcolor(YELLOW);
        }

    }while(valid==0);
    fflush(stdin);
    return ticket_no;
}


void view_ticket(int ticket_no)
{
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!!! no bookings done yet..........");
        return;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
          {
              if(pr.ticketno==ticket_no)
                {
                    printf("\nName:%s\nGender:%c\nTrain number:%s\nClass:%c\nAddress:%s\nAge:%d\nMobile number:%s\nTicket Number:%d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.p_address,pr.age,pr.mob_no,pr.ticketno);
                    found=1;
                    break;
                }
          }
          if(!found)
          {
              textcolor(LIGHTRED);
              printf("\n\n\n\nNo Details of ticket number %d found",ticket_no);
              gotoxy(1,25);
              printf("\t\t\t\t\t\t\t\t\t");
          }
          fclose(fp);
}


char* accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid;
    gotoxy(60,1);
    textcolor(GREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(WHITE);
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,12,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
        {
            *pos='\0';
        }
        if(strcmp(mob_no,"0")==0)
        {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling input !!!");
                getch();
                textcolor(YELLOW);
                clrscr();
                return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid mobile number...");
            getch();
            gotoxy(27,1);
            printf(" \t\t\t\t\t");
            gotoxy(27,1);
            textcolor(WHITE);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int* get_ticket_no(char *p_mob_no)
{
    int count=0;
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!!! No bookings done yet.......");
        return NULL;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(!count)
    {
        fclose(fp);
        return NULL;
    }
    int *arr;
    int i=0;
    arr=(int*)malloc(sizeof(int)*(count+1));
    rewind(fp);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
            {
               *(arr+i)=pr.ticketno;
                i++;
            }
    }
    *(arr+i)=-1;
    fclose(fp);
    return arr;
}

void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nSorry!! NO tickets booked against mobile number %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress Any key to go back to main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for the mobile number %s",pmob_no);
    textcolor(GREEN);
    int i;
    printf("\n\nTICKET NUMBERS");
    printf("\n------------------------------------------------------------------------");
    for(i=0;*(pticket_no+i)!=-1;i++)
    {
        printf("\n%d",*(pticket_no+i));

    }
    textcolor(WHITE);
     printf("\n\n\n\n\n\n\n\n\n\n\n\nPress Any key to go back to main screen");
     getch();
        textcolor(YELLOW);
        free(pticket_no);
}


char* accept_train_no()
{
    static char train_no[10];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter Train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
              textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling input !!!");
                getch();
                textcolor(YELLOW);
       //         clrscr();
                return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
              textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid train number...");
            getch();
            gotoxy(20,1);
            printf(" \t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}


void view_bookings(char *train_no)
{
    int found=0,i;
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!!! No bookings done yet.....");
        getch();
        return;
    }
    Passenger pr;
    printf("TICKET_NO\tCLASS\tNAME\t\t\tGENDER\tAGE\tMOBILE_NUMBER\n");
    for(i=1;i<=80;i++)
    {
        printf("-");
    }

    int row=3;
    textcolor(LIGHTCYAN);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(49,row);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(!found)
    {
        clrscr();
        textcolor(RED);
        printf("\nNO Details of booking in train number %s found",train_no);

    }
    textcolor(WHITE);
    printf("\n\n\nPress any key to continue!!!");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}

void view_all_bookings()
{
    int found=0,i;
    FILE *fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry!!! File cannot be opened");
        getch();
        clrscr();
        return;
    }
    textcolor(YELLOW);
    printf("TRAIN_NO  CLASS\tTICKET_NO\tNAME\t\t\tGENDER\tMOBILE_NO\n");
    for(i=1;i<=80;i++)
    {
        printf("-");
    }
    Passenger pr;
    int row=3;
    textcolor(LIGHTGREEN);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%s\t  %c\t%d\t\t%s",pr.train_no,pr.p_class,pr.ticketno,pr.p_name);
        gotoxy(60,row);
        printf("%c\t%s\n",pr.gender,pr.mob_no);
        found=1;
        row++;
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("SORRY!!!!!NO RECORD FOUND...............");
    }
    textcolor(WHITE);
    printf("\n\n\nPress any key to continue..........");
    getch();
    fclose(fp);
    clrscr();
}


// case 7 cancel_ticket()

int cancel_ticket(int ticket_no)
{
      int result;
      FILE *fp1=fopen("allbookings.dat","rb");
      if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! NO bookings done yet.......");
        //perror("Caused by");
        return -1;
    }
       FILE *fp2=fopen("temp.dat","wb");
       Passenger pr;
       int found=0;
  while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.dat");
    }
    else
    {
        result=remove("allbookings.dat");
        if(result!=0)
        {
            perror("Error in removing allbookings.dat");
            return 2;
        }
       else{
        result=rename("temp.dat","d:\\codeblocks\\allbookings.dat");
        if(result!=0)
         {
            perror("Error in renaming.dat");
            return 2;
        }
       }
    }
    return found;
}


// case 8 cancel Train()


int cancel_train(char* train_no)
{
      int result;
      FILE *fp1=fopen("allbookings.dat","rb");
      if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! NO bookings done yet........");
        //perror("Caused by");
        return -1;
    }
       FILE *fp2=fopen("temp1.dat","wb");
       Passenger pr;
       int found=0;
  while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp1.dat");
    }
    else
    {
        result=remove("allbookings.dat");
        if(result!=0)
        {
            perror("Error in removing allbookings.dat");
            return 2;
        }
        else
            {
        result=rename("temp1.dat","d:\\codeblocks\\allbookings.dat");
        if(result!=0)
         {
            perror("Error in renaming temp1.dat");
            return 2;
        }
        }
    }
    return found;
}
