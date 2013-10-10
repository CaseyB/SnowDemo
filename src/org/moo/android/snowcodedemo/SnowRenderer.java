package org.moo.android.snowcodedemo;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class SnowRenderer implements GLSurfaceView.Renderer
{
	private long _lastTime, _currentTime, _deltaTime;

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		JNIWrapper.on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		JNIWrapper.on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl)
	{
		_currentTime = System.currentTimeMillis();
		if(_lastTime != 0) _deltaTime = _currentTime - _lastTime;

		JNIWrapper.on_draw_frame(_deltaTime);
		
		_lastTime = _currentTime;
	}
}
