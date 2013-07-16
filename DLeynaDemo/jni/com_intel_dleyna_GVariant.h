/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_intel_dleyna_GVariant */

#ifndef _Included_com_intel_dleyna_GVariant
#define _Included_com_intel_dleyna_GVariant
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    refSink
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_dleyna_GVariant_refSink
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    unref
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_intel_dleyna_GVariant_unref
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newBooleanNative
 * Signature: (Z)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newBooleanNative
  (JNIEnv *, jclass, jboolean);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newUInt32Native
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newUInt32Native
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newDoubleNative
 * Signature: (D)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newDoubleNative
  (JNIEnv *, jclass, jdouble);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newStringNative
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newStringNative
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newObjectPathNative
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newObjectPathNative
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    newArrayNative
 * Signature: ([Lcom/intel/dleyna/GVariant;J)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_newArrayNative
  (JNIEnv *, jclass, jobjectArray, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getBooleanNative
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_intel_dleyna_GVariant_getBooleanNative
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getUInt32Native
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_intel_dleyna_GVariant_getUInt32Native
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getDoubleNative
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_intel_dleyna_GVariant_getDoubleNative
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getStringNative
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_intel_dleyna_GVariant_getStringNative
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getArrayOfDoubleNative
 * Signature: (J)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_com_intel_dleyna_GVariant_getArrayOfDoubleNative
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getArrayOfStringNative
 * Signature: (J)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_com_intel_dleyna_GVariant_getArrayOfStringNative
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getChildValueNative
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_com_intel_dleyna_GVariant_getChildValueNative
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_intel_dleyna_GVariant
 * Method:    getTypeStringNative
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_intel_dleyna_GVariant_getTypeStringNative
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
