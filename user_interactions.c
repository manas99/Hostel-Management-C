
void UIdisplayMenu(){
    char con;
    struct user u;
    int check2, block, floor_, room;
    char user_name[100], disp_str[500];
    displayTitle("Database interactions:\n");
    printf("\ta.  \u2014  Add a User\n");
    printf("\tb.  \u2014  Remove a User\n");
    printf("\tc.  \u2014  Search for a User\n");

    printf("\n\tEnter command: ");
    scanf(" %c", &con);

    switch (con) {
        case 'a':
            printf("\t\tEnter Name of the User to add: ");
            scanf(" %[^\n]s", u.name);
            printf("\t\tEnter block no.: ");
            scanf("%d", &u.block);
            printf("\t\tEnter floor no.: ");
            scanf("%d", &u.floor_);
            printf("\t\tEnter room no.: ");
            scanf("%d", &u.room);
            check2 = addUser(u);
            if(check2==1){
                displaySuccess("\n\t\tName added successfully\n");
            }else{
                displayError("\n\t\tError while adding\n");
            }
            endProcess();
            break;

        case 'b':
            printf("\t\tEnter Username to be deleted: ");
            scanf(" %[^\n]s", user_name);
            check2 = alert("\n\t\tAre you sure you want to delete this Username? ");
            if(check2==1){
                if(removeUser(user_name)==1){
                    displaySuccess("\n\t\tUser Deleted successfully.\n");
                }else{
                    displayError("\n\t\tAn error occured.\n");
                }
            }else{
                printf("\n\t\tDelete operation cancelled.\n");
            }
            endProcess();
            break;

		case 'c':
			printf("\t\tEnter Username to be searched: ");
            scanf(" %s", user_name);
            u = searchUser(user_name);
			if(strcmp(u.name, "none") != 0){
                sprintf(disp_str, "\n\t\tUser found successfully.\n\t\tBlock: %d\n\t\tFloor: %d\n\t\tRoom: %d\n", u.block, u.floor_, u.room);
                displaySuccess(disp_str);
            }else{
                displayError("\n\t\tNo User found\n");
            }
            endProcess();
            break;
   }
}
