#include <stdio.h>
#include "fuel_calc_b.h"

static int mode;
static int dist;
static float capa;

void set_mode(int sel)
{
    switch (sel)
    {
        case 0:
        case 1:
            mode = sel;
            break;
        default:
            printf("Invalid mode specified. Mode 1(US) used.\n");
    }
}

void get_info(void)
{
    switch (mode)
    {
        case 0:
            printf("Enter distance traveled in kilimeters: ");
            scanf("%d", &dist);
            printf("Enter fuel consumed in liters: ");
            scanf("%f", &capa);
            break;
        case 1:
            printf("Enter distance traveled in miles: ");
            scanf("%d", &dist);
            printf("Enter fuel consumed in gallons: ");
            scanf("%f", &capa);
            break;
        default:
            break;
    }
}

void show_info(void)
{
    switch (mode)
    {
        case 0:
            printf("Fuel consumprion is %.2f liters per 100 km.\n", capa/dist*100);
            break;
        case 1:
            printf("Fuel consumprion is %.1f miles per gallon.\n", dist/capa);
            break;
        default:
            break;
    }
}