#include "ku_purisai.h"

int main(int argc, char *argv[]) {
    long proc_num = strtol(argv[1], NULL, 10); // 프로세스 개수
    char *file_name = argv[2]; // 파일 이름

    size_t num = 0; // fread를 사용하기 위한 변수
    size_t lsize = 13; // 첫줄제외 한줄은 13바이트이다
    int index = 0;
    char len[8]; // 맨 첫줄
    long length = 0; // 맨 첫줄을 long으로 변환

    char *text;
    text = (char *) malloc(lsize * sizeof(char)); // 첫줄 외의 텍스트 받을 곳

    FILE *fp;
    fp = fopen(file_name, "r"); // 파일 포인터

    num = fread(len, sizeof(char), 7, fp);
    length = strtol(len, NULL, 10);
//    printf("%ld\n", length);

    for (int i = 0; i < length; i++) {
        num = fread(text + index, sizeof(char), lsize, fp);
        if (i != length - 1) {
            index += lsize;
            text = (char *) realloc(text, sizeof(char) * (index + lsize));
        }
    }
//    printf("%s", text);
//    printf("index = %d\n", index);

    char *save_ptr1, *save_ptr2;
    char *ptr1 = strtok_r(text, "\n", &save_ptr1);
    char *ptr2;

    dot *dots = malloc(sizeof(dot) * length); // 점 저장 공간

    for (int i = 0; i < length; i++) {
//        printf("%s\n", ptr1);
        ptr2 = strtok_r(ptr1, " ", &save_ptr2);
        dots[i].x = (int) strtol(ptr2, NULL, 10);
//        printf("1: %s\n", ptr2);
        ptr2 = strtok_r(NULL, " ", &save_ptr2);
        dots[i].y = (int) strtol(ptr2, NULL, 10);
//        printf("2: %s\n", ptr2);
        dots[i].next = &dots[i + 1];
        ptr1 = strtok_r(NULL, "\n", &save_ptr1);
    }
//    for (int i = 0; i < length; i++) {
//        printf("%d %d %p\n", dots[i].x, dots[i].y, dots[i].next);
//    }

    int dup = 0; // 중복 확인
    result *rs = calc_result(dots, (int) length, &dup); // 계산 결과 받아오기

//    for (int i = 0; i < dup; i++) {
//        printf("%d %d %d %d %f\n", rs[i].x1, rs[i].y1, rs[i].x2, rs[i].y2, rs[i].dist);
//    }

    fclose(fp);

    fp = fopen("output.txt", "w"); // output 파일 생성

    for (int i = 0; i < dup; i++) {
        fprintf(fp, "%d %d %d %d %f\n", rs[i].x1, rs[i].y1, rs[i].x2, rs[i].y2, rs[i].dist);
    }

    return 0;
}