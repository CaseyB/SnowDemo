#include "snowRenderer.h"

void on_surface_created()
{
	glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
}

void on_surface_changed()
{

}

void on_draw_frame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
