#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include <time.h>
#define N 20

int Q[N],Pr[N];
int r = -1,f = -1;
char Tokenhandler(int,char[]);
int a=0,b=0,c=0;                     //variables used to store tokens in array
int wa=0,wb=0,wc=0;                 //variables used to store waiting time of each counters
int A[100],B[100],C[100];          //array to store token numbers

// function for enqueue ,dequeue and print

void enqueue(int data,int p)               //Enqueue function to insert data and its priority in queue
{
	int i;
	if((f==0)&&(r==N-1))                    //Check if Queue is full that is no beds available
		printf("No room available");
	else
	{
		if(f==-1)                           //if beds are empty
		{
			f = r = 0;
			Q[r] = data;
			Pr[r] = p;

		}
		else if(r == N-1)                  //if there there is few beds full in Queue
		{
			for(i=f;i<=r;i++)
            { Q[i-f] = Q[i]; Pr[i-f] = Pr[i]; r = r-f; f = 0; for(i = r;i>f;i--)
				{
					if(p>Pr[i])
					{
						Q[i+1] = Q[i];
						Pr[i+1] = Pr[i];
					}
					else
						break;
					Q[i+1] = data;
					Pr[i+1] = p;
					r++;
				}
			}
		}
		else
		{
			for(i = r;i>=f;i--)
			{
				if(p>Pr[i])
				{
					Q[i+1] = Q[i];
					Pr[i+1] = Pr[i];
				}
				else
					break;
			}
			Q[i+1] = data;
			Pr[i+1] = p;
			r++;
		}
	}

}
void print()        //print the data of Queue, the patient data
{
int i;
	for(i=f;i<=r;i++)
	{
		printf("\nID of Patient = %d\tPriority = %d",Q[i],Pr[i]);
	}
}
int dequeue()      //remove the data from the queue that is removing the patient data
{
	if(f == -1)
	{
		printf("Rooms are Empty");    // no beds available
	}
	else
	{
		printf("Deleted Patient ID = %d\t Its Priority = %d",Q[f],Pr[f]);
		if(f==r)
			f = r = -1;
		else
			f++;
	}
}

int main()
{
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    char id[20];
    int i;
    int choice, choice2;
    long int phno, num;
          // variable to identify which type of main query is selected by visitor.
x:
do{
    printf("\n\t\t\t ___________________Welcome to SMS HOSPITAL____________________\n");
    printf("Today's Date -%d/%d/%d\n",stime.wDay,stime.wMonth,stime.wYear);
    printf("\nIs the Patient Emergent? \nEnter 0 for Yes, 1 for No \n");       // to check whether patient is emergent
    scanf("%d",&choice);
    if(choice!=0&choice!=1)
    {
        printf("Kindly enter a Valid Choice :\n");
        goto x;
    }

    if(choice==0)
    {
        int opt,n,i,p;
        printf("Enter Your Choice:-");
        do{
            printf("\n \n 1)Insert the Patient Data \n 2)Show the Patient Data \n 3)Delete the Patient Data \n 4)Exit \n");
            scanf("%d",&opt);
            switch(opt)
            {
                case 1:
                    printf("\nTotal Number of Emergent Patients :\n");
                    scanf("%d",&n);
                    i=0;
                    while(i<n)
                    {
                        printf("\nEnter Priority for Patient %d\n",i+1);
                        u:
                        printf("1-Accident\n2-Severe Medical Problem\n");
                        scanf("%d",&p);
                        if(p!=1 & p!=2)
                        {
                            printf("\nEnter valid choice\n");
                            goto u;
                        }
                        emer:
                            printf("\t Enter your Phone number\t");     //phone number entering
                            scanf("%s",id);
                            if(strlen(id)!=10)
                            {
                                printf("Please Enter 10 Digit Number");
                                goto emer;
                            }
                            FILE *fp;
                            fp = fopen("emergent.txt","a+");           //Writing Patient ID to emergent.txt file
                            fprintf(fp,"%s\n",id);                     //Adding numbers to the file
                            fclose(fp);
                        FILE *fptr;
                        int ctr = 0;
                        char c, chr;
                        fptr = fopen("emergent.txt", "r");
                        chr = getc(fptr);
                        while (chr != EOF)
                        {
                            if (chr == '\n')        //Count whenever new line is encountered
                            {
                                ctr = ctr + 1;
                            }
                            chr = getc(fptr);       //take next character from file.
                        }
                        fclose(fptr);
                        int data=ctr+1;
                        printf("your ID is %d\n",data);
                        enqueue(data,p);
                        i++;
                    }
                    break;
                    case 2:
                        print();
                    break;
                    case 3:
                        dequeue();
                    break;
                    case 4:
                        goto x;
                    break;
                    default:
                        printf("\nIncorrect Choice");
            }
        }while(opt!=0);
        goto x;
    }
    else
    {
        e:
        printf("\tAre you an Old Patient?\n Enter 0 for Yes, 1 for No\n");
        scanf("%d",&choice2);
        if(choice2!=0&choice2!=1)
        {
            printf("Kindly Enter a Valid Choice :\n");
            goto e;
        }
        if(choice2==0)
        {
            int h, count=0;
            char sta[20];
            t:
            printf("Enter your Phone Number :\t");
            scanf("%s",id);
            if(strlen(id)!=10)
            {
                printf("Please Enter 10 Digit Number");
                goto t;
            }
            FILE *fp;
            fp = fopen("patient.txt","r");
            if (fp == NULL)
            {
                printf("No Record Found.\n");
                goto x;
            }
            strcpy(sta,id);
            printf("Your Phone Number==%s\n",sta);
            char string[50];
            count=0;
            while(!feof(fp))
            {
                fscanf(fp,"%s", string);
                if(strcmp(string,sta)==0)         //if record is found
                count++;
            }
            fclose(fp);
            if(count!=0)
            {
                char str[20];
                sprintf(str,"%s.txt",sta);
                FILE *fp;
                fp = fopen(str,"r");
                if (fp == NULL)
                {
                    printf("\n You are not Registered to our System, Kindly Register\n");
                    goto y;
                    exit(0);
                };
                printf("You are an old patient\n");
                char dataToBeRead[50];
                while(fgets(dataToBeRead, 50, fp) != NULL)   // Read the dataToBeRead from the file using fgets() method
                {
                    printf( "%s" , dataToBeRead ) ;
                }
                fclose(fp) ;
                goto b;
            }
            else
            {
                printf("Your Phone Number is not Registered. Register your Number :\n");
                goto y;
            }
        }
        else
        y:
        printf("\t Enter Phone Number\t");
        scanf("%s",id);
        if(strlen(id)!=10)
        {
            printf("Please Enter 10 Digit Number");
            goto y;
        }
        char str2[20];
        sprintf(str2,"%s.txt",id);
        FILE *fp3;
        fp3 = fopen(str2,"r");
        if (fp3 != NULL)
        {
            printf("\n Number already exist, Kindly Check Again\n");      //Patient ID exist in the system
            goto x;
            exit(0);
        }
        fclose(fp3);
        FILE *fp;
        fp = fopen("patient.txt","a+");
        fprintf(fp,"%s\n",id);
        fclose(fp);
        b:
        printf("\n\n___________________Room/location_________________\n\n");
        printf("\t 1. Doctor \n");
        printf("\t 2. Laboratory and Tests \n");
        printf("\t 3. Treatment \n");
		printf("\nSelect from 1 to 3: ");
        scanf("%d",&i);
        if(i!=2 & i!=1 & i!=3)
        {
            printf("Kindly enter Valid Choice\n");
            goto b;
        }
        char str20[10];
        sprintf(str20, "%s.txt", id);
        FILE *fp10;
        fp10 = fopen(str20,"a+");
        if (fp10 == NULL)
        {
            printf("\nNo Record Found.");
            exit(0);
        };
        fclose(fp10) ;
        if(i==1 || i==2 || i==3)
        {
            char r=Tokenhandler(i,str20);
            printf("\nYour Token Number is: %c",r);
            printf("\n");
        }
        else
            printf("\nPlease select a Valid Sub-Query.\n");
    }
}while(1);
    return 0;
}

char Tokenhandler(int qno,char str20[10])
{
    time_t curtime;
    time(&curtime);
    int sq,time;
    switch(qno)
    {
        case 1:
        {
            char ch;
            START1:
                printf("\nSelect Doctor Category:\n");
                printf("\t1.General Doctor\n");
                printf("\t2.Cardiologist\n");
                printf("\t3.Neurologist\n");
                scanf("\t%d",&sq);
                FILE *fp10;
                fp10 = fopen(str20,"a+");
                if (fp10 == NULL)
                {
                    printf("\nFile does not exist.");
                    exit(0);
                };
                if(sq==1)
                    fprintf(fp10, "%s Visited General\n",ctime(&curtime));
                else if(sq==2)
                    fprintf(fp10, "%s Visited Cardio\n",ctime(&curtime));
                else if(sq==3)
                    fprintf(fp10, "%s Visited Neuro\n",ctime(&curtime));
                fclose(fp10);
                switch(sq)
                {
                    case 1:
                        time=20;
                        break;
                    case 2:
                        time=15;
                        break;
                    case 3:
                        time=10;
                        break;
                    default:
                        printf("Please Select a Valid Query.");
                        goto START1;
                }
                printf("You have been directed to Counter A.\n");
                FILE *fp;
                fp=fopen("Acounter.txt","r");
                if(fp == NULL)
                {
                     printf("\nFile does not exist.");
                     exit(0);
                }
                ch=getc(fp);
                fclose(fp);
                fp=fopen("Acounter.txt","r+");
                int x;            // to update the previous token number
                x=ch;
                x++;
                putc(x,fp);
                fclose(fp);
                A[a]=ch;
                a++;
                if((a-1)!=0 && (a-1)!=1)                 // for displaying the number of people in the queue before you
                {
                    printf("There are %d people before you in the queue.\n",a-1);
                    printf("\nToken Numbers before you in the queue:");
                    for(int j=0;j<a-1;j++)
                        printf("\n\t%c",A[j]);
                }
                if((a-1)==0)
                {
                    printf("There are no people before you in the queue.Go to counter A.");
                }
                if((a-1)==1)
                {
                    printf("There is 1 person before you in the queue.");
                    printf("Token numbers before you in the queue:");
                    for(int j=0;j<a-1;j++)
                        printf("\n\t%c",A[j]);
                }
                printf("\nYour waiting time is %d",wa);
                wa=wa+time;
                return ch;
        }
        break;
        case 2:
        {
            char ch;
            START2:
                printf("\n Laboratory and Tests \n");
                printf("\t 1.Pathology Lab\n");
                printf("\t 2.Scan Lab (X-rays/CT/MRI)\n");
                printf("\t 3.Radiology \n");
                scanf("\t%d",&sq);
                FILE *fp10;
                fp10 = fopen(str20,"a+");
                if (fp10 == NULL)
                {
                    printf("\nFile does not exist.");
                    exit(0);
                };
                if(sq==1)
                    fprintf(fp10, "%s Visited Path Lab\n",ctime(&curtime));
                else if(sq==2)
                    fprintf(fp10, "%s Visited Scan Lab\n",ctime(&curtime));
                else if(sq==3)
                    fprintf(fp10, "%s Visited Radiology Lab\n",ctime(&curtime));
                fclose(fp10) ;
                switch(sq)
                {
                case 1:
                     time=15;     //estimated time for path lab
                     break;
                case 2:
                    time=20;      //estimated time for scans
                    break;
                case 3:
                    time=20;      //estimated time for radiology lab
                    break;
                default:
                    printf("Please select a Valid Query.");
                    goto START2;         //jump to START2 for selecting a correct sub query
                }
                printf("You have been directed to Counter B.\n");
                FILE *fp;
                fp=fopen("Bcounter.txt","r");
                if(fp == NULL)
                {
                     printf("\nFile does not exist.");
                     exit(0);
                }
                ch=getc(fp);
                fclose(fp);
                fp=fopen("Bcounter.txt","r+");
                int x;             // to update the previous token number
                x=ch;
                x++;
                putc(x,fp);
                fclose(fp);
                B[b]=ch;                      //storing the then tokens in a queue
                b++;
                if((b-1)!=0 && (b-1)!=1)
                {
                    printf("There are %d people before you in the queue.\n",b-1);
                    printf("Token numbers before you in the queue:");
                    for(int j=0;j<b-1;j++)
                    printf("\n%c",B[j]);
                }
                if((b-1)==0)
                {
                    printf("There are no people before you in the queue.Go to counter B.");
                }
                if((b-1)==1)
                {
                    printf("There is 1 person before you in the queue.");
                    printf("Token numbers before you in the queue:");
                    for(int j=0;j<b-1;j++)
                        printf("\n%c",B[j]);
                }
                printf("\nYour waiting time is %d",wb);
                wb=wb+time;
                return ch;
        }
        break;
        case 3:
        {
            char ch;
            START3:
            printf("\n TREATMENT:\n");
            printf("\t 1.Surgery\n");
            printf("\t 2.Medication\n");
            printf("\t 3.Therapy\n");
            scanf("\t%d",&sq);
            FILE *fp10;
            fp10 = fopen(str20,"a+");
            if (fp10 == NULL)
            {
                printf("\nFile does not exist.");
                exit(0);
            };
            if(sq==1)
                fprintf(fp10, "%s Had Surgery \n",ctime(&curtime));
            else if(sq==2)
                fprintf(fp10, "%s Purchased Medicines \n",ctime(&curtime));
            else if(sq==3)
                fprintf(fp10, "%s Recommended Therapy \n",ctime(&curtime));
            fclose(fp10) ;
            switch(sq)
            {
            case 1:
                    time=120;
                    break;
            case 2:
                    time=10;
                    break;
            case 3:
                    time=50;
                    break;
            default:
                    printf("Please select a Valid Query.");
                    goto START3;     //jump to START3 for selecting a correct sub query
            }
            printf("You have been directed to counter C.\n");
            FILE *fp;
            fp=fopen("Ccounter.txt","r");
            if(fp == NULL)
            {
                printf("\nFile does not exist.");
                exit(0);
            }
            ch=getc(fp);
            fclose(fp);
            fp=fopen("Ccounter.txt","r+");
            int x;
            x=ch;
            x++;
            putc(x,fp);
            fclose(fp);
            C[c]=ch;              //storing the then tokens in a queue
            c++;
            if((c-1)!=0 && (c-1)!=1)
            {
                printf("There are %d people before you in the queue.\n",c-1);
                printf("Token numbers before you in the queue:");
                for(int j=0;j<c-1;j++)
                    printf("\n%c",C[j]);
            }
            if((c-1)==0)
            {
                printf("There are no people before you in the queue.Go to counter C.");
            }
            if((c-1)==1)
            {
                printf("There is 1 person before you in the queue.");
                printf("Token numbers before you in the queue:");
                for(int j=0;j<c-1;j++)
                    printf("\n%c",C[j]);
            }
            printf("\nYour waiting time is %d",wc);
            wc=wc+time;
            return ch;
        }
        default:
        {
            printf("Not a valid query start again");
            exit(0);
        }
    }
}
