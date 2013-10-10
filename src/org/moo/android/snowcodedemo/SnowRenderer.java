package org.moo.android.snowcodedemo;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;

public class SnowRenderer implements GLSurfaceView.Renderer
{
	private Context _context;
	private long _lastTime, _currentTime, _deltaTime;
	
	public SnowRenderer(Context context)
	{
		_context = context;
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		JNIWrapper.on_surface_created();
		loadTexture(gl, _context);
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
	
	private void loadTexture(GL10 gl, Context context)
	{
		int[] textures = new int[1];

        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.flake);

        gl.glGenTextures(1, textures, 0);
        gl.glBindTexture(GL10.GL_TEXTURE_2D, textures[0]);

        // create nearest filtered texture
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);

        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
        bitmap.recycle();
        
        JNIWrapper.set_texture_id(textures[0]);
    }
}
