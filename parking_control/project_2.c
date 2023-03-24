#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 주차장 정보를 담을 구조체 구현
typedef struct _parking_t
{
    char name[100];
    char agency[100];
    char city[100];
    char district[100];
    double longitude;
    double latitude;
} parking_t;

// 배열리스트 구조체 구현
typedef struct _parking_list_t
{
    int len;
    parking_t* parkings;
} parking_list_t;

// utils_t 구조체 구현
typedef struct _utils_t
{
    void (*sort)   (parking_list_t*);
    void (*print)  (parking_list_t*);
    int  (*sorted) (parking_list_t*);
} utils_t;

/* Array List */
int array_list_create(parking_list_t** list);
int array_list_destroy(parking_list_t** list);
int array_list_insert_last(parking_list_t* list, parking_t e);

/* Sort */
void selection_sort(parking_list_t* list);
void insertion_sort(parking_list_t* list);

void my_print(parking_list_t* list);
void my_sort(parking_list_t* list);
int  is_sorted(parking_list_t* list);

/* Filter */
parking_list_t* my_filter(parking_list_t* plist);

int main(int argc, char** argv)
{
    parking_list_t* plist = (parking_list_t*)malloc(sizeof(parking_list_t*) * 1);
    array_list_create(&plist);
    parking_t for_input;
    char str_tmp[1024]; char* p;
    FILE* pfile = NULL;
    const char* fname = "free_parcking_spot-small.csv";

    int op;

    utils_t my_util;
    my_util.sort = my_sort;
    my_util.print = my_print;

    pfile = fopen(fname, "r");
    if (pfile != NULL)
    {
        fgets(str_tmp, 1024, pfile);
        while (!feof(pfile))
        {
            fgets(str_tmp, 1024, pfile);

            // 1.자원명(str) 2.관리기관구분(str) 3.시도(str) 4.군구(str) 5.경도(double) 6.위도(double)
            char copy_str[1024];
            strcpy(copy_str, str_tmp);
            p = strtok(copy_str, ",");
            strcpy(for_input.name, p);
            p = strtok(NULL, ",");
            strcpy(for_input.agency, p);
            p = strtok(NULL, ",");
            strcpy(for_input.city, p);
            p = strtok(NULL, ",");
            strcpy(for_input.district, p);
            p = strtok(NULL, ",");
            for_input.longitude = strtod(p, NULL);
            p = strtok(NULL, ",");
            for_input.latitude = strtod(p, NULL);

            array_list_insert_last(plist, for_input);
        }
        fclose(pfile);
        printf("Stored all elements\n");
    }
    else  // 비어있다면
    {
        printf("Cannot open the file free_parcking_spot-small.csv\n");
        return 0;
    }

    while (true)
    {
        printf("====== Choose function ======\n");
        printf("(1) sort\n(2) print\n(3) filter\n(4) exit\nInput option : ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            my_util.sort(plist);
            break;
        case 2:
            my_util.print(plist);
            break;
        case 3:
            plist = my_filter(plist);
            break;
        case 4:
            printf("Exit the program\n");
            return 0;
            break;
        }
    }
    array_list_destroy(&plist);

    return 0;
}

void my_print(parking_list_t* list)
{
    int i;
    parking_t key;
    printf("====== Print all elements (len:%d)======\n", list->len - 1);

    int len = list->len;
    for (int i = 0; i < len - 1; i++)
    {
        printf("%s(%s) [%s %s (%5f, %5f)]\n", list->parkings[i].name, list->parkings[i].agency, list->parkings[i].city, list->parkings[i].district, list->parkings[i].longitude, list->parkings[i].latitude);
    }
}

void my_sort(parking_list_t* list)
{
    int op;

    // 옵션 입력
    printf("====== Choose a sorting algorithm ======\n");
    printf("(1) selection sort\n");
    printf("(2) insertion sort\n");
    printf("Input option 1:");
    scanf("%d", &op);

    if (op == 1)
    {
        // selection sort
        selection_sort(list);
    }
    else if (op == 2)
    {
        // insertion sort
        insertion_sort(list);
    }
    else
    {
        printf("Invalid option\n");
    }
}

parking_list_t* my_filter(parking_list_t* plist)
{
    int op;
    parking_list_t* new_plist = (parking_list_t*)malloc(sizeof(parking_list_t*) * 1);
    array_list_create(&new_plist);

    printf("====== Filter ======\n(1) by city - district\n(2) by longitude - latitude\nInput option : ");
    scanf("%d", &op);

    if (op == 1)  ///(1) by city - district
    {
        printf("Input city: ");
        char tmp_city[100];
        scanf("%s", tmp_city);
        printf("Input district: ");
        char tmp_district[100];
        scanf("%s", tmp_district);

        for (int i = 0; i < plist->len; i++)
        {
            if (strcmp(plist->parkings[i].city, tmp_city) == 0 && strcmp(plist->parkings[i].district, tmp_district) == 0) // 같다면
            {
                array_list_insert_last(new_plist, plist->parkings[i]);
            }
        }
    }
    else if (op == 2)  ////(2) by longitude - latitude
    {
        double min_long, max_long, min_lat, max_lat;
        printf("Input min_long: "); scanf("%lf", &min_long);
        printf("Input max_long: "); scanf("%lf", &max_long);
        printf("Input min_lat: "); scanf("%lf", &min_lat);
        printf("Input max_lat: "); scanf("%lf", &max_lat);

        for (int i = 0; i < plist->len; i++)
        {
            if (plist->parkings[i].longitude >= min_long && plist->parkings[i].longitude <= max_long)
            {
                if (plist->parkings[i].latitude >= min_lat && plist->parkings[i].latitude <= max_lat)
                {
                    array_list_insert_last(new_plist, plist->parkings[i]);
                }
            }
        }
    }
    array_list_destroy(&plist);

    return new_plist;
}

/* Array List */
int array_list_create(parking_list_t** list)
{
    (*list)->len = 0;
    (*list)->parkings = (parking_t*)malloc(sizeof(parking_t) * 1);

    return 1;    // return Success
}

int array_list_destroy(parking_list_t** list)
{
    free((*list)->parkings);
    return 1;    // return Success
}

int array_list_insert_last(parking_list_t* list, parking_t e)
{
    strcpy(list->parkings[list->len].name, e.name);  // list->parkings[0].city
    strcpy(list->parkings[list->len].agency, e.agency);
    strcpy(list->parkings[list->len].city, e.city);
    strcpy(list->parkings[list->len].district, e.district);

    list->parkings[list->len].longitude = e.longitude;
    list->parkings[list->len].latitude = e.latitude;

    list->len += 1;
    list->parkings = (parking_t*)realloc(list->parkings, sizeof(parking_t) * (list->len + 1));

    return 1;
}

/* Sort */

void swap(parking_t* a, parking_t* b)
{
    parking_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(parking_list_t* list)
{
    int op;

    //list = (parking_list_t*)malloc(sizeof(parking_list_t) * 1);
    //array_list_create(&list);

    printf("====== Selection Sort ======\n");
    printf("(1) by city-district\n");
    printf("(2) by longitude-latitude\n");
    printf("Input option2:");
    scanf("%d", &op);

    if (op == 1) // city - district로 정렬
    {
        int i, j, min; // 저장할 변수들
        for (i = 0; i < list->len; i++)
        {
            min = i;

            for (j = i; j < list->len; j++)
            {

                if (strcmp(list->parkings[j].city, list->parkings[min].city) < 0)
                {
                    min = j;
                }
                else if (strcmp(list->parkings[j].city, list->parkings[min].city) == 0)
                {
                    if (strcmp(list->parkings[j].district, list->parkings[min].district) < 0)
                    {
                        min = j;
                    }
                }
            }
            // i 인덱스의 원소와 min 인덱스의 원소 교환

            swap(&list->parkings[i], &list->parkings[min]);

        }
    }
    else if (op == 2) // long-lati 로 정렬
    {
        int i, j, min; // 저장할 변수들
        for (i = 0; i < list->len; i++)
        {
            min = i;

            for (j = i; j < list->len; j++)
            {

                if (list->parkings[j].longitude < list->parkings[min].longitude)
                {
                    min = j;
                }
                else if (list->parkings[j].longitude == list->parkings[min].longitude)
                {
                    if (list->parkings[j].latitude < list->parkings[min].latitude)
                    {
                        min = j;
                    }
                }
            }
            // i 인덱스의 원소와 min 인덱스의 원소 교환

            swap(&list->parkings[i], &list->parkings[min]);
        }
    }
    else
    {
        printf("Invalid option\n");
    }
}

void insertion_sort(parking_list_t* list)
{
    int op;

    printf("====== Insertion Sort ======\n");
    printf("(1) by city-district\n");
    printf("(2) by longitude-latitude\n");
    printf("Input option2:");
    scanf("%d", &op);

    if (op == 1)
    {
        int i, j;
        parking_t key;
        for (i = 1; i < list->len; i++)
        {
            key = list->parkings[i];
            for (j = i; j > 0; j--)
            {
                if (strcmp(list->parkings[j].city, key.city) < 0)
                    list->parkings[j] = list->parkings[j - 1];
                else if (strcmp(list->parkings[j].city, key.city) == 0)
                {
                    if (strcmp(list->parkings[j].district, key.district) < 0)
                        list->parkings[j] = list->parkings[j - 1];
                }
                else
                    break;
            }

            list->parkings[j] = key;
        }
    }
    else if (op == 2)
    {
        int i, j;
        parking_t key;
        for (i = 1; i < list->len; i++)
        {
            key = list->parkings[i];
            for (j = i; j > 0; j--)
            {
                if (list->parkings[j - 1].longitude > key.longitude)
                    list->parkings[j] = list->parkings[j - 1];
                else if (list->parkings[j - 1].longitude == key.longitude)
                {
                    if (list->parkings[j - 1].latitude > key.latitude)
                        list->parkings[j] = list->parkings[j - 1];
                }
                else
                    break;
            }

            list->parkings[j] = key;
        }
    }
    else
    {
        printf("Invalid option\n");
    }
}



