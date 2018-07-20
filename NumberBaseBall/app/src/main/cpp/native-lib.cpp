#include <jni.h>
#include <string>
#include<cstdio>
#include<cmath>
#include<time.h>

struct NODE{
    NODE* next, *prev;
    char value[4];
    NODE(){
        next = prev = NULL;
    }
} nodes[10000];

struct MYAL{
    int i;
    MYAL() {
        i = 0;
    }
    void clear(){
        i = 0;
    }

    NODE* alloc(){
        if(i >= 10000) return NULL;

        return &nodes[i++];
    }
}myal;

struct List{
    int size;

    NODE *head, *tail, *cursor;
    List(){
        head = myal.alloc();
        tail = myal.alloc();
        head->next = tail;
        tail->prev = head;
    }

    void insert(const char num[4]){
        NODE* nn = myal.alloc();
        memcpy(nn->value, num, sizeof(char)*4);

        nn->prev = tail->prev;
        nn->next = tail;

        tail->prev->next = nn;
        tail->prev = nn;
        size++;
    }

    void clear(){
        size = 0;
        head = myal.alloc();
        tail = myal.alloc();

        head->next = tail;
        tail->prev = head;
    }
    void setCursor(){
        cursor = head;
    }

    bool next(char num[4]){
        if(cursor->next == tail){
            return false;
        }

        cursor = cursor->next;
        memcpy(num, cursor->value, sizeof(char)*4);
        return true;
    }

    void del(){
        if(cursor == head) return;

        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        cursor = cursor->prev;
        size--;
    }
}list;

int nums[10] = {0,1,2,3,4,5,6,7,8,9};

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void setFirst(int depth, char num[4]){
    if(depth ==  4){
        for(int i = 0; i < depth; i++){
            num[i] = nums[i] + '0';
        }
        list.insert(num);
    }

    for(int i = depth; i < 10; i++){
        swap(nums[depth], nums[i]);
        setFirst(depth + 1, num);
        swap(nums[depth], nums[i]);
    }
}

void init(){
    myal.clear();
    list.clear();

    char num[4];
    for(int i = 1; i < 10; i++){
        swap(nums[0], nums[i]);
        setFirst(1, num);
        swap(nums[0], nums[i]);
    }
}

typedef struct QUERTY{
    int str, ball;
} QUERTY;

QUERTY ballAndStrike(const char numA[4], const char numB[4]){
    bool nums[10] = {false};
    int b= 0, s = 0;
    for(int i =0; i < 4; i++) {
        s += numA[i] == numB[i];
        nums[numA[i] - '0'] = true;
    }

    for(int i = 0; i < 4; i++){
        b += nums[numB[i]-'0'];
    }
    return {s, b - s};
}

char mynum[4];

extern "C"
{
    JNIEXPORT void  JNICALL
    Java_com_example_sd_numberbaseball_NumberBaseball_clear(
            JNIEnv *env,
            jobject thiz,
            jstring str
    ){
        const char* num = env->GetStringUTFChars(str, NULL);

        for(int i = 0; i < 4; i++) mynum[i] = num[i];
        env->ReleaseStringUTFChars(str,num);
        init();
    }

    JNIEXPORT jint  JNICALL
    Java_com_example_sd_numberbaseball_NumberBaseball_size(
            JNIEnv *env,
            jobject thiz
    ) {
        return list.size;
    }

    JNIEXPORT jstring  JNICALL
    Java_com_example_sd_numberbaseball_NumberBaseball_myQuery(
            JNIEnv *env,
            jobject thiz,
            jstring str
    ){
        const char* num = env->GetStringUTFChars(str, NULL);
        QUERTY query;

        query = ballAndStrike(mynum, num);

        env->ReleaseStringUTFChars(str,num);

        char res[7];
        res[0] = query.str + '0';
        res[1] = 'S';
        res[2] = ' ';
        res[3] = query.ball + '0';
        res[4] = 'B';
        res[5] = ' ';
        res[6] = 0;

        return env->NewStringUTF(res);
    }

    JNIEXPORT jstring  JNICALL
    Java_com_example_sd_numberbaseball_NumberBaseball_yourQuery(
            JNIEnv *env,
            jobject thiz,
            jstring str
    ){
        const char* num = env->GetStringUTFChars(str, NULL);
        QUERTY query;
        query.ball = num[5] - '0';
        query.str = num[4] - '0';

        char n[6], called[4];

        for(int i = 0; i < 4; i++) called[i] = num[i];

        env->ReleaseStringUTFChars(str,num);
        list.setCursor();

        while(list.next(n)){
            QUERTY q;
            q = ballAndStrike(n, called);
            if(q.ball != query.ball || q.str != query.str){
                list.del();
            }
        }

        n[0] = query.str + '0';
        n[1] = 'S';
        n[2] = ' ';
        n[3] = query.ball + '0';
        n[4] = 'B';
        n[5] = 0;
        return env->NewStringUTF(n);
    }

    JNIEXPORT jstring  JNICALL
    Java_com_example_sd_numberbaseball_NumberBaseball_whatNext(
            JNIEnv *env,
            jobject thiz
    ){
        char n[5];
        srand(time(NULL));

        if(list.size == 0) return env->NewStringUTF("false");

        int cnt = rand() % (list.size);
        cnt++;

        bool res = false;

        list.setCursor();
        while(cnt--) res = list.next(n);
        n[4] = 0;
        return env->NewStringUTF(res? n : "false");
    }
}