#include "JNIWrapper.h"

#include "snowRenderer.h"

static SnowRenderer* renderer = NULL;

/*
 * Class:     org_moo_android_snowcodedemo_JNIWrapper
 * Method:    on_surface_created
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1surface_1created(JNIEnv *env, jclass clazz)
{
	if(renderer)
	{
		delete renderer;
		renderer = NULL;
	}

	renderer = new SnowRenderer();
	renderer->onSurfaceCreated();
}

/*
 * Class:     org_moo_android_snowcodedemo_JNIWrapper
 * Method:    on_surface_changed
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1surface_1changed(JNIEnv *env, jclass clazz, jint width, jint height)
{
	if(renderer)
	{
		renderer->onSurfaceChanged((int)width, (int)height);
	}
}

/*
 * Class:     org_moo_android_snowcodedemo_JNIWrapper
 * Method:    on_draw_frame
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1draw_1frame(JNIEnv *env, jclass clazz, jlong deltaTime)
{
	if(renderer)
	{
		renderer->onDrawFrame((long)deltaTime);
	}
}
