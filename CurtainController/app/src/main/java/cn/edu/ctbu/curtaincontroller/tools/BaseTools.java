package cn.edu.ctbu.curtaincontroller.tools;

import android.content.Context;
import android.util.DisplayMetrics;
import android.view.WindowManager;

public class BaseTools {
	
	public static int getWindowWidth(Context context){
		// 获取屏幕分辨率——宽
		WindowManager wm = (WindowManager) (context.getSystemService(Context.WINDOW_SERVICE));
		DisplayMetrics dm = new DisplayMetrics();
		int mScreenWidth = dm.widthPixels;
		return mScreenWidth;
	}
	
	public static int getWindowHeigh(Context context){
		// 获取屏幕分辨率——高
		WindowManager wm = (WindowManager) (context.getSystemService(Context.WINDOW_SERVICE));
		DisplayMetrics dm = new DisplayMetrics();
		int mScreenHeigh = dm.heightPixels;
		return mScreenHeigh;
	}
}
