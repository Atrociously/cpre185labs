#include <stdio.h>

//void force(int mass, int acceleration);
void force(double mass, double acceleration); // fixed bad type in declaration

int main(int argc, char *argv[]) {
    //double mass;
    double mass, acceleration; // fixed missing variable declaration

    printf("Enter an acceleration in m/s^2: ");
    scanf("%lf", &acceleration);

    printf("Enter the mass of the object in kg: ");
    scanf("%lf", &mass);

    printf("\nYou entered %lf m/s^2.\n", acceleration);
    printf("You entered %lf kg.\n\n", mass);

    force(mass, acceleration);

    return 0;
}

void force(double mass, double acceleration) {
    printf("The force is approximately %.2lf Newtons.\n", mass * acceleration);
}
