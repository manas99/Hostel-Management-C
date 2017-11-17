void STdisplayMenu(){
    char con;
    struct user e;
    int check,block, floor_, room,block1,floor_1,room1,flag = 0;
    FILE *fp;
    char tmp[256], uname[100],error[50];
    displayTitle("User statistics:\n");
    printf("\ta.  \u2014  Total no. of people\n");
    printf("\tb.  \u2014  Total no. of people in a specific room\n");
    printf("\tc.  \u2014  Total no. of people on a specific floor\n");
    printf("\td.  \u2014  Total no. of people in a specific block\n");
    printf("\n\tEnter command: ");
    scanf(" %c", &con);
    switch(con){
        case 'a':
            printf("\t\tAll the people present\n");

            fp = fopen("./db/user.db","r+");
            rewind(fp);
            while (1) {
                check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block, &floor_, &room);
                if(check==4){
                    printf("\t\t\tName:");
                    printf("%s\n",uname);
                    printf("\t\t\t\tblock:%d\n\t\t\t\tfloor:%d\n\t\t\t\troom:%d\n",block,floor_,room);
                }
                if(check==EOF){
                    fclose(fp);
                    break;
                }
            }
            endProcess();
            break;
        case 'b':
            printf("\t\tEnter block no.:");
            scanf("%d",&block);
            printf("\t\tEnter floor no.:");
            scanf("%d",&floor_);
            printf("\t\tEnter room no.:");
            scanf("%d",&room);
            fp = fopen("./db/user.db","r+");
            rewind(fp);
            while (1) {
                check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block1, &floor_1, &room1);
                if(check==4){
                    if(block==block1&&floor_==floor_1&&room==room1){
                        printf("\t\t\tName:");
                        printf("%s\n",uname);
                            flag = 1;
                        }
                        else if(flag!=1){
                            printf("\t\t\tNo people present\n");
                        }
                }
                if(check==EOF){
                    fclose(fp);
                    break;
                }
            }
            endProcess();
            break;
        case 'c':
            printf("\t\tEnter block no.:");
            scanf("%d",&block);
            printf("\t\tEnter floor no.:");
            scanf("%d",&floor_);
            fp = fopen("./db/user.db","r+");
            rewind(fp);
            while (1) {
                check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block1, &floor_1, &room1);
                if(check==4){
                    if(block==block1&&floor_==floor_1){
                        printf("\t\t\tName:");
                        printf("%s\n",uname);
                        flag = 1;
                        }
                        else if(flag!=1){
                            printf("\t\t\tNo people present\n");
                        }
                    }
                    if(check==EOF){
                        fclose(fp);
                        break;
                    }
                }
                endProcess();
            break;
        case 'd':
            printf("\t\tEnter block no.:");
            scanf("%d",&block);
            fp = fopen("./db/user.db","r+");
            rewind(fp);
            while (1) {
                check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block1, &floor_1, &room1);
                if(check==4){
                    if(block==block1){
                        printf("\t\t\tName:");
                        printf("%s\n",uname);
                        flag = 1;
                        }
                        else if(flag!=1){
                            printf("\t\t\tNo people present\n");
                        }
                    }
                    if(check==EOF){
                        fclose(fp);
                        break;
                    }
                }
                endProcess();
            break;
	default:
		displayError("\n\t\tInvalid Input\n");
		endProcess();
		break;
    }
}
