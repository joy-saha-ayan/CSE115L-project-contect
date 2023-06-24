
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define tab printf("\t\t")

void Menu(void);
void Add(void);
void view(void);
void Search(void);
void Edit(void);
void Delete(void);
void DeleteAll(void);
void ClearWindow(void);
void L_WithSpace(char *Name[20],char ContactInfo);
void ErrorAndRestart(char *error[100]);
void GoBack(void);
void Guide(void);





void Menu(void)
{
    tab;printf("\n **** Contact Management System Using C ****\n");
    tab;printf("\n    \tMAIN MENU\n");
    tab;printf(" ==================================\n");
    tab;printf(" [1] Add a new Contact\n");
    tab;printf(" [2] Show all Contacts\n");
    tab;printf(" [3] Search contact\n");
    tab;printf(" [4] Edit a Contact\n");
    tab;printf(" [5] Delete a Contact\n");
    tab;printf(" [6] Delete All Contact\n");
    tab;printf(" [7] Clear Window\n");
    tab;printf(" [8] Guideline\n");
    tab;printf(" [0] Exit\n");
    tab;printf("====================================\n");
    tab;printf("Enter the choice:");
}

void Add(void)
{
    system("cls");
    tab;printf("\n **** Add new Contact ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    printf("\n*Phone should maximum 20 characters long.\n");
    printf("Enter The Phone Number: ");
    scanf("  %s",Phone);
    if(strlen(Phone) > 20){
        ErrorAndRestart("!!!!Phone Length Error!!!!");
        return;
    }

    printf("\n*Email should maximum 30 characters long.\n");
    printf("Enter The Email: ");
    scanf("%s",Email);
    if(strlen(Email) > 30){
        ErrorAndRestart("!!!!Email Length Error!!!!");
        return;
    }

    strcat(NewContact,Name);
    strcat(NewContact,"\n");
    strcat(NewContact,Phone);
    strcat(NewContact,"\n");
    strcat(NewContact,Email);
    strcat(NewContact,"\n");

    FILE *allContactTxtFile = fopen("All-Contact.txt","a"); // create file and open in append mood
    fprintf(allContactTxtFile,NewContact); // store contact in file
    fclose(allContactTxtFile); // close the file
    printf("\n Added Successfully!\n");
    GoBack();
}

void view(void)
{
    system("cls");
    tab;printf("\n **** All Contacts ****\n\n");
    FILE* AllContactTextFile;
    int LineLength = 300;
    char Line[LineLength];

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllContactTextFile = fopen("All-Contact.txt", "r");
    int TotalContact = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllContactTextFile)) {
        LineCount++;
        if(LineCount==1){
            // name
            L_WithSpace(Line,'n');
        }else if(LineCount == 2){
            // phone
           L_WithSpace(Line,'p');
        }else if(LineCount == 3){
            // email
            L_WithSpace(Line,'e');
            LineCount=0;
            TotalContact++;
        }
    }
    printf("You Have Total %d Contacts.\n\n",TotalContact);
    fclose(AllContactTextFile);
    GoBack();
}

void L_WithSpace(char *Name[20],char ContactInfo) //Print Line With Space
{
    int i;
    char *F_Name = NULL;
    F_Name = strdup(Name);
    int F_NameLenght = strlen(F_Name);

    int TotalSpace = 0;
    if(ContactInfo == 'n'){
        TotalSpace = 20 - F_NameLenght; // name
    }else if(ContactInfo == 'p'){
        TotalSpace = 20 - F_NameLenght; // phone
    }else if(ContactInfo == 'e'){
        TotalSpace = 30 - F_NameLenght; // email
    }

    printf("|");
    for(i=0;i<F_NameLenght-1;i++){
        printf("%c",F_Name[i]);
    }

    for(i=0;i<=TotalSpace;i++){
        printf(" ");
    }

    if(ContactInfo == 'e'){
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

void Search(void)  //Search Contact
   {
    system("cls");
    tab;printf("\n **** Search Contact ****\n\n");

    int FoundContact = 0;
    char Name[100];
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }
    strcat(Name,"\n");

    FILE* AllContactFile;
    int LineLength = 255;
    char Line[LineLength];
    AllContactFile = fopen("All-Contact.txt", "r");
    int LineCount = 0;
    int NeedToPrintLine = 0;
    while(fgets(Line, LineLength, AllContactFile)) {
       LineCount++;
        if(LineCount == 1 && strcmp(Name, Line) == 0){
            FoundContact = 1;
            NeedToPrintLine = 3;
        }
        if(NeedToPrintLine > 0){
            if(LineCount==1){
                printf("\nContact information of %s",Name);
                printf("\nName: %s",Line);
                NeedToPrintLine = 2;
            }else if(LineCount == 2){
                printf("Phone: %s",Line);
                NeedToPrintLine = 1;
            }else if(LineCount == 3){
                printf("Email: %s\n",Line);
                NeedToPrintLine = 0;
            }
        }
        if(LineCount == 3){
            LineCount=0;
        }
    }
    fclose(AllContactFile);
    if(FoundContact == 0){
        printf("\nSorry no contact found for %s\n",Name);
    }
    GoBack();
}

void Edit(void)   // Edit Contact
{
    system("cls");
    tab;printf("\n **** Edit Contact ****\n\n");

    int LineCount = 0;
    int FoundContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullContact[300];
    NewFullContact[0] = 0;
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLength = 255;
    char Line[LineLength];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Line, LineLength, OurExistingFile)) {
        LineCount++;

        if(LineCount == 1 && strcmp(GivenName, Line) == 0){
            // we found the contact
            FoundContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            if(LineCount == 1){
                printf("\n*New Name should maximum 20 characters long.\n");
                printf("Old Name is: %s",Line);
                printf("New Name(0 for skip): ");
                scanf(" %[^\n]s",NewName);
                if(strcmp(NewName, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewName) > 20){
                        ErrorAndRestart("!!!!Name Length Error!!!");
                        return;
                    }

                    strcat(NewFullContact,NewName);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 2;
            }else if(LineCount == 2){
                printf("\n*New Phone should  maximum 20 characters long.\n");
                printf("Old Phone is: %s",Line);
                printf("New Phone(0 for skip): ");
                scanf("%s",NewPhone);
                if(strcmp(NewPhone, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewPhone) > 20){
                        ErrorAndRestart("!!!!Phone Length Error!!!");
                        return;
                    }

                    strcat(NewFullContact,NewPhone);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 1;
            }else if(LineCount == 3){
                printf("\n*New Email should maximum 30 characters long.\n");
                printf("Old Email is: %s",Line);
                printf("New Email(0 for skip): ");
                scanf("%s",NewEmail);

                if(strcmp(NewEmail, "0") == 0){
                    strcat(NewFullContact,Line);
                }else{
                    if(strlen(NewEmail) > 30){
                        ErrorAndRestart("!!!!Email Length Error!!!");
                        return;
                    }

                    strcat(NewFullContact,NewEmail);
                    strcat(NewFullContact,"\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile,NewFullContact);
            }
        }else{
            fprintf(NewTempFile,Line);
        }

        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundContact == 0){
        printf("Contact Not Found!\n");
        remove("temp-file.txt");
    }else{
        printf("\nContact Updated Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBack();
}

void Delete(void)   //Delete Contact
{

    system("cls");
    tab;printf("\n**** Delete Contact ****\n\n");

    int lineCount = 0;
    int FoundTheContact = 0;
    int SkipLines = 0;
    char GivenName[100];
    printf("\n*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to delete: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("All-Contact.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile)) {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0){
            // we found the contact
            FoundTheContact = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            SkipLines--;
        }else{
            fprintf(NewTempFile,line);
        }

        if(lineCount == 3){
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheContact == 0){
        printf("\nContact Not Found!\n\n");
        remove("temp-file.txt");
    }else{
        printf("\nContact Deleted Successfully!\n\n");
        remove("All-Contact.txt");
        rename("temp-file.txt", "All-Contact.txt");
    }
    GoBack();
}

void DeleteAll(void)    //Delete All Contacts
{
    system("cls");
    printf("\n\t\t **** Delete All The Contacts ****\n\n");

    char Option;
    getchar();
    printf("Are you sure want to delete all the contacts? (Y,N)?: ");
    scanf("%c",&Option);
    if(Option=='Y' || Option=='y'){
        int i;
        remove("All-Contact.txt");
        FILE *AllContactTxtFile = fopen("All-Contact.txt","a");
        fclose(AllContactTxtFile);

        char Deleting[100] = "Deleting....";
        for(i=0;i<strlen(Deleting);i++){
            printf("%c",Deleting[i]);
            sleep(40);
        }
        printf("\nSuccessfully Deleted All Contacts!\n\n");

    }
    GoBack();
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0;i<10;i++){
        printf(".");
        sleep(500);
    }
    system("cls");
    Menu();
}

void GoBack(void)
{
    char op;
    getchar();
    printf("Press (b) to Go Back : ");
    scanf("%c",&op);
    if(op=='b')
        {
        system("cls");
        }


}

void Guide(void){
    system("cls");
    tab;printf("======================================================\n");
    tab;printf("        User Guideline\n                       ");
    tab;printf("======================================================\n");
    tab;printf("   * This Program is created using C Language.\n");
    tab;printf("   * Name, Phone and email should be unique.\n");
    tab;printf("   * Maximum length of name is 20 characters.\n");
    tab;printf("   * Maximum length of phone is 20 characters.\n");
    tab;printf("   * Maximum length of email is 30 characters.\n");
    tab;printf("=======================================================\n");

    GoBack();
}
