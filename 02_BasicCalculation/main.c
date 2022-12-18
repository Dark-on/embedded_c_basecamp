/*
 * Variant 2
*/

#include <stdio.h>
#include <math.h>


void wait_for_user_input(void);


int main(void){
	float alpha;
	printf("a = ");
	if ( scanf("%f", &alpha) ){
			printf("Invalid input! Exiting...");
			wait_for_user_input();
			return 0;
	}

	float z1, z2;
	z1 = cos(alpha) + sin(alpha) + cos(3 * alpha) + sin(3 * alpha);
	z2 = 2 * sqrt(2) * cos(alpha) * sin(M_PI_4 + 2 * alpha);
	printf("\nz1 = %f\nz2 = %f\n", z1, z2);

	wait_for_user_input();
	return 1;
}


void wait_for_user_input(void){
	printf("\nPress enter key to exit the application");
	while(getchar() != '\n')
	{
		//just read the input buffer and do nothing
	}
	getchar();
}



