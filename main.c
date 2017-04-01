#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

enum class_cars{
    Sedan,
    Hachback,
    crossower,
};

struct car{
    char name[100];
    char model[100];
    int year;
    float power;
    double speed;
    int ID;
};

struct data_base{
    int unic_number;
    int number_of_cars;
    struct car** cars;
};

struct data_base create()
{
    struct data_base b;
    b.unic_number = 0;
    b.number_of_cars = 0;
    b.cars = 0;
    return(b);
}

void print(struct car* c)
{
    printf("Марка автомобиля: %s \n Модель автомобиля: %s\n Год выпуска: %d\n Объём двигателя: %.1f\n Время разгона до 100 км/ч: %lf\n ID %d\n", c->name, c->model, c->year, c->power, c->speed, c->ID);
}

void print_all(struct data_base* base)
{
    if(base->number_of_cars == 0)
        printf("Элементов в базе данных нет\n");
    int i;
    for(i = 0; i < base->number_of_cars; ++i)
        print(base->cars[i]);
}

void add(struct car* new_car, struct data_base* base)
{
    base->unic_number ++;
    base->number_of_cars ++;
    if(base->cars == 0)
        base->cars = malloc(1 * sizeof(struct car*));
    else
        base->cars = realloc(base->cars, base -> number_of_cars * sizeof(struct car*));
    base->cars[base->number_of_cars - 1] = new_car;
    new_car->ID = base->unic_number;
}

void search(char *name, struct data_base* base)
{
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(strcmp(name, base->cars[j]->name) == 0)
            print(base->cars[j]);
        j--;
    }
}

int delete(int ID, struct data_base* base)
{
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(base->cars[j]->ID == ID)
            break;
        j--;
    }
    if(j < 0)
        return 0;
    free(base->cars[j]);
    base->number_of_cars--;
    if(base->number_of_cars == 0)
    {
        free(base->cars);
        return 1;
    }
    while(j < base->number_of_cars)
    {
        base->cars[j] = base->cars[j + 1];
        ++j;
    }
    base->cars = realloc(base->cars, base -> number_of_cars * sizeof(struct car*));
    return 1;
}

void delete_all(struct data_base* base)
{
    int i;
    for(i = 0; i < base->number_of_cars; ++i)
        free(base->cars[i]);
    free(base->cars);
    base->number_of_cars = 0;
}

void output(FILE *in, struct data_base* base)
{
    in = fopen("SUBD.txt", "w");
    int i;
    for(i = 0; i < base->number_of_cars; ++i)
        fwrite(base->cars[i], 1, sizeof(struct car), in);
    fclose(in);
}

int main()
{
    FILE *in;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    struct data_base base = create();
    int i;
    printf("Справка по использованию: \n");
    printf("1 - добавить элемент\n2 - удалить элемент\n3 - найти элемент\n4 - удалить все элементы и завершить работу\n5 - вывести все элементы\n6 - вывести справку\n");
    while(1)
    {
        printf("Что будем делать?\n");
        scanf("%d", &i);
        if(i == 1)
        {
            struct car* a = malloc(sizeof(struct car));
            printf("Введите марку\n");
            scanf("%s", a->name);
            printf("Введите модель\n");
            scanf("%s", a->model);
            printf("Введите год выпуска\n");
            scanf("%d", &a->year);
            printf("Введите объём двигателя\n");
            scanf("%f", &a->power);
            printf("Введите время разгона до 100 км/ч\n");
            scanf("%lf", &a->speed);
            add(a, &base);
        }
        if(i == 2)
        {
            int ID;
            printf("Введите ID удаляемого элемента\n");
            scanf("%d", &ID);
            int k = delete(ID, &base);
            if(k == 0)
                printf("Ошибка, данного элемента нет в базе данных\n");
        }
        if(i == 3)
        {
            char name[100];
            printf("Введите имя искомого элемента\n");
            scanf("%s", name);
            search(name, &base);
            /*if(b == 0)
                printf("Ошибка, данного элемента нет в базе данных\n");
            else
                print(b);*/
        }
        if(i == 4)
        {
            delete_all(&base);
            return 0;
        }
        if(i == 5)
        {
            print_all(&base);
        }
        /*if(i == 7)
            output(in, &base);*/
        if(i == 6)
             printf("1 - добавить элемент\n2 - удалить элемент\n3 - найти элемент\n4 - удалить все элементы и завершить работу\n5 - вывести все элементы\n6 - вывести справку\n");
    }
}
