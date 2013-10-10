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

	glEnable(GL_TEXTURE_2D);
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

	glBindTexture(GL_TEXTURE_2D, texture);

	updateFlakeBuffer(deltaTime);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, _verticies);
	glTexCoordPointer(2, GL_SHORT, 0, _texCoords);

	glDrawArrays(GL_TRIANGLES, 0, MAX_FLAKES * VERTS_PER_FLAKE);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void SnowRenderer::setTextureId(int id)
{
	texture = id;
}

void SnowRenderer::buildFlakeBuffer()
{
	for(i = 0; i < MAX_FLAKES; i++)
	{
		_radii[i] = MIN_SIZE + (float)rand() / ((float)RAND_MAX / (MAX_SIZE - MIN_SIZE));
		_positions[i*2+0] = (rand() / (float)RAND_MAX) * _width;
		_positions[i*2+1] = (rand() / (float)RAND_MAX) * _height;

		_verticies[i*FLOAT_PER_FLAKE+0]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+1]  = _positions[i*2+1] - _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+2]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+3]  = _positions[i*2+1] + _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+4]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+5]  = _positions[i*2+1] - _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+6]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+7]  = _positions[i*2+1] + _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+8]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+9]  = _positions[i*2+1] + _radii[i];

		_verticies[i*FLOAT_PER_FLAKE+10] = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+11] = _positions[i*2+1] - _radii[i];




		_texCoords[i*FLOAT_PER_FLAKE+0]  = 0;
		_texCoords[i*FLOAT_PER_FLAKE+1]  = 0;

		_texCoords[i*FLOAT_PER_FLAKE+2]  = 0;
		_texCoords[i*FLOAT_PER_FLAKE+3]  = 1;

		_texCoords[i*FLOAT_PER_FLAKE+4]  = 1;
		_texCoords[i*FLOAT_PER_FLAKE+5]  = 0;

		_texCoords[i*FLOAT_PER_FLAKE+6]  = 0;
		_texCoords[i*FLOAT_PER_FLAKE+7]  = 1;

		_texCoords[i*FLOAT_PER_FLAKE+8]  = 1;
		_texCoords[i*FLOAT_PER_FLAKE+9]  = 1;

		_texCoords[i*FLOAT_PER_FLAKE+10] = 1;
		_texCoords[i*FLOAT_PER_FLAKE+11] = 0;
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
		_verticies[i*FLOAT_PER_FLAKE+3]  = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+5]  = _positions[i*2+1] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+7] = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+9]  = _positions[i*2+1] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+11] = _positions[i*2+1] - _radii[i];

		// Wiggle
		_positions[i*2+0] = _positions[i*2+0] + (MAX_SPEED - (((float)rand() / (float)RAND_MAX) * (MAX_SPEED * 2))) * deltaTime;

		_verticies[i*FLOAT_PER_FLAKE+0]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+2]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+4]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+6]  = _positions[i*2+0] - _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+8]  = _positions[i*2+0] + _radii[i];
		_verticies[i*FLOAT_PER_FLAKE+10] = _positions[i*2+0] + _radii[i];
	}
}
