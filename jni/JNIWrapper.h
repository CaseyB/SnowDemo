#ifndef __JNI_WRAPPER__
#define __JNI_WRAPPER__

#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1surface_1created(JNIEnv*, jclass);
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1surface_1changed(JNIEnv*, jclass, jint, jint);
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_on_1draw_1frame(JNIEnv*, jclass, jlong);
JNIEXPORT void JNICALL Java_org_moo_android_snowcodedemo_JNIWrapper_set_1texture_1id(JNIEnv*, jclass, jint);
};

#endif
