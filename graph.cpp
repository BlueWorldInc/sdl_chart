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


Uint32 * get_pixel_from_coordinates ( Graph * myGraph, float x, float y )
{
  	Uint32 * pixel;
  	
	int realWidth = get_width_from_coordinate(myGraph, x); 
  	
  	
	int realHeight = get_height_from_coordinate(myGraph, y);
  	
  	
  	if ( realHeight < 0 || realHeight >= myGraph->height || realWidth < 0 || realWidth >= myGraph->width )
		return NULL;
  	else
  	{
		pixel = (Uint32*) myGraph->workingSurface->pixels;
		
		Uint32 width,height;
		width = realWidth;
		height = realHeight * myGraph->width;
		pixel += width + height;
		
		return pixel;
	}

}

Uint32 * get_pixel_from_window ( Graph * myGraph, int x, int y )
{
  	Uint32 * pixel;
  	
  	if ( y < 0 || y >= myGraph->height || x < 0 || x >= myGraph->width )
		return NULL;
  	else
  	{
		Uint32 width,height;
		width = x;
		height = y * myGraph->width;
		pixel = (Uint32*)myGraph->workingSurface->pixels + width + height;
		return pixel;
	}

}

int get_width_from_coordinate ( Graph * myGraph, float x )
{
  	int realWidth = (int)((float)myGraph->width * (x - myGraph->xMin) / (myGraph->xMax - myGraph->xMin));
	
	return realWidth;	
}

int get_height_from_coordinate ( Graph * myGraph, float y )
{
  	int realHeight = (int)((float)myGraph->height - (float)myGraph->height * (y - myGraph->yMin) / (myGraph->yMax - myGraph->yMin));
	
	return realHeight;	
}

void init_graph ( Graph * myGraph )
{
	SDL_Window *window = NULL;
    window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, myGraph->width, myGraph->height, SDL_WINDOW_FULLSCREEN_DESKTOP);
    // SDL_WM_SetCaption("GRAPH OUTPUT", NULL);
    set_color(myGraph, 0xFF, 0xFF, 0xFF);
      
}

void draw_grid ( Graph * myGraph, int thickness, int length )
{
	
	
	int height, width;
	
	thickness = abs(thickness);
	length = abs(length);
	
	
	height = get_height_from_coordinate(myGraph, 0.0);
	width = get_width_from_coordinate(myGraph, 0.0);
	
	
	int countX, countY;
	
	int pitchX, pitchY;
	pitchX = get_width_from_coordinate(myGraph, myGraph->xScale) - width;
	pitchY = get_height_from_coordinate(myGraph, myGraph->yScale) - height;
	
	
	for ( countX = 0; countX < myGraph->width; countX++ )
	{
		
		
		if ( (countX - width) % pitchX == 0 )
		{
			
			for ( countY = height - length; countY <= height + length; countY++ )
			{
				print_pixel_by_window(myGraph, countX, countY);
			}
		}
		
		else
		{
			for ( countY = height - thickness; countY <= height + thickness; countY++ )
			{
				
		    
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
	}
	
	for ( countY = 0; countY < myGraph->height; countY++ )
	{
		
		if ( ((countY - height) % pitchY) == 0 )
		{
			
			for ( countX = width - length; countX <= width + length; countX++ )
			{
				
			   
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
		
		
		else
		{
			for ( countX = width - thickness; countX <= width + thickness; countX++ )
			{
			   
				print_pixel_by_window ( myGraph, countX, countY );
			}
		}
	}
	
	 
}

void print_pixel_by_window ( Graph * myGraph, int x, int y )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
	
		pixel = get_pixel_from_window( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = myGraph->color;
	
	
}
	
void print_pixel ( Graph * myGraph, float x, float y )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
		pixel = get_pixel_from_coordinates( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = myGraph->color;
	
}
	
void print_pixel_by_window_color ( Graph * myGraph, int x, int y, Uint32 color )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
	
		pixel = get_pixel_from_window( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = color;	
	
}

void print_pixel_color ( Graph * myGraph, float x, float y, Uint32 color )
{
	Uint32 * pixel;
	SDL_Event event;
	if ( SDL_PollEvent ( &event ) )
	{
		if (event.type == SDL_QUIT)
		{
				quit();
		}
	}
	
		pixel = get_pixel_from_coordinates( myGraph, x, y );
	
		if( pixel != NULL )
			*pixel = color;
}

void update_screen(Graph * myGraph)
{
	if (SDL_RenderPresent(myGraph->workingSurface) != 0) quit();
}

void delay ( int time )
{
	int startTime = SDL_GetTicks();
	
	SDL_Event event;
	
	while ( (SDL_GetTicks() - startTime) < time )
	{
		if ( SDL_PollEvent ( &event ) )
		{
			if (event.type == SDL_QUIT)
			{
				quit();
			}
		}
		else 
			SDL_Delay( 1 );
	}
}

void clear_graph(Graph * myGraph)
{
	SDL_FillRect(myGraph->workingSurface, NULL, 0x00000000);
}

void idle()
{
	SDL_Event event;
	while ( 1 )
	{
		if ( SDL_PollEvent ( &event ) )
		{
			if (event.type == SDL_QUIT)
			{
				quit();
			}
		}
		else
			delay(1);
	}
}

int write_BMP_header(FILE * file, int width, int height )
{
	int size;
	if ( width % 4 == 0 )
		size = 54 + 3*width*height;
	else
		size = 54 + 3*width*height + height*(4 - width%4);

	int temp[0x36] = { 
		0x42, 0x4D, // Magic number 
		size%0x100, size/0x100, size/0x10000, size/0x1000000, // Size of BMP file
	    0x00, 0x00, // NA
		0x00, 0x00, // NA
		0x36, 0x00, 0x00, 0x00, // The offset where the bitmap data can be found 
		0x28, 0x00, 0x00, 0x00, // The number of bytes in the header (from this point)
		width%0x100, width/0x100, width/0x10000, width/0x1000000, // Width of bitmap in pixels
		height%0x100, height/0x100, height/0x10000, height/0x1000000, // The height of the bitmap in pixels
		0x01, 0x00, // Number color planes being used
		0x18, 0x00, // Number of bits/pixel
		0x00, 0x00, 0x00, 0x00, // BI_RGB, No compression
		0x10, 0x00, 0x00, 0x00, // Size of raw BMP data (after this header) 
		0x13, 0x0B, 0x00, 0x00, // Horizontal reso (pixels/meter)
		0x13, 0x0B, 0x00, 0x00, // Vertical reso (pixels/meter)
		0x00, 0x00, 0x00, 0x00, // Number of colors in the palette
		0x00, 0x00, 0x00, 0x00 // All colors are important
		};

		int count;
		for ( count = 0; count < 0x36; count++ )
		{
			if (fputc(temp[count], file) == EOF )
				return 0;
		}
		return 1;
}

int write_BMP_data(FILE * file, Graph * myGraph )
{
	int count, padding;
	if ( myGraph->width % 4 == 0 )
		padding = 0;
	else
		padding = 4 - (3*myGraph->width)%4;

	Uint32 * pixel;
	Uint8 * subpixel;

	int widthCount, heightCount;

	for ( heightCount = 0; heightCount < myGraph->height; heightCount++ )
	{
		for ( widthCount = 0; widthCount < myGraph->width; widthCount++ )
		{
			pixel = get_pixel_from_window(myGraph, widthCount, myGraph->height - heightCount - 1);
			if ( pixel != NULL )
			{
			subpixel = (Uint8*)pixel;
			if (fputc(subpixel[0], file) == EOF)
				return 0;
			if (fputc(subpixel[1], file) == EOF)
				return 0;
			if (fputc(subpixel[2], file) == EOF)
				return 0;
			}
		}
        for ( count = 0; count < padding; count++ )
		{
			if (fputc(0x00, file) == EOF)
				return 0;
		}
	}
	return 1;
}


void write_BMP(Graph * myGraph, char * name)
{
	FILE * file = fopen(name, "wb");
	if ( file == NULL )
	{
		fprintf(stderr, "Error opening file\n");
		exit(1);
	}
	if (!write_BMP_header(file, myGraph->width, myGraph->height))
	{
		fprintf(stderr, "Error writing BMP header\n");
		exit(2);
	}
	if (!write_BMP_data(file, myGraph))
	{
		fprintf(stderr, "Error writing BMP data\n");
		exit(3);
	}
	fclose(file);
}


void set_color(Graph * window, int r, int g, int b)
{
	window->color = RGB(r, g, b);
}
		
void quit()
{
	SDL_Quit();
	exit(0);
}
