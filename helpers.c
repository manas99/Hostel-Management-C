

#if defined(_WIN32)
    const char* os = "win";
#elif defined(__unix)
    const char* os = "unix";
#else
    const char* os = "unknown";
#endif

void clear(){
    if(strcmp(os, "win")){
        system("cls");
    }
    if(strcmp(os, "unix")){
        system("clear");
    }
}

int checkIfDirExists(char* dirname){
    DIR* dir = opendir(dirname);
    if(dir){
        closedir(dir);
        return 1;
    }else if(ENOENT == errno){
        return 0;
    }
    return 0;
}

int removeDir(char *str){
    char name[200];
    if(checkIfDirExists(str) == 1){
        sprintf(name, "rm -rf %s/",str);
        if(strcmp(os, "unix")){
            system(name);
            return 1;
        }
    }
    return 0;
}

int removeFile(char *str){
    int ret;
    ret = remove(str);
    if(ret == 0){
        return 1;
    }else{
        return 0;
    }
}

void endProcess(){
    printf("\n--------------------------------------------------------------------------------------\n\n");
}

void displayTitle(char* str){
    printf("\x1b[4;1m");
    printf("%s", str);
    printf("\x1b[0m");
}

void displayError(char* str){
    printf("\x1b[1;31m");
    printf("%s", str);
    printf("\x1b[0m");
}

void displaySuccess(char* str){
    printf("\x1b[1m");
    printf("%s", str);
    printf("\x1b[0m");
}

int alert(char *dispStr){
    char char_;
    printf("\x1b[1;33m");
    printf("%s: Y/n? ", dispStr);
    scanf(" %c", &char_);
    printf("\x1b[0m");
    if(char_ == 'Y'){
        return 1;
    }else if(char_ == 'n'){
        return 0;
    }
    return alert(dispStr);
}
