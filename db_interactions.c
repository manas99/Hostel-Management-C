

void DBIdisplayMenu(){
    char cond;
    int block_name, floor_name, room_name, check1;
    displayTitle("Database interactions:\n");
    printf("\ta.  \u2014  create new block\n");
    printf("\tb.  \u2014  add a new floor to existing block\n");
    printf("\tc.  \u2014  add a new room to existing block\n");
    printf("\td.  \u2014  remove an existing block\n");
    printf("\te.  \u2014  remove an existing floor from an existing block\n");
    printf("\tf.  \u2014  remove a room from an existing floor and existing block\n");
    printf("\n\tEnter command: ");
    scanf(" %c", &cond);
    switch (cond) {
        case 'a':
            printf("\t\tEnter block number to add: ");
            scanf("%d", &block_name);
            check1 = addBlock(block_name);
            if(check1==1){
                displaySuccess("\n\t\tBlock added successfully\n");
            }else{
                displayError("\n\t\tBlock already exists\n");
            }
            endProcess();
            break;
        case 'b':
            printf("\t\tEnter block number in which the floor is to be added: ");
            scanf("%d", &block_name);
            printf("\t\tEnter floor number: ");
            scanf("%d", &floor_name);
            check1 = addFloor(block_name, floor_name);
            if(check1==1){
                displaySuccess("\n\t\tFloor added successfully.\n");
            }else{
                displayError("\n\t\tAn error occured.\n");
            }
            endProcess();
            break;
        case 'c':
            printf("\t\tEnter block number in which the floor is to be added: ");
            scanf("%d", &block_name);
            printf("\t\tEnter floor number to which room has to be added: ");
            scanf("%d", &floor_name);
            printf("\t\tEnter new room number: ");
            scanf("%d", &room_name);
            check1 = addRoom(block_name, floor_name, room_name);
            if(check1==1){
                displaySuccess("\n\t\tRoom added successfully.\n");
            }else{
                displayError("\n\t\tAn error occured.\n");
            }
            endProcess();
            break;
        case 'd':
            printf("\t\tEnter block number to be deleted: ");
            scanf("%d", &block_name);
            check1 = alert("\n\t\tAre you sure you want to delete this block? ");
            if(check1==1){
                if(removeBlock(block_name)==1){
                    displaySuccess("\n\t\tDeleted block successfully.\n");
                }else{
                    displayError("\n\t\tAn error occured.\n");
                }
            }else{
                printf("\n\t\tDelete operation cancelled.\n");
            }
            endProcess();
            break;
        case 'e':
            printf("\t\tEnter block from which the floor is to be deleted: ");
            scanf("%d", &block_name);
            printf("\t\tEnter floor number to be deleted: ");
            scanf("%d", &floor_name);
            check1 = alert("\n\t\tAre you sure you want to delete this floor? ");
            if(check1==1){
                if(removeFloor(block_name, floor_name) == 1){
                    displaySuccess("\n\t\tDeleted floor successfully.\n");
                }else{
                    displayError("\n\t\tAn error occured.\n");
                }
            }else{
                printf("\n\t\tDelete operation cancelled.\n");
            }
            endProcess();
            break;
        case 'f':
            printf("\t\tEnter block from which the room is to be deleted: ");
            scanf("%d", &block_name);
            printf("\t\tEnter floor from which the room is to be deleted: ");
            scanf("%d", &floor_name);
            printf("\t\tEnter the room number to be deleted: ");
            scanf("%d", &room_name);
            check1 = alert("\n\t\tAre you sure you want to delete this room? ");
            if(check1==1){
                if(removeRoom(block_name, floor_name, room_name) == 1){
                    displaySuccess("\n\t\tDeleted room successfully.\n");
                }else{
                    displayError("\n\t\tAn error occured.\n");
                }
            }else{
                printf("\n\t\tDelete operation cancelled.\n");
            }
            endProcess();
            break;
    }
}
