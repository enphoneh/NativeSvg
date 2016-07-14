//
// Created by HuangEnphone on 16/7/6.
//
#include "com_aven_nativesvg_NativeSvgUtils.h";
#include <android/log.h>

#define  LOG_TAG    "hyf"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , LOG_TAG, __VA_ARGS__)
JNIEXPORT void JNICALL Java_com_aven_nativesvg_NativeSvgUtils_getNativeBitmap
        (JNIEnv *env, jclass zthis, jstring sourceString) {
    const char *str;
    str = env->GetStringUTFChars(sourceString, false);
    if (str == NULL) {
        return;
    }
    jclass objClass = env->FindClass("com/aven/nativesvg/NativeSvgUtils");
    jmethodID mid = env->GetStaticMethodID(objClass, "onDataCallBack", "(C[F)V");
    jclass objClass3 = env->FindClass("com/aven/nativesvg/NativeSvgUtils");
    jmethodID mid3 = env->GetStaticMethodID(objClass3, "onPathFinish", "(Ljava/lang/String;)V");
    int sourceLength = strlen(str);
    char preOperate = ' ';
    float params[6] = {-1};
    int paramsIndex = 0;
    char cmd[20];
    bool isColor = false;
    char* color;
    memset(params, -1, 6);
    memset(cmd,'-',20);
    for (int i = 0; i < sourceLength; i++) {
        char cha = str[i];
        switch (cha) {
            case 'M':
            case 'm': {
                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {
                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
                break;
            }

            case 'C':
            case 'c':
            case 'S':
            case 's': {
                if (isColor) {
                    int cmdLength = strlen(cmd);
                    for (int j = 0; j < cmdLength; j++) {
                        if (cmd[j] == '-') {
                            cmd[j] = cha;
                            break;
                        }
                    }
                    break;
                }

                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {
                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
            }
                break;

            case 'Z':
            case 'z': {

                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {
                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
            }
                break;
            case 'L':
            case 'l': {
                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {

                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case 'A':
            case 'a': {
                if (isColor) {
                    int cmdLength = strlen(cmd);
                    for (int j = 0; j < cmdLength; j++) {
                        if (cmd[j] == '-') {
                            cmd[j] = cha;
                            break;
                        }
                    }
                    break;
                }
                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {
                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case 'Q':
            case 'T':
            case 'q':
            case 't': {
                if (preOperate != ' ') {
                    if (objClass != NULL && mid != NULL) {
                        jfloatArray array = env->NewFloatArray(6);
                        env->SetFloatArrayRegion(array,0,6,params);
                        env->CallStaticVoidMethod(objClass,mid, preOperate, array);
                        env->DeleteLocalRef(array);
                    }
                }
                memset(params, -1, 6);
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case '$':{
                jstring jcolor = env->NewStringUTF(color);
                env->CallStaticVoidMethod(objClass3,mid3, jcolor);
                env->DeleteLocalRef(jcolor);
                break;
            }

                break;
            case '@':{
                isColor = false;
                int len = 0;
                for (int j = 0; j < 20; j++) {
                    if (cmd[j] == '-') {
                        break;
                    }
                    len++;
                }
                if (len == 0) {
                    break;
                }
                if (color != NULL) {
                    free(color);
                    color = NULL;
                }
                color = (char*)malloc(len*sizeof(char));
                for (int j = 0; j < len; j++) {
                    color[j] = cmd[j];
                }
                memset(cmd, '-', 20);
                break;
            }

            case ' ': {
                int len = 0;
                for (int j = 0; j < 20; j++) {
                    if (cmd[j] == '-') {
                        break;
                    }
                    len++;
                }
                if (len == 0) {
                    break;
                }
                char strParam[len];
                for (int j = 0; j < len; j++) {
                    strParam[j] = cmd[j];
                }
                params[paramsIndex++] = atof(strParam);
                memset(cmd, '-', 20);
                break;
            }
            default: {
                if (cha == '#') {
                    isColor = true;
                }
                int cmdLength = strlen(cmd);
                for (int j = 0; j < cmdLength; j++) {
                    if (cmd[j] == '-') {
                        cmd[j] = cha;
                        break;
                    }
                }
                break;
            }
        }
    }
    jclass objClass2 = env->FindClass("com/aven/nativesvg/NativeSvgUtils");
    jmethodID mid2 = env->GetStaticMethodID(objClass, "onDataFinish", "()V");
    env->CallStaticVoidMethod(objClass,mid2);
    env->DeleteLocalRef(objClass);
    env->DeleteLocalRef(objClass2);
    env->DeleteLocalRef(objClass3);
}
