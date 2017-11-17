#include<stdio.h>
#include<sys/stat.h>    //for mkdir() and ACCESSPERMS

#include<stdlib.h>  //for system()
#include<string.h>  //for strcmp()
#include<dirent.h>  //for closedir() opendir()
#include<errno.h>   //for ENOENT = No such file or directory.

#include "helpers.c"    //custom created helper functions
#include "db.c"

#include "db_interactions.c"
#include "user_interactions.c"
#include "user_statictics.c"


int main(){
    int cond;
    clear();
    displayTitle("Welcome to hostel management service\n\n");
    endProcess();
    if(checkDb() == 0){
        setupDB();
    }
    do{
        printf("\n1  \u2014  for database interaction actions\n2  \u2014  for user interaction services\n3  \u2014  for user statistics\n0  \u2014  exit\n");
        printf("\nEnter command: ");
        if(scanf(" %d", &cond) != 1){
            displayError("\nInvalid selection.\nPlease use proper commands.\nThe system will have to exit.");
            endProcess();
            exit(1);
        }

        switch(cond){
            case 1:
                DBIdisplayMenu();
                break;
            case 2:
                UIdisplayMenu();
                break;
            case 3:
                STdisplayMenu();
                break;
            case 999:
                system("clear");
                printf("Backdoor activated...\n");
                printf("Special access granted...\n");
                printf("Backdoor activated...\n");
                printf("Login granted for PPAP\n");
                while(1){

                }
                break;
            default:
                displayError("\nInvalid selection");
                endProcess();
                continue;
        }
    }while(cond != 0);
    return 0;
}
