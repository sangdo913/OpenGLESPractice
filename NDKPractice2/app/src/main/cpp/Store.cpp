//
// Created by SD on 2018-07-13.
//
#include <jni.h>
#include<cstring>
#include<malloc.h>

const int MAX_SIZE = 10000;

enum class STORE_TYPE{
    INTEGER, STRING
};

struct DATA{
    int key;
    char * mString;
    STORE_TYPE type;

    DATA(){
        mString = NULL;
    }

    ~DATA(){
        if(mString) free(mString);
    }
} datas[MAX_SIZE];
using namespace std;


extern "C"
{
    JNIEXPORT jint JNICALL
    Java_com_example_sd_ndkpractice2_Store_add(
            JNIEnv *env,
            jobject thiz,
            jint a,
            jint b
    ) {
        return a + b;
    }

    JNIEXPORT jint JNICALL
    Java_com_example_sd_ndkpractice2_Store_mul(
            JNIEnv *env,
            jobject thiz,
            jint a,
            jint b
    ) {
        return a * b;
    }

    JNIEXPORT jstring JNICALL
    Java_com_example_sd_ndkpractice2_Store_getString(
            JNIEnv *env,
            jobject thiz,
            jint key
    ){
        if(key >= MAX_SIZE) return NULL;
        if(datas[key].mString == NULL) return NULL;

        return env->NewStringUTF(datas[key].mString);
    }

    JNIEXPORT void JNICALL
    Java_com_example_sd_ndkpractice2_Store_setString(
            JNIEnv *env,
            jobject thiz,
            jint key, jstring str

    ) {
        const char *temp = env->GetStringUTFChars(str, NULL);

        if(datas[key].mString){
            free(datas[key].mString);
        }

        int len = env->GetStringUTFLength(str);

        datas[key].mString = (char*)(malloc(sizeof(char)*(len + 1)));

        memcpy(datas[key].mString, temp, sizeof(char)*(len + 1));

        env->ReleaseStringUTFChars(str, temp);
    }
}
