
/*
Arrays of structs : BroCode Youtube
Link: https://www.youtube.com/watch?v=ZwSyuqbeN0c
*/

#include <stdio.h>


typedef struct
{
	char model[25];
	int year;
	int price;
}Car;

int main()
{
	Car cars[] = {{ "Mustang", 2025, 32000 },
					{ "Corvette", 2026, 68000 },
					{ "Challenger", 2024, 29000 }};

	int number = sizeof(cars) / sizeof(cars[0]);

	for (int i = 0; i < number; i++)
	{
		printf("%s %d $%d\n", cars[i].model, cars[i].year, cars[i].price);
	}

	Car car1 = { "Mustang", 2025, 32000 };
	Car car2 = { "Corvette", 2026, 68000 };
	Car car3 = { "Challenger", 2024, 29000 };

	printf("%s %d $%d\n", car1.model, car1.year, car1.price);
	printf("%s %d $%d\n", car2.model, car2.year, car2.price);
	printf("%s %d $%d\n", car3.model, car3.year, car3.price);

	return 0;
}
