package org.moo.android.snowcodedemo;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.ViewGroup.LayoutParams;
import android.widget.FrameLayout;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 * 
 * @see SystemUiHider
 */
public class MainActivity extends Activity
{
	private FrameLayout _frame;
	private GLSurfaceView _surface;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		_frame = (FrameLayout)findViewById(R.id.main_frame);
		
		_surface = new GLSurfaceView(this);
		_surface.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
		_surface.setRenderer(new SnowRenderer());
		_surface.getHolder().setFormat(PixelFormat.TRANSLUCENT);
		_surface.setZOrderOnTop(true);
		_frame.addView(_surface, LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		_surface.onResume();
	}

	@Override
	protected void onPause()
	{
		_surface.onPause();
		super.onPause();
	}
}
