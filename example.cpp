/*  sdl-grapher - SDL library
 *  Copyright (C) 2009 - Hans-Kristian Arntzen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "./include/sdl_graph/sdlgraph.h"

int main(int argc, char *argv[])
{
	Graph myGraph; /* Creates a new Graph */
	
	myGraph.xMin = -10.0;
	myGraph.xMax = 10.0;
	myGraph.xScale = 1.0;
	myGraph.yMin = -10.0;
	myGraph.yMax = 10.0;
	myGraph.yScale = 1.0;
	myGraph.width = 500;
	myGraph.height = 500;
	
	/* Sets some initial values for the graph. These MUST be defined before you run
	 * init_graph()! */
	
	init_graph(&myGraph); /* Initialized the graph, which gives you a normal SDL window */
	
	draw_grid(&myGraph, 0, 2); /* Draws a grid in origo. With thickness 0 (1 pixel), and after each xScale or yScale, draw
									some "landmarks". These will be 5 pixels high (2*2 + 1). */

	int count;
	float x, y, temp;

	set_color(&myGraph, 0, 0xFF, 0); /* Normal RGB fashion. Sets all points written to screen to be green */
    
	for ( count = -100; count < 100; count++ )
	{
		x = count/10.0; /* x will go from -10 to 10 with interval 0.1 */
		y = 5.0*sin(x)/x; /* y is the result of f(x) = 5*sin(x)/x. You might run into "diving by zero" errors. :D */

		// std::cout << x << " " << y << std::endl;

		print_pixel(&myGraph, x, y); /* Prints a pixel to the screen on the graph coordinated (x,y).
										Since this goes through a loop, you print out the entire graph. */
		delay(1);					 /* Waits 10ms between each point printed. */
		update_screen(&myGraph);      /* Updates the screen. You now have a cool graph animation :D */
	}
	
	std::cout << "heey" << std::endl;

	delay(2000); /* Waits two seconds ... */
	
	clear_graph(&myGraph); /* Clears out the graph */
	
	set_color(&myGraph, 0, 0, 0xFF); /* Changes color to be blue */

	SDL_Color orange = {255, 127, 40, 255};
	SDL_Color black = {0, 0, 0, 255};
	SDL_Color white = {255, 255, 255, 255};
	SDL_SetRenderDrawColor((&myGraph)->renderer, white.r, white.g, white.b, white.a);
	
	// draw_grid(&myGraph, 1, 250); /* Draws a full grid on the screen */
	draw_grid(&myGraph, 0, 2); /* Draws a full grid on the screen */
	
	update_screen(&myGraph);
	
	set_color(&myGraph, 0xFF, 0xFF, 0xFF); 
	
	// for ( count = -1000; count < 1000; count++ )
	// {
	// 	x = count/100.0;
	// 	y = exp(x);

	// 	delay(2);
	// 	print_pixel(&myGraph, x, y);
	// 	update_screen(&myGraph);
		
	// 	/* Prints out the exp(x) function */ 
	// }
	
	int pixels = 0;
	// /* This will print out something really fancy :D 
	//  * Parmetrization example */
	for ( count = 0; count < 2000000; count+=1 )
	{
		temp = (float)count;
		SDL_SetRenderDrawColor((&myGraph)->renderer, rand()%255, rand()%255, rand()%255, white.a);
		// set_color(&myGraph, rand()%255, rand()%255, rand()%255);

		x = cos(temp/1000.0)*(exp(temp/1000000.0)-1.0)*tan(temp/500.0);
		y = sin(temp/1000.0)*(exp(temp/1000000.0)-1.0)*tan(temp/200.0);
		// x = cos(temp/1000.0)*tan(temp/500.0);
		// y = sin(temp/1000.0)*tan(temp/200.0);

		print_pixel(&myGraph, x, y);
		
		// pixels++;
		
		// if ( pixels % 5000 == 0)
		// {
			update_screen(&myGraph);
		// }
		
	}
	
	
	
	
	

	idle(); 	/* Waits for the user to exit the program.
  					To do: Accept aribitary event to continue program
					instead of only exiting it.	*/
	quit(); 	/* Quits ... baibai! (if idle() didn't do so already ...)*/
	
	return 0;
}
