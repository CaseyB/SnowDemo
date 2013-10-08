#include "snowRenderer.h"

#include <stdlib.h>
#include <GLES/gl.h>

#define MAX_FLAKES 40
#define MAX_SPEED 0.08
#define MIN_SPEED 0

#define MIN_SIZE 10
#define MAX_SIZE 30

#define FLOAT_PER_FLAKE 6 * 3

GLfloat VERTICIES[MAX_FLAKES * FLOAT_PER_FLAKE];
GLfloat POSITIONS[MAX_FLAKES*2];
GLfloat RADII[MAX_FLAKES];

int _width, _height, i;

void on_surface_created()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
	glClearDepthf(1.0f);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void on_surface_changed(int width, int height)
{
	_width = width;
	_height = height;

	buildFlakeBuffer();

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void on_draw_frame(long deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	updateFlakeBuffer(deltaTime);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, VERTICIES);

	glDrawArrays(GL_TRIANGLES, 0, MAX_FLAKES * FLOAT_PER_FLAKE);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void buildFlakeBuffer()
{
	for(i = 0; i < MAX_FLAKES; i++)
	{
		RADII[i] = MIN_SIZE + (float)rand() / ((float)RAND_MAX / (MAX_SIZE - MIN_SIZE));
		POSITIONS[i*2+0] = (rand() / (float)RAND_MAX) * _width;
		POSITIONS[i*2+1] = (rand() / (float)RAND_MAX) * _height;

		VERTICIES[i*FLOAT_PER_FLAKE+0]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+1]  = POSITIONS[i*2+1] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+2]  = 0;

		VERTICIES[i*FLOAT_PER_FLAKE+3]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+4]  = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+5]  = 0;

		VERTICIES[i*FLOAT_PER_FLAKE+6]  = POSITIONS[i*2+0] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+7]  = POSITIONS[i*2+1] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+8]  = 0;

		VERTICIES[i*FLOAT_PER_FLAKE+9]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+10] = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+11] = 0;

		VERTICIES[i*FLOAT_PER_FLAKE+12] = POSITIONS[i*2+0] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+13] = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+14] = 0;

		VERTICIES[i*FLOAT_PER_FLAKE+15] = POSITIONS[i*2+0] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+16] = POSITIONS[i*2+1] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+17] = 0;
	}
}

void updateFlakeBuffer(deltaTime)
{
	for(i = 0; i < MAX_FLAKES; i++)
	{
		// Gravity
		POSITIONS[i*2+1] = POSITIONS[i*2+1] + MAX_SPEED * deltaTime;
		if(POSITIONS[i*2+1] - RADII[i] > _height) POSITIONS[i*2+1] = - RADII[i];

		VERTICIES[i*FLOAT_PER_FLAKE+1]  = POSITIONS[i*2+1] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+4]  = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+7]  = POSITIONS[i*2+1] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+10] = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+13] = POSITIONS[i*2+1] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+16] = POSITIONS[i*2+1] - RADII[i];

		// Wiggle
		continue;
		POSITIONS[i*2+0] = POSITIONS[i*2+1] + (MIN_SIZE - (((float)rand() / (float)RAND_MAX) * (MAX_SPEED * 2))) * deltaTime;

		VERTICIES[i*FLOAT_PER_FLAKE+0]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+3]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+6]  = POSITIONS[i*2+0] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+9]  = POSITIONS[i*2+0] - RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+12] = POSITIONS[i*2+0] + RADII[i];
		VERTICIES[i*FLOAT_PER_FLAKE+15] = POSITIONS[i*2+0] + RADII[i];
	}
}
