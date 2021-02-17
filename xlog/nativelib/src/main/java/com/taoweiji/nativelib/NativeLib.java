package com.taoweiji.nativelib;

import android.content.Context;

import com.tencent.mars.xlog.Log;
import com.tencent.mars.xlog.Xlog;

public class NativeLib {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


    public static void initXLog(Context context) {
        String logPath = context.getFilesDir().getAbsolutePath() + "/logsample/xlog";
        Xlog xlog = new Xlog();
        Log.setLogImp(xlog);
        Log.setConsoleLogOpen(true);
        Log.appenderOpen(Xlog.LEVEL_DEBUG, Xlog.AppednerModeAsync, "", logPath, "LOGSAMPLE", 0);
    }
}
