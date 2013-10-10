#include "SnowRenderer.h"

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

void SnowRenderer::onSurfaceCreated()
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

void SnowRenderer::onSurfaceChanged(int width, int height)
{
	_width = width;
	_height = height;

	buildFlakeBuffer();

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, width, height, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SnowRenderer::onDrawFrame(long deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	updateFlakeBuffer(deltaTime);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _verticies);

	glDrawArrays(GL_TRIANGLES, 0, (MAX_FLAKES - 1) * FLOAT_PER_FLAKE);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void SnowRenderer::buildFlakeBuffer()
{
	LOGD("SnowRenderer", "Building Flakes");

	char buffer[50];

	for(i = 0; i < MAX_FLAKES; i++)
	{
		_radii[i] = MIN_SIZE + (float)rand() / ((float)RAND_MAX / (MAX_SIZE - MIN_SIZE));
		_positions[i*2+0] = (rand() / (float)RAND_MAX) * _width;
		_positions[i*2+1] = (rand() / (float)RAND_MAX) * _height;

		sprintf(buffer, "(%f, %f) radius: %f", _positions[i*2+0], _positions[i*2+1], _radii[i]);
		LOGD("SnowRenderer", buffer);

		_verticies[i*FLOAT_PER_FLAKE+0]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+1]  = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+2]  = 0;

		_verticies[i*FLOAT_PER_FLAKE+3]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+4]  = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+5]  = 0;

		_verticies[i*FLOAT_PER_FLAKE+6]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+7]  = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+8]  = 0;

		_verticies[i*FLOAT_PER_FLAKE+9]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+10] = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+11] = 0;

		_verticies[i*FLOAT_PER_FLAKE+12] = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+13] = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+14] = 0;

		_verticies[i*FLOAT_PER_FLAKE+15] = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+16] = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+17] = 0;
	}
}

void SnowRenderer::updateFlakeBuffer(long deltaTime)
{
	for(i = 0; i < MAX_FLAKES; i++)
	{
		// Gravity
		_positions[i*2+1] = _positions[i*2+1] + MAX_SPEED * deltaTime;
		if(_positions[i*2+1] - _radii[i] > _height) _positions[i*2+1] = - _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+1]  = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+4]  = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+7]  = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+10] = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+13] = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+16] = _positions[i*2+1] - _radii[i];

		// Wiggle
		_positions[i*2+0] = _positions[i*2+0] + (MAX_SPEED - (((float)rand() / (float)RAND_MAX) * (MAX_SPEED * 2))) * deltaTime;

		_verticies[i*FLOAT_PER_FLAKE+0]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+3]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+6]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+9]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+12] = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+15] = _positions[i*2+0] + _radii[i];
	}
}
