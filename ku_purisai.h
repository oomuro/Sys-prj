#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct dot {
    int x;
    int y;
    struct dot *next;
} dot;

typedef struct result {
    int x1;
    int y1;
    int x2;
    int y2;
    float dist;
    struct result *next;
} result;

result calc_dist(dot *a, dot *b) {
    long powers = (long) (a->x - b->x) * (long) (a->x - b->x) + (long) (a->y - b->y) * (long) (a->y - b->y);
//    printf("result_ld = %ld ", powers);
//    printf("result_lf = %lf ", (double) powers);
    float result = (float) sqrt((double) powers);
//    printf("%d %d %d %d sqrt = %f\n", a->x, a->y, b->x, b->y, result);

    struct result rs;
    rs.x1 = a->x;
    rs.x2 = b->x;
    rs.y1 = a->y;
    rs.y2 = b->y;
    rs.dist = result;
    return rs;
}

result *calc_result(dot *d, int index, int *dup) {
    result *rs;
    rs = malloc(sizeof(result));
    memset(rs, 0, sizeof(result));
    int possible = (index * (index - 1)) / 2; // 주어진 점집합에 대해 가능한 경우의 수
    int a = 0, b = 1;
//    printf("possible = %d\n", possible);
    for (int i = 0; i < possible; i++) {
//        printf("a , b = %d, %d\n", a, b);

        if ((*dup) == 0) {
            rs[*dup] = calc_dist(&d[a], &d[b]);
            (*dup)++;
        } // 첫번째 값은 무조건 입력
        else {
            if (rs[*dup - 1].dist > calc_dist(&d[a], &d[b]).dist) {
                rs[*dup - 1] = calc_dist(&d[a], &d[b]);
            } else if (rs[*dup - 1].dist == calc_dist(&d[a], &d[b]).dist) {
                rs = realloc(rs, sizeof(result) * (*dup + 1));
                memset(rs + 1, 0, sizeof(result));
                rs[*dup] = calc_dist(&d[a], &d[b]);
                (*dup)++;
            }
        }

        b++;
        if (b == index) {
            a++;
            b = a + 1;
        }
    }

//    printf("%d\n", *dup);

    return rs;
} // 주어진 점집합에 대해 최소의 거리 계산