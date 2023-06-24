void spalsh (void)
{
      {

       printf("  11        11   2222222     33            444444         55        6       6   7777777   \n");
       printf("  11        11   2222222     33           4     4       5    5      6 6   6 6   77      \n");
       printf("  11        11   22          33           4            5      5     6   6   6   77     \n");
       printf("  11        11   22          33           4           5        5    6       6   777777      \n");
       printf("  11        11   2222222     33           4           5        5    6       6   77      \n");
       printf("  11   11   11   22          33           4      4     5      5     6       6   77      \n");
       printf("  11 11  11 11   22          3333333       4    4       5   5       6       6   7777777       \n");
       printf("  11        11   2222222     33333333       444          55         6       6   7777777     \n");
      }
      sleep(2);
      system("cls");

      char AppStarting[100] = "Application is Starting....";
      for(int i=0;i<strlen(AppStarting);i++)
        {
        printf("%c",AppStarting[i]);
        Sleep(40);
        }
    system("cls");

}
