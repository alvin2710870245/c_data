#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

int schedule[400];             
int head_position = 0;

void diskTrackCreate(void);
int FCFS(void);
int SSTF(void);
void swap(int *a, int *b);
void BubbleSort(int *num, int len);
int LOOK(void);
int C_SCAN(void);

int main(int argc, char *argv[])
{   
    diskTrackCreate();
    printf("\r\n");

    int fcfs = FCFS();
    printf("FCFS track head movement times: %d\n", fcfs);
    printf("FCFS track head movement average times: %.4f\n", fcfs*1.0/400);
    printf("\r\n");

    int sstf = SSTF();
    printf("SSTF track head movement times: %d\n", sstf);
    printf("SSTF track head movement average times: %.4f\n", sstf*1.0/400);
    printf("\r\n");

    int look = LOOK();
    printf("LOOK track head movement times: %d\n", look);
    printf("LOOK track head movement average times: %.4f\n", look*1.0/400);
    printf("\r\n");

    int c_scan = C_SCAN();
    printf("C_SCAN track head movement times: %d\n", c_scan);
    printf("C_SCAN track head movement average times: %.4f\n", c_scan*1.0/400);

    while(1);
    exit(0);
}


void diskTrackCreate(void){
    srand(time(NULL));
    head_position = rand() % 1500;
    printf("magnetic head position = %d\n", head_position);
    int index = 0;
    int val = 0;
    int i;
    int flag1 = 0, flag2 = 0, flag3 = 0;
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    while(flag1 == 0 || flag2 == 0 || flag3 == 0){
        index = rand() % 400;
        if(schedule[index] == 0){
            if(cnt1 <= 199 && flag1 == 0){
                val = rand() % 500;
                if(val == 0){
                    schedule[index] = 1;
                }
                else{
                    schedule[index] = val;
                }
                cnt1++;
                if(cnt1 == 200){
                    flag1 = 1;
                }
                goto check;
            }
            if(cnt2 <= 99 && flag2 == 0){
                schedule[index] = rand() % 500 + 500;
                cnt2++;
                if(cnt2 == 100){
                    flag2 = 1;
                }
                goto check;
            }
            if(cnt3 <= 99 && flag3 == 0){
                schedule[index] = rand() % 500 + 1000;
                cnt3++;
                if(cnt3 == 100){
                    flag3 = 1;
                }
                goto check;
            }
        }
        else{
            for(i = 0; i < 400 && schedule[i] == 0; i++){
                if(flag1 == 0){
                    schedule[i] = rand() % 500;
                    cnt1++;
                    goto check;
                }
                if(flag2 == 0){
                    schedule[i] = rand() % 500 + 500;
                    cnt2++;
                    goto check;
                }
                if(flag3 == 0){
                    schedule[i] = rand() % 500 + 1000;
                    cnt3++;
                    goto check;
                }
            }
        }
        check:
        if(flag1 == 1 && flag2 == 1 && flag3 == 1){
            break;  
        }
    }

    printf("-----------------Create 400 Disk Track Number---------------\r\n");
    for(i = 0; i <= 399; i++){
        printf("%d\t", schedule[i]);
        if((i + 1) % 8 == 0){
            printf("\r\n");
        }
    }
}

int FCFS(void){
    int diskTrackNumber = 0;
    int temp = head_position;
    int i;
    printf("magnetic head position = %d\n", head_position);
    printf("----------------FCFS disk Track Access Order----------------\n");
    for(i = 0; i < 400; i++){
        printf("%d\t", schedule[i]);
        if((i + 1) % 8 == 0){
            printf("\r\n");
        }
        diskTrackNumber += abs(temp - schedule[i]);
        temp = schedule[i];
    }
    printf("\r\n");
    return diskTrackNumber;
}

int SSTF(void){
    int diskTrackNumber = 0;
    int temp = head_position;
    int index = 0;
    int min = 0;
    int i, j;
    int compare[400];
    memset(compare, 0, sizeof(compare));    //一定要清零,分配的栈空间值不是全0
    printf("magnetic head position = %d\n", head_position);
    printf("-----------------SSTF disk Track Access Order---------------\n");
    min = 1500;
    for(i = 0; i < 400; i++){
        for(j = 0; j < 400; j++){
            if(compare[j] == 0 && min >= abs(temp - schedule[j])){
                index = j;
                min = abs(temp - schedule[j]);
            }
            if(min == 0){
                break;
            }
        }
        compare[index] = 1;
        printf("%d\t", schedule[index]);
        if((i + 1) % 8 == 0){
            printf("\r\n");
        }
        diskTrackNumber += min;
        temp = schedule[index];
        min = 1500; 
    }
    printf("\r\n");
    return diskTrackNumber;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(int *num, int len){
    int i, j;
    int flag = 0;
    for(i = 0; i < len - 1; i++){
        for(j = len - 1; j > i; j--){
            if(num[j - 1] > num[j]){
                swap(&num[j], &num[j - 1]);
                flag = 1;
            }
        }
        if(flag == 0){
            return;
        }
    }
}

int LOOK(void){
    int diskTrackNumber = 0;
    int i, j;
    int temp = head_position;
    int *arr = (int*)malloc(sizeof(int)*400);
    int count = 0;
    memset(arr, 0, 400*4);
    memcpy(arr, schedule, 400*4);
    BubbleSort(arr, 400);
    printf("magnetic head position = %d\n", head_position);
    printf("-----------------LOOK disk Track Access Order---------------\n");
    for(i = 0; i < 400; i++){
        if(arr[i] > head_position){
            count++;
            printf("%d\t", arr[i]);
            diskTrackNumber += abs(temp - arr[i]);
            temp = arr[i];
            if(count % 8 == 0){//打印换行符printf("\r\n")不要放到if语句外面，要不然会打出会多空行，因为count开始默认为0
                printf("\n"); 
            }
        }  
        
    }
    for(i = 399; i >= 0; i--){
        if(arr[i] < head_position){
            count++;
            printf("%d\t", arr[i]);
            diskTrackNumber += abs(temp - arr[i]);
            temp = arr[i];
            if(count % 8 == 0){
                printf("\n");
            }
        }  
    }
    printf("\r\n");
    free(arr);
    return diskTrackNumber;
}

int C_SCAN(void){
    int i, j;
    int diskTrackNumber = 0;
    int temp = head_position;
    int *arr = (int*)malloc(sizeof(int)*400);
    int count = 0;
    memset(arr, 0, 400*4);
    memcpy(arr, schedule, 400*4);
    BubbleSort(arr, 400);
    printf("magnetic head position = %d\n", head_position);
    printf("----------------C_SCAN disk Track Access Order--------------\n");
    for(i = 0; i < 400; i++){
        if(arr[i] > head_position){
            count++;
            printf("%d\t", arr[i]);
            diskTrackNumber += abs(temp - arr[i]);
            temp = arr[i];
            if(count % 8 == 0){//打印换行符printf("\r\n")不要放到if语句外面，要不然会打出会多空行，因为count开始默认为0
                printf("\n"); 
            }
        } 
    }
    temp = 0;
    for(i = 0; i < 400; i++){
        if(arr[i] < head_position){
            count++;
            printf("%d\t", arr[i]);
            diskTrackNumber += abs(temp - arr[i]);
            temp = arr[i];
            if(count % 8 == 0){//打印换行符printf("\r\n")不要放到if语句外面，要不然会打出会多空行，因为count开始默认为0
                printf("\n"); 
            }
        } 
    }
    printf("\r\n");
    free(arr);
    return diskTrackNumber;
}