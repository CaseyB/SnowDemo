#ifndef __snow_renderer__
#define __snow_renderer__

#include <GLES/gl.h>

#define MAX_FLAKES 100
#define MAX_SPEED 0.08
#define MIN_SPEED 0

#define MIN_SIZE 8
#define MAX_SIZE 15

#define VERTS_PER_FLAKE 6
#define FLOAT_PER_FLAKE VERTS_PER_FLAKE * 2

class SnowRenderer
{
public:
	void onSurfaceCreated();
	void onSurfaceChanged(int width, int height);
	void onDrawFrame(long deltaTime);
	void setTextureId(int id);

private:
	void buildFlakeBuffer();
	void updateFlakeBuffer(long deltaTime);

	GLfloat _verticies[MAX_FLAKES * FLOAT_PER_FLAKE];
	GLshort _texCoords[MAX_FLAKES * FLOAT_PER_FLAKE];
	GLfloat _positions[MAX_FLAKES*2];
	GLfloat _radii[MAX_FLAKES];

	int texture;

	int _width, _height, i;
};

#endif
