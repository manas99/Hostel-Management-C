
#define db_folder "./db"
#define ppl_per_room 3

struct user{
    char name[100];
    int block;
    int floor_;
    int room;
};

int checkDb(){
    if (checkIfDirExists(db_folder) == 0) {
        return 0;
    }else{
        return 1;
    }
}

void createDB(){
    FILE *file;
    mkdir("db", ACCESSPERMS);
    file = fopen("./db/user.db","a");
    fclose(file);
    file = fopen(db_folder, "a");
    fclose(file);
}

void setupDB(){
    FILE *file;
    int blocks, floors, rooms;
    int i, j, k;
    char blockname[100], floorname[100], roomname[100];
    createDB();
    printf("Starting Setup...\n\n");
    printf("Enter number of blocks:\n");
    scanf("%d", &blocks);
    for(i=1;i<=blocks;i++){
        sprintf(blockname, "./db/%d", i);
        mkdir(blockname, ACCESSPERMS);
        printf("Enter number of floors for block no. %d:\n", i);
        scanf("%d", &floors);
        for(j=1;j<=floors;j++){
            sprintf(floorname, "./db/%d/%d", i, j);
            mkdir(floorname, ACCESSPERMS);
            printf("Enter number of rooms for block no. %d and floor number %d:\n", i, j);
            scanf("%d", &rooms);
            for(k=1;k<=rooms;k++){
                sprintf(roomname, "./db/%d/%d/%d.db", i, j, k);
                file = fopen(roomname, "a");
                fclose(file);
            }
        }
    }
    printf("Setup Completed.\n");
    system("clear");
}

int addBlock(int name){
    char filename[100];
    sprintf(filename, "./db/%d", name);
    if(checkIfDirExists(filename) == 0){
        mkdir(filename, ACCESSPERMS);
        return 1;
    }else{
        return 0;
    }
}

int addFloor(int block, int name){
    char filename[100], blockname[100];
    sprintf(blockname, "./db/%d", block);
    sprintf(filename, "./db/%d/%d", block, name);
    if(checkIfDirExists(blockname) == 1){
        if(checkIfDirExists(filename) == 0){
            mkdir(filename, ACCESSPERMS);
            return 1;
        }else{
            return 0;
        }
    }else{
        return 0;
    }
}

int addRoom(int block, int floor_, int name){
    FILE* file;
    char filename[100], floorname[100];
    sprintf(floorname, "./db/%d/%d", block, floor_);
    sprintf(filename, "./db/%d/%d/%d.db", block, floor_, name);
    if(checkIfDirExists(floorname) == 1){
        file = fopen(filename,"r+");
        if(file == NULL){
            file = fopen(filename,"a");
            fclose(file);
            return 1;
        }else{
            fclose(file);
            return 0;
        }
    }else{
        return 0;
    }
}

int removeBlock(int block){
    int check;
    char filename[100];
    sprintf(filename, "./db/%d", block);
    check = removeDir(filename);
    if(check == 1){
        return 1;
    }else{
        return 0;
    }
}

int removeFloor(int block, int floor_){
    int check;
    char filename[100];
    sprintf(filename, "./db/%d/%d", block, floor_);
    check = removeDir(filename);
    if(check == 1){
        return 1;
    }else{
        return 0;
    }
}

int removeRoom(int block, int floor_, int room){
    int check;
    char filename[100];
    sprintf(filename, "./db/%d/%d/%d.db", block, floor_, room);
    check = removeFile(filename);
    return check;
}

int noPeople(int block,int floor_,int room){
    FILE *fp;
    char filename[100];
    char cfile;
    int counter = 0;
    sprintf(filename, "./db/%d/%d/%d.db", block, floor_, room);
    fp = fopen(filename,"r");
    if(fp==NULL){
        return -1;
    }
    while(1){
        cfile = fgetc(fp);
        if(cfile=='\n'){
            counter++;
        }else if(cfile==EOF){
            break;
        }
    }
    fclose(fp);
    return counter;
}

int addUser(struct user u){
	FILE *fp,*ft;
    char filename[100];
    fp = fopen("./db/user.db","a");
    int nop;
    nop = noPeople(u.block,u.floor_,u.room);
    if(nop >= 0 && nop < 3){
        fprintf(fp, "%s,%d,%d,%d\n", u.name, u.block, u.floor_, u.room);
        sprintf(filename, "./db/%d/%d/%d.db", u.block, u.floor_,u.room);
        ft = fopen(filename,"a+");
        fprintf(ft,"%s,\n",u.name);

        fclose(ft);
        fclose(fp);
        return 1;
    }
    return 0;
}

int removeUser(char user_name[]){
	FILE *fp, *ft, *fs, *fm;
    char filename[100], ch, tmp[256];
    char uname[100];
    int block, floor_, room;
    int check, check1, error = 0;

    fp = fopen("./db/user.db", "r");
	ft = fopen("./db/temp.dat", "w");
    rewind(fp);
    while (1) {
        check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block, &floor_, &room);
        if (check == 4) {
            if(strcmp(uname, user_name) != 0){
                sprintf(tmp, "%s,%d,%d,%d\n", uname, block, floor_, room);
                fputs(tmp, ft);
            }else{
                error = 1;
                sprintf(filename, "./db/%d/%d/%d.db", block, floor_, room);
            }
        }
        if (check == EOF) {
            break;
        }
    }
    fclose(fp);
    fclose(ft);
    if(error == 0){
        displayError("\n\t\tUser not found.");
        return 0;
    }
    fs = fopen(filename, "r");
    fm = fopen("./db/temporary.dat","w");
	rewind(fs);
	while (1) {
        check1 = fscanf(fs, "%[^,],\n", uname);
        if (check1 == 1) {
            if(strcmp(uname, user_name) != 0){
                sprintf(tmp, "%s,\n", uname);
                fputs(tmp, fm);
            }
        }
        if (check1 == EOF) {
            break;
        }
    }
	fclose(fs);
    fclose(fm);

    remove("./db/user.db");
    rename("./db/temp.dat", "./db/user.db");

	remove(filename);
    rename("./db/temporary.dat",filename);
	return 1;
}

struct user searchUser(char user_name[]){
    struct user e;
    int check;
	FILE *fp;
    int block, floor_, room;
    char tmp[256], uname[100];

    fp = fopen("./db/user.db","r+");
    rewind(fp);
    while (1) {
        check = fscanf(fp, "%[^,],%d,%d,%d\n", uname, &block, &floor_, &room);
        if (check == 4) {
            if(strstr(uname, user_name) != 0){
                strcpy(e.name, uname);
                e.block = block;
                e.floor_ = floor_;
                e.room = room;
                fclose(fp);
                return e;
            }
        }
        if (check == EOF) {
            break;
        }
    }
    fclose(fp);
    strcpy(e.name, "none");
    return e;
}
