#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_sd_ndk_1practice_NDKPractice_stringFromJNI(
        JNIEnv *env,
jobject /* this */) {
std::string hello = "Hello from C++";
return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_sd_ndk_1practice_NDKPractice_getMyData(
        JNIEnv *env, jobject) {
std::string hello = "SangDoLee";
return env->NewStringUTF(hello.c_str());
}