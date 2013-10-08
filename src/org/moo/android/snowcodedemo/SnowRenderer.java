package org.moo.android.snowcodedemo;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

import android.opengl.GLSurfaceView;

public class SnowRenderer implements GLSurfaceView.Renderer
{
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		JNIWrapper.on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		GL11 gl11 = (GL11)gl;
		gl11.glViewport(0, 0, width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl)
	{
		JNIWrapper.on_draw_frame();
	}
}
