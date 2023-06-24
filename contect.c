



#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
void Menu(void);
void AddNewContact(void);
void ShowAllContacts(void);
void SearchContact(void);
void EditContact(void);
void DeleteContact(void);
void DeleteAllContacts(void);
void ClearWindow(void);
void PrintLineWithSpace(char *Name[20],char ContactInfo);
void ShowPhoneWithSpace(char *Phone[20]);
void ShowEmailWithSpace(char *Email[30]);
void ErrorAndRestart(char *error[100]);
void GoBack(void);
void UserGuideline(void);



void Menu(void)
{
    printf("\n\t **** My-Contact Management System Using C ****\n");
    printf("\n\t\t\tMAIN MENU\n");
    printf("\t\t==============================\n");
    printf("\t\t[1] Add a new Contact\n");
    printf("\t\t[2] Show all Contacts\n");
    printf("\t\t[3] Search for contact\n");
    printf("\t\t[4] Edit a Contact\n");
    printf("\t\t[5] Delete a Contact\n");
    printf("\t\t[6] Delete All Contact\n");
    printf("\t\t[7] Clear Window\n");
    printf("\t\t[8] User Guideline\n");

    printf("\t\t[0] Exit\n\t\t");
    printf("\t\t=================================\n\t\t");
    printf("Enter the choice:");
}

void AddNewContact(){
    system("cls");
    printf("\n\t\t **** Add new Contact ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewContact[100];
    NewContact[0] = 0;
    printf("*Name should be unique and maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    printf("\n*Phone should be unique and maximum 20 characters long.\n");
    printf("Enter The Phone Number: ");
    scanf("  %s",Phone);
    if(strlen(Phone) > 20){
        ErrorAndRestart("!!!!Phone Length Error!!!!");
        return;
    }

    printf("\n*Email should be unique and maximum 30 characters long.\n");
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
    printf("\nContact Added Successfully!\n");
    GoBack();
}

void ShowAllContacts(void){
    system("cls");
    printf("\n\t\t **** All Contacts ****\n\n");
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
            PrintLineWithSpace(Line,'n');
        }else if(LineCount == 2){
            // phone
           PrintLineWithSpace(Line,'p');
        }else if(LineCount == 3){
            // email
            PrintLineWithSpace(Line,'e');
            LineCount=0;
            TotalContact++;
        }
    }
    printf("You Have Total %d Contacts.\n\n",TotalContact);
    fclose(AllContactTextFile);
    GoBack();
}

void PrintLineWithSpace(char *Name[20],char ContactInfo){
    int i;
    char *FormatedName = NULL;
    FormatedName = strdup(Name);
    int FormatedNameLenght = strlen(FormatedName);

    int TotalSpace = 0;
    if(ContactInfo == 'n'){
        TotalSpace = 20 - FormatedNameLenght; // name
    }else if(ContactInfo == 'p'){
        TotalSpace = 20 - FormatedNameLenght; // phone
    }else if(ContactInfo == 'e'){
        TotalSpace = 30 - FormatedNameLenght; // email
    }

    printf("|");
    for(i=0;i<FormatedNameLenght-1;i++){
        printf("%c",FormatedName[i]);
    }

    for(i=0;i<=TotalSpace;i++){
        printf(" ");
    }

    if(ContactInfo == 'e'){
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

void SearchContact(void){
    system("cls");
    printf("\n\t\t **** Search Contact ****\n\n");

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

void EditContact(void){
    system("cls");
    printf("\n\t\t **** Edit Contact ****\n\n");

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
                printf("\n*New Name should be unique and maximum 20 characters long.\n");
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
                printf("\n*New Phone should be unique and maximum 20 characters long.\n");
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
                printf("\n*New Email should be unique and maximum 30 characters long.\n");
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

void DeleteContact(void){

    system("cls");
    printf("\n\t\t **** Delete Contact ****\n\n");

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

void DeleteAllContacts(void){
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
            Sleep(40);
        }
        printf("\nSuccessfully Deleted All Contacts!\n\n");

    }
    GoBack();
}

void ErrorAndRestart(char *error[100]){
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0;i<10;i++){
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void GoBack(void){
    char op;
    getchar();
    printf("Go Back(b): ");
    scanf("%c",&op);
    if(op=='b')
        {
        system("cls");
        }


}

void UserGuideline(void){
    system("cls");
    printf("\n\t\t **** My-Contact Management System ****\n");
    printf("\n\n\n\t\t\tUser Guideline\n");
    printf("\t\t===============================================\n");
    printf("\t\t[>] This Program is created using C Language.\n");
    printf("\t\t[>] Name, Phone and email should be unique.\n");
    printf("\t\t[>] Maximum length of name is 20 characters.\n");
    printf("\t\t[>] Maximum length of phone is 20 characters.\n");
    printf("\t\t[>] Maximum length of email is 30 characters.\n");
    printf("\t\t===============================================\n\t\t");

    GoBack();
}

