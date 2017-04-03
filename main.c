#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

enum class_cars{
    car = 1,
    motorbike,
};

union type{
    int doors;
    char types[80];
};

struct car{
    int k;
    char name[100];
    char model[100];
    union type Type;
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
        int g = c->k;
        if(g == 1)
            printf("Автомобиль\n Марка автомобиля: %s \n Модель автомобиля: %s\n Количество дверей: %d\n Год выпуска: %d\n Объём двигателя: %.1f\n Время разгона до 100 км/ч: %lf\n ID %d\n", c->name, c->model, c->Type.doors, c->year, c->power, c->speed, c->ID);
        else
            printf("Мотоцикл\n Марка мотоцикла: %s \n Модель мотоцикла: %s\n Разновидность мотоцикла: %s\n Год выпуска: %d\n Объём двигателя: %.1f\n Время разгона до 100 км/ч: %lf\n ID %d\n", c->name, c->model, c->Type.types,c->year, c->power, c->speed, c->ID);
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

void search_name(char *name, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(strcmp(name, base->cars[j]->name) == 0)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_model(char *model, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(strcmp(model, base->cars[j]->model) == 0)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_year(int year, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(base->cars[j]->year == year)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_power(float power, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(base->cars[j]->power == power)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_speed(double speed, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(base->cars[j]->speed == speed)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_doors(int door, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(base->cars[j]->Type.doors == door)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
}

void search_types(char *types, struct data_base* base)
{
    int counter = 0;
    int j = base->number_of_cars - 1;
    while(j >= 0)
    {
        if(strcmp(types, base->cars[j]->Type.types) == 0)
        {
            print(base->cars[j]);
            ++counter;
        }

        j--;
    }
    if(counter == 0)
        printf("Ошибка, данного элемента нет в базе");
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

/*void output(FILE *in, struct data_base* base)
{
    in = fopen("SUBD.txt", "w");
    int i;
    for(i = 0; i < base->number_of_cars; ++i)
    {
        int g = base->cars[i]->k;
        if(g == 1)
            fprintf(in, "Автомобиль\n Марка автомобиля: %s \n Модель автомобиля: %s\n Количество дверей: %d\n Год выпуска: %d\n Объём двигателя: %.1f\n Время разгона до 100 км/ч: %lf\n ID %d\n", base->cars[i]);
        else
            fprintf(in, "Мотоцикл\n Марка мотоцикла: %s \n Модель мотоцикла: %s\n Разновидность мотоцикла: %s\n Год выпуска: %d\n Объём двигателя: %.1f\n Время разгона до 100 км/ч: %lf\n ID %d\n", base->cars[i]);
    }
    fclose(in);
}*/

int main()
{
    char types[100];
    char name[100];
    char model[100];
    int l;
    float h;
    int door;
    double z;
    enum class_cars Class;
    FILE *in;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    struct data_base base = create();
    int i;
    printf("Справка по использованию: \n");
    printf("1 - добавить элемент\n2 - удалить элемент\n3 - найти элемент\n4 - удалить все элементы и завершить работу\n5 - вывести все элементы\n6 - вывесть содержание базы данных в файл\n7 - вывести справку\n");
    while(1)
    {
        printf("Что будем делать?\n");
        scanf("%d", &i);
        if(i == 1)
        {
            struct car* a = malloc(sizeof(struct car));
            printf("Введите тип транспортного средства( 1 - автомобиль, 2 - мотоцикл)\n");
            scanf("%d", &a->k);
            switch(a->k)
            {
                case car:
                    printf("Введите марку\n");
                    scanf("%s", a->name);
                    printf("Введите модель\n");
                    scanf("%s", a->model);
                    printf("Введите количество дверей\n");
                    scanf("%d", &a->Type.doors);
                    printf("Введите год выпуска\n");
                    scanf("%d", &a->year);
                    printf("Введите объём двигателя\n");
                    scanf("%f", &a->power);
                    printf("Введите время разгона до 100 км/ч\n");
                    scanf("%lf", &a->speed);
                    add(a, &base);
                    break;
                case motorbike:
                    printf("Введите марку\n");
                    scanf("%s", a->name);
                    printf("Введите модель\n");
                    scanf("%s", a->model);
                    printf("Введите разновидность мотоцикла\n");
                    scanf("%s", a->Type.types);
                    printf("Введите год выпуска\n");
                    scanf("%d", &a->year);
                    printf("Введите объём двигателя\n");
                    scanf("%f", &a->power);
                    printf("Введите время разгона до 100 км/ч\n");
                    scanf("%lf", &a->speed);
                    add(a, &base);
                    break;
            }
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
            printf("Введите ключ поиска\n");
            printf("1 - по марке\n2 - по модели\n3 - по году выпуска\n4 - по объему двигателя\n5 - по времени разгона до 100 км/ч\n6 - по количеству дверей машины\n7 - по разновидности мотоцикла\n");
            int n;
            scanf("%d", &n);
            switch(n)
            {
                case 1:
                    printf("Введите марку искомого элемента\n");
                    scanf("%s", name);
                    search_name(name, &base);
                    break;
                case 2:
                    printf("Введите модель искомого элемента\n");
                    scanf("%s", model);
                    search_model(model, &base);
                    break;
                case 3:
                    printf("Введите год выпуска искомого элемента\n");
                    scanf("%d", &l);
                    search_year(name, &base);
                    break;
                case 4:
                    printf("Введите объём двигателя искомого элемента\n");
                    scanf("%f", &h);
                    search_power(h, &base);
                    break;
                case 5:
                    printf("Введите время разгона до 100 км/ч искомого элемента\n");
                    scanf("%lf", &z);
                    search_speed(z, &base);
                    break;
                case 6:
                    printf("Введите количество дверей у искомого элемента\n");
                    scanf("%d", &door);
                    search_doors(door, &base);
                    break;
                case 7:
                    printf("Введите какая разновидность мотоцикла у искомого элемента\n");
                    scanf("%s", types);
                    search_types(types, &base);
                    break;
            }
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
        /*if(i == 6)
            output(in, &base);*/
        if(i == 7)
             printf("1 - добавить элемент\n2 - удалить элемент\n3 - найти элемент\n4 - удалить все элементы и завершить работу\n5 - вывести все элементы\n6 - вывесть содержание базы данных в файл\n7 - вывести справку\n");
    }
}

