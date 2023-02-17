#include <stdio.h>

double voltage(double resistance, double current);
double resistance(double voltage, double current);
double current(double voltage, double resistance);

int main(int argc, char *argv[]) {
    int selection = 0;
    //int v, i, r;
    double v, i, r; // fixed incorrect type for inputs

    printf("selection:\n1 for voltage\n2 for resistance\n3 for current\n");
    scanf("%d", &selection);

    if (selection > 3 || selection < 1) {
	printf("Invalid number\n");
	return -1;
    }

    printf("Enter floating point numbers for input...\n");
    if (selection == 1) {
	printf("Please enter a resistance value: ");
	scanf("%lf", &r);

	printf("Please enter a current value: ");
	scanf("%lf", &i);

	printf("Your voltage is: %lf Volts\n", voltage(r, i));
    } else if (selection == 2) {
	printf("Please enter a voltage value: ");
	scanf("%lf", &v);

	printf("Please enter a current value: ");
	scanf("%lf", &i);

	printf("Your resistance is: %lf Ohms\n", resistance(v, i));
    } else if (selection == 3) {
	printf("Please enter a resistance value: ");
	scanf("%lf", &r);

	printf("Please enter a voltage value: ");
	scanf("%lf", &v);

	printf("Your current is: %lf Amps\n", current(v, r));
    }
}

double voltage(double resistance, double current) {
    return resistance * current;
}

double resistance(double voltage, double current) {
    return voltage / current;
}

double current(double voltage, double resistance) {
    return voltage / resistance;
}
