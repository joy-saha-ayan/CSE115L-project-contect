#include <string.h>
void login(void)
{
    FILE *fp;
    char name[50], fname[50];
    char pin[15], fpin[15];
    printf("=================\n");
    printf("    ~Login~\n");
    printf("=================\n");

    do {
        fp = fopen("test.txt", "r");

        printf("Name: ");
        scanf("  %[^\n]s", name);

        printf("Password: ");
        scanf(" %[^\n]s",pin);

        getchar();

        fscanf(fp, "%s ", fname);
         fscanf(fp, "%s ", fpin);
        if ((strcmp(name, fname) == 0) && (strcmp(pin, fpin) == 0)){
            printf("You have successfully logged in!\n");
            fclose(fp);
        } else {
            printf("The information you gave is incorrect. Try again... \n");
        }
    } while ((strcmp(name, fname) != 0) || (strcmp(pin, fpin)!=0));
}
void create(void)
{
    FILE *fp;
    char name[50];
    char pin[15];

     int length;
    fp = fopen("test.txt", "w");

    printf("\nEnter your name: ");
    scanf(" %[^\n]s",name);
    fprintf(fp, "%s\n", name);

    printf("Enter a numerical password: ");
    scanf(" %s",pin);

    getchar();
    fprintf(fp, "%s ", pin);

    printf("\nYour new account has been created! Use your info to login!\n");

    fclose(fp);

    login();
}
