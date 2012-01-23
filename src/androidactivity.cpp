#include <jni.h>
#include <errno.h>

#include <android/log.h>
//#include <android_native_app_glue.h>

#include "Driver.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
//
//
///**
// * This is the main entry point of a native application that is using
// * android_native_app_glue.  It runs in its own thread, with its own
// * event loop for receiving input events and doing other things.
// */
//void android_main(struct android_app* state) {
//    // Make sure glue isn't stripped.
////    app_dummy();
//
//    LOGI("App started.");
//
//    testLibraries(10);
//}

#include "mother.h"

#include <sstream>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jstring JNICALL Java_com_mfoot_mathlibtest_HelloJNI_test(JNIEnv* env, jobject thisobj) {
    LOGI("App started.");

    unsigned long seed = 104000;
    double random = Mother(&seed);
    std::stringstream ss;
    ss << "random number was '" << random << "'.";
    testLibraries(10);

    return(env->NewStringUTF(ss.str().c_str()));

    if(random != 0) {
        return (*env).NewStringUTF("got non-zero value from JNI !");
    }

}
#ifdef __cplusplus
}
#endif

