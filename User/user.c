#include "user.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void saveUser(User *u[], int count){
    FILE *data;
    data = fopen("user.txt", "w");
    for(int i=0; i<count; i++){
        fprintf(data,"%s %s %s %s\n", u[i]->id, u[i]->password, u[i]->phoneNumber, u[i]->userName);
    }
    printf("저장되었습니다.\n");
    fclose(data);
}

int loadUser(User *u[]){
    FILE *data;
    int i = 0;
    data = fopen("user.txt", "r");
    while(!feof(data)){
        if(fscanf(data, "%s %s %s %s",u[i]->id, u[i]->password, u[i]->phoneNumber, u[i]->userName)!=4) break;
        i++;
    }
    fclose(data);
    return i;
}

void withdrawal(User *u[], int count){
    char id[11];
    char password[13];
    bool id_check = false;
    bool password_check = false;
    int id_location;

    printf("------------Withdrawal------------\n");
    printf("삭제하려는 계정의 아이디: ");
    getchar();
    scanf("%[^\n]s", id);
    if(strcmp(id, "-1")==0){
        printf("찾으시는 아이디가 없습니다.\n");
        return;
    }
    for(int i=0; i<count; i++){
        if(strcmp(u[i]->id, id)==0){
            id_check = true;
            id_location = i;
            break;
        }
    }
    if(id_check==false){
        printf("찾으시는 아이디가 없습니다.\n");
        return;
    }
    else{
        printf("삭제하려는 계정의 비밀번호: ");
        getchar();
        scanf("%[^\n]s", password);
        if(strcmp(u[id_location]->password, password)==0) {
            strcpy(u[id_location]->id, "-1");
            password_check = true;
        }
        if(password_check==false){
            printf("틀린 비밀번호입니다.\n");
            return;
        }
        else {
            printf("삭제되었습니다.\n");
            saveUser(u, count);
        }
    }
}

int signUp(User *u[], int count){
    bool check_blank;
    char id[11];
    char password[13];
    char phoneNumber[12];
    char userName[30]; 

    printf("------------Sign Un------------\n");
    printf("각 단계에서 회원가입을 취고하시려면 -1을 입력해주세요.\n");
    while(1){
        check_blank = false;
        printf("1. 아이디(10글자 이내, 띄어쓰기 미포함): ");
        getchar();
        scanf("%[^\n]s", id);
        if(strcmp(id,"-1")==0) return count;
        if(strlen(id)>10){
            printf("10글자 초과입니다. 다시 시도해주세요.\n");
            continue;
        }
        for(int i=0; i<strlen(id); i++){
            if(id[i] == ' '){
                printf("띄어쓰기가 되어 있습니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
        }
        for(int i=0; i<count; i++){
            if(strcmp(u[i]->id, id)==0){
                printf("중복된 아이디입니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
        }
        if(check_blank==true) continue;
        else break;
    }

    while(1){
        check_blank = false;
        printf("2. 비밀번호(12글자 이내, 띄어쓰기 미포함): ");
        getchar();
        scanf("%[^\n]s", password);
        if(strcmp(password,"-1")==0) return count;
        if(strlen(password)>12){
            printf("12글자 초과입니다. 다시 시도해주세요.\n");
            continue;
        }
        for(int i=0; i<strlen(password); i++){
            if(password[i] == ' '){
                printf("띄어쓰기가 되어 있습니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
        }
        if(check_blank==true) continue;
        else break;
    }

    while(1){
        check_blank = false;
        printf("3. 전화번호(-없이 숫자만, 띄어쓰기 미포함): ");
        getchar();
        scanf("%[^\n]s", phoneNumber);
        if(strcmp(phoneNumber,"-1")==0) return count;
        /*if(strlen(password)!=11){
            printf("11글자 초과, 미만 혹은 '-'이나 띄어쓰기가 포함되어 있습니다. 다시 시도해주세요.\n");
            continue;
        }
        else break;*/
        for(int i=0; i<strlen(phoneNumber); i++){
            if(phoneNumber[i] == ' '){
                printf("띄어쓰기가 되어 있습니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
            if(phoneNumber[i] == '-'){
                printf("-이 포함되어있습니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
            if(!isdigit(phoneNumber[i])){
                printf("숫자가 아닙니다. 다시 시도해주세요.\n");
                check_blank = true;
                break;
            }
        }
        if(check_blank==true) continue;
        else break;
    }

    printf("이름: ");
    getchar();
    scanf("%[^\n]s", userName);
    if(strcmp(userName,"-1")==0) return count;

    strcpy(u[count]->id, id);
    strcpy(u[count]->password, password);
    strcpy(u[count]->phoneNumber, phoneNumber);
    strcpy(u[count]->userName, userName);

    count++;
    printf("\n회원가입이 완료되었습니다.\n");
    saveUser(u, count);
    return count;
}

int signIn(User *u[], int count){
    char id[11];
    char password[13];
    bool id_check = false;
    bool password_check = false;

    printf("------------Sign In------------\n");
    printf("아이디: ");
    scanf("%s", id);
    for(int i=0; i<count; i++){
        if(strcmp(u[i]->id,id)==0){
            id_check = true;
            break;
        }
    }
    if(id_check == false){
        printf("잘못되거나 없는 아이디입니다.\n");
        return 0;
    }
    else{
        printf("비밀번호: ");
        scanf("%s", password);
        for(int i=0; i<count; i++){
            if(strcmp(u[i]->password,password)==0){
            password_check = true;
            break;
            }
        }
    }
    if(password_check==false){
        printf("잘못된 비밀번호입니다.\n");
        return 0;
    }
    else printf("로그인되었습니다.\n");
    return 1;
}

int userMenu(){
    int menu;
    printf("\n*** 유저 시스템 ***\n");
    printf("1. 로그인\n");
    printf("2. 회원 가입\n");
    printf("3. 회원 탈퇴\n");
    printf("0. 종료\n\n");
    printf("메뉴 선택: ");
    scanf("%d", &menu);
    return menu;
}