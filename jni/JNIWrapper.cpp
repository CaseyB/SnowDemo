#include "JNIWrapper.h"

#include "snowRenderer.h"

static SnowRenderer* renderer = NULL;

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

JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1surface_1changed(JNIEnv *env, jclass clazz, jint width, jint height)
{
	if(renderer)
	{
		renderer->onSurfaceChanged((int)width, (int)height);
	}
}

JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1draw_1frame(JNIEnv *env, jclass clazz, jlong deltaTime)
{
	if(renderer)
	{
		renderer->onDrawFrame((long)deltaTime);
	}
}

JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_set_1texture_1id(JNIEnv *env, jclass clazz, jint textureId)
{
	if(renderer)
	{
		renderer->setTextureId((int)textureId);
	}
}
