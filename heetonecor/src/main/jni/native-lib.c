#include <jni.h>
#include "createLongControlPackageAudioMain.h"

JNIEXPORT jstring JNICALL
Java_com_mseen_tools_AudioCommandPlayer_stringFromJNI(JNIEnv *env, jobject instance) {

    char *hello = "Hello from C";
    return (*env)->NewStringUTF(env, hello);

}

JNIEXPORT void JNICALL
Java_com_mseen_tools_AudioCommandPlayer_createLongControlPackageAudioMainFromJNI(JNIEnv *env,
                                                                                 jobject instance,
                                                                                 jstring dataStr_,
                                                                                 jstring wavFile_) {
    const char *dataStr = (*env)->GetStringUTFChars(env, dataStr_, 0);
    const char *wavFile = (*env)->GetStringUTFChars(env, wavFile_, 0);

    doCreateMain(dataStr,wavFile);

    (*env)->ReleaseStringUTFChars(env, dataStr_, dataStr);
    (*env)->ReleaseStringUTFChars(env, wavFile_, wavFile);
}

JNIEXPORT void JNICALL
Java_com_mseen_tools_AudioCommandPlayer_createShortControlPackageAudioMainFromJNI(JNIEnv *env,
                                                                                  jobject instance,
                                                                                  jint value,
                                                                                  jstring wavFile_) {
    const char *wavFile = (*env)->GetStringUTFChars(env, wavFile_, 0);

    doCreateShortCommand( value, wavFile);

    (*env)->ReleaseStringUTFChars(env, wavFile_, wavFile);
}