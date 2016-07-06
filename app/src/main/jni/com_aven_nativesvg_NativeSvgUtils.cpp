//
// Created by HuangEnphone on 16/7/6.
//
#include "com_aven_nativesvg_NativeSvgUtils.h";
#include <android/log.h>
#include "SkCanvas.h"

#define  LOG_TAG    "hyf"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , LOG_TAG, __VA_ARGS__)

JNIEXPORT jobject JNICALL Java_com_aven_nativesvg_NativeSvgUtils_getNativeBitmap
        (JNIEnv *env, jclass zthis, jstring sourceString) {
    //    SkCanvas* canv = GraphicsJNI::getNativeCanvas(env, canvasObj);
//    if (!canv)
//    {
//        return NULL;
//    }
//    SkPaint paint;
//    paint.setFlags(paint.kAntiAlias_Flag);
    const char *str;
    str = env->GetStringUTFChars(sourceString, false);
    if (str == NULL) {
        return NULL;
    }
    int sourceLength = strlen(str);
    char preOperate = ' ';
    float params[6] = {-1};
    int paramsIndex = 0;
    char cmd[20] = {'-'};
    memset(params, -1, sizeof(params));
    for (int i = 0; i < sourceLength; i++) {
        char cha = str[i];
        switch (cha) {
            case 'M':
            case 'm': {
                if (preOperate != ' ') {
//                                path.moveTo(params[0], params[1]);
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
                break;
            }

            case 'C':
            case 'c':
            case 'S':
            case 's': {

                if (preOperate != ' ') {
//                                path.cubicTo(params[0], params[1],params[2], params[3],params[4], params[5]);
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
            }
                break;

            case 'Z':
            case 'z': {

                if (preOperate != ' ') {
//                                path.close();
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
            }
                break;
            case 'L':
            case 'l': {
                if (preOperate != ' ') {
//                                path.lineTo(params[0], params[1]);
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case 'A':
            case 'a': {
                if (preOperate != ' ') {
//                                path.arcTo(params[0], params[1],params[2], params[3],params[4], params[5], false);
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case 'Q':
            case 'T':
            case 'q':
            case 't': {
                if (preOperate != ' ') {
//                                path.quadTo(params[0], params[1],params[2], params[3]);
                }

                memset(params, -1, sizeof(params));
                paramsIndex = 0;
                preOperate = cha;
                break;
            }
            case '$':

                break;
            case '@':
                break;

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
                memset(cmd, '-', sizeof(cmd));
                break;
            }
            default: {
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
    return NULL;
}

long fun(char *s) {
    int i, t;
    long sum = 0;
    for (i = 0; s[i]; i++) {
        if (s[i] <= '9')t = s[i] - '0';
        else t = s[i] - 'a' + 10;
        sum = sum * 16 + t;
    }
    return sum;
}