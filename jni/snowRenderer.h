#ifndef __snow_renderer__
#define __snow_renderer__

void on_surface_created();
void on_surface_changed(int width, int height);
void on_draw_frame(long deltaTime);
void buildFlakeBuffer();
void updateFlakeBuffer();

#endif
