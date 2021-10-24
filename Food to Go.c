#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
 {
   int num;
   char Name[30];
   int price;
   struct node *rptr;
   struct node *lptr;
 }NODE;

NODE *Food_Menu(NODE *Start)
 {
   NODE *newnode[6];
   int i,j=0;
   newnode[0]=(NODE *)malloc(sizeof(NODE));
   newnode[0]->lptr=newnode[0]->rptr=NULL;
   newnode[0]->num=1;
   Start=newnode[0];
   for(i=1;i<7;i++)
   {
     newnode[i]=(NODE *)malloc(sizeof(NODE));
     newnode[j]->rptr=newnode[i];
     newnode[i]->lptr=newnode[j];
     newnode[i]->rptr=NULL;
     newnode[i]->num=i+1;
     j++;
    }
   strcpy(newnode[0]->Name,"Pani Puri");
   newnode[0]->price=35;
   strcpy(newnode[1]->Name,"Gobi Manchuri");
   newnode[1]->price=35;
   strcpy(newnode[2]->Name,"Veg Momos");
   newnode[2]->price=50;
   strcpy(newnode[3]->Name,"Paneer Rolls");
   newnode[3]->price=70;
   strcpy(newnode[4]->Name,"Tomoto Soup");
   newnode[4]->price=70;
   strcpy(newnode[5]->Name,"Garlic Bread");
   newnode[5]->price=90;
   strcpy(newnode[6]->Name,"Cheese Burger");
   newnode[6]->price=120;
   return Start;
}

void DisplayMenu(NODE *Start)
 {
   printf("\n.............FOOD MENU...............");
   while(Start!=NULL)
   {
     printf("\n %d\t %s\t %d",Start->num,Start->Name,Start->price);
     Start=Start->rptr;
   }
 }

NODE *EditPrice(NODE *Start)
 {
   NODE *temp;
   int fdnum,nprice;
   printf("\n Enter the food number for editing the price: ");
   scanf("%d",&fdnum);
   printf("\n Enter the newprice: ");
   scanf("%d",&nprice);
   temp=Start;
   while(temp!=NULL&&temp->num!=fdnum)
     temp=temp->rptr;
   if(temp==NULL)
    {
      printf("\n Invalid Food Number");
      return 0;
    }
  else
    temp->price=nprice;
  return Start;
 }

NODE *NewItem(NODE *Start)
 {
   NODE *nwnode,*temp;
   nwnode=(NODE *)malloc(sizeof(NODE));
   nwnode->rptr=nwnode->lptr=NULL;
   temp=Start;
   while(temp->rptr!=NULL)
     temp=temp->rptr;
   temp->rptr=nwnode;
   nwnode->lptr=temp;
   nwnode->num=temp->num+1;

   printf("\n Enter the name of the Food:");
   scanf("%s",nwnode->Name);

   printf("\nEnter the price of new food:");
   scanf("%d",&nwnode->price);
   return Start;
 }

 NODE *fdelete(NODE*Start)
 {
   NODE* temp;
   temp=Start;
   int fnum,i;
   printf("Enter the food number to be deleted: ");
   scanf("%d",&fnum);
   while(temp!=NULL&&temp->num!=fnum)
       temp=temp->rptr;
   if(temp==NULL)
    {
      printf("Food number not found: ");
      exit(0);
    }
   else if(temp==Start)
   {
    temp->rptr->lptr=NULL;
    Start=Start->rptr;
   }
   else if(temp->rptr==NULL)
   {
    temp->lptr->rptr=NULL;
   }
   else
  {
   temp->lptr->rptr=temp->rptr;
   temp->rptr->lptr=temp->lptr;
   }
   temp=Start;
   i=1;
   while(temp!=NULL)
   {
     temp->num=i++;
     temp=temp->rptr;
   }
   printf("\nThe food is successfully deleted from the Menu");
   free(temp);
   return Start;
 }


void GenerateBill(NODE *Start)
 {
   NODE *temp;
   int i,sum=0;
   int a[15];
   int Qty[15];
   printf("\n Enter the food number and Enter 0 for finalizing the Bill");
   printf("\n Enter the food number: ");
   scanf("%d",&a[0]);
   printf("\n Enter the Quantity: ");
   scanf("%d",&Qty[0]);
   for(i=0;a[i]!=0;i++)
   {
     printf("\n Enter the food number: ");
     scanf("%d",&a[i+1]);
     printf("\n Enter the Quantity: ");
     scanf("%d",&Qty[i+1]);
   }
   printf("\n **** BILL **** \n");
   temp=Start;
   printf("\nSL. \tNAME\t\tQty\tPRICE");
   for(i=0;a[i]!=0;i++)
   {
     temp=Start;
     while(temp->num!=a[i]&&temp->rptr!=NULL)
        temp=temp->rptr;
     printf("\n %d\t %s\t %d\t %d",i+1,temp->Name,Qty[i],temp->price);
     sum=sum+(Qty[i]*temp->price);
   }
   printf("\n..........................................");
   printf("\n\t\t\tBill Total=%d",sum);
}

void freenode(NODE *Start)
 {
   NODE *temp;
   temp=Start;
   while(temp!=NULL)
   {
    Start=temp;
    temp=Start->rptr;
    free(Start);
   }
 }

int main()
 {
   NODE *Start=NULL;
   int choice;
   Start=Food_Menu(Start);
   while(1)
   {
     printf("\n\t\t\tFOOD TO GO\n");

     printf("\n \n 1:Display Food Menu \n 2:Edit The Price \n 3:Add a New Item \n 4:Delete food from Menu \n 5:Generate the Bill \n 6:Exit");
     printf("\nEnter your choice: ");
     scanf("%d",&choice);
     switch(choice)
      {
        case 1: DisplayMenu(Start);
                break;
        case 2: Start=EditPrice(Start);
                printf("\n Food Menu after editing");
                DisplayMenu(Start);
                break;
        case 3: Start=NewItem(Start);
                printf("\n Food Menu after Addition of New Item");
                DisplayMenu(Start);
                break;
        case 4: Start=fdelete(Start);
                break;
        case 5: GenerateBill(Start);
                break;
        case 6: freenode(Start);
                exit(0);
        default: printf("\n Invalid Choice");
       }
    }
  return 0;
 }
