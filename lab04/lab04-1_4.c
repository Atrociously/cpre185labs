#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    //double speed_of_light!;
    double speed_of_light; // fixed invalid identifier
    //double wave-length;
    double wave_length; // fixed invalid identifier
    //double ~length_in_meters;
    double length_in_meters; // fixed invalid identifier
    //double plank const;
    double plank_const; // fixed invalid identifier
    //double 0energy;
    double energy; // fixed invalid identifier

    // All lines beyond this point was fixed to use the correct new identifiers for the variables

    plank_const = 6.62606957 * pow(10, 9); // Plank's constant
    speed_of_light = 2.99792458 * pow(10, 8); // Constant for the speed of light
    wave_length = 0;
    length_in_meters = 0;
    energy = 0;

    printf("Welcome! This program will give the energy, in Joules,\n");
    printf("of 1 photon with a certain wave-length.\n");
    printf("Please input a wave-length of light in nano-meters.\n");
    printf("Please do not enter a negative, or zero wave-length.\n");

    scanf("%lf", &wave_length);
    if (wave_length > 0.0) {
	length_in_meters = wave_length / pow(10, 9); // converting nano-meters to meters
	energy = (plank_const * speed_of_light) / length_in_meters; // Calculating the energy of one photon
	printf("A photon with a wave-length of %08.3lf nano-meters, carries "
	       "\napproximately %030.25lf joules of energy.", wave_length, energy);
    } else {
	printf("Sorry, you put in an invalid number.");
	printf("Please rerun the program and try again.");
    }

    return 0;
}
