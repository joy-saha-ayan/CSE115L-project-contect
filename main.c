
#include <stdio.h>
#include "manu.h"
#include<dos.h>
#include "login.h"
#include<dos.h>
#include "spalsh.h"


int main(void)
{
   int pss;
    int i;

     spalsh();
     printf("Enter [0] for Login  and  [1] for Create Account :  ");
     scanf("%d",&pss);
     if(pss==0)
        {
          login();
        }
     else if(pss==1)
       {
         create();
       }
     char num;
      do{
        Menu();
        scanf(" %c",&num);

        switch(num){
            case '0':
                printf("Exit.Thank you.");
                break;
            case '1':
                Add();
                break;
            case '2':
                view();
                break;
            case '3':
                Search();
                break;
            case '4':
                Edit();
                break;
            case '5':
                Delete();
                break;
            case '6':
                DeleteAll();
                break;
            case '7':
                system("cls");
                break;

            case '8':
                Guide();
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }while(num!='0');

    return 0;
}

