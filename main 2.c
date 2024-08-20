
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
int	main(void)
{
	int	i;
	int	plr_x;
	int	plr_y;
	int	ray;
	int	start_direction_angles;
	int	main_ray;
	int	ray;

	i = 0;
	start_direction_angles = 0;
	main_ray = start_direction_angles;
	main_ray += change_direction(main_ray);
	/// field of view = 80;
	main_ray -= 40;
	while (i < 9)
	{
		throw_ray(main_ray);
		main_ray += 10;
		i++;
	}
}

int	change_direction(int old_direction)
{
	int	new_main_direction;

	////write a function that adds or substracts degrees depending on what key is pressed
	new_main_direction = old_direction + 10;
	if (new_main_direction == 360)
		new_main_direction = 0;
	return (new_main_direction);
}

int	throw_ray(int plr_x, int plr_y, int angle_degrees)
{
	int map[5][5] = 
    {{1, 1, 1, 1, 1}, 
    {1, 0, 1, 1, 1}, 
    {1, 0, 1, 0, 1}, 
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1};
    };

    ///1.out of map, making a grid map with position points x & y
    //to know where the boxes on the grid start and end;
    //2.making a structure with x & y of walls;
    //3. calculating x & y to the nearest grid border
    //4. define M_PI = 3,14
    //5. we could work with radians fnot degrees from the beginning?

    //calculating hypotenuse:
    double angle_radians = angle_degrees * (M_PI / 180.0);
    double hypotenuse = opposite / sin(angle_radians);
    printf("The hypotenuse is: %.2f\n", hypotenuse);
    //calculating adjacent:
    double adjacent = sqrt(hypotenuse * hypotenuse - opposite * opposite);
    //we have to check if the point is the wall (anywehere between the )







}*/