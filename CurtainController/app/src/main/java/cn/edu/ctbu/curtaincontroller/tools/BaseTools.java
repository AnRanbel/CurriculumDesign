package cn.edu.ctbu.curtaincontroller.tools;

import android.content.Context;
import android.util.DisplayMetrics;
import android.view.WindowManager;

public class BaseTools {
	
	public static int getWindowWidth(Context context){
		// ��ȡ��Ļ�ֱ��ʡ�����
		WindowManager wm = (WindowManager) (context.getSystemService(Context.WINDOW_SERVICE));
		DisplayMetrics dm = new DisplayMetrics();
		int mScreenWidth = dm.widthPixels;
		return mScreenWidth;
	}
	
	public static int getWindowHeigh(Context context){
		// ��ȡ��Ļ�ֱ��ʡ�����
		WindowManager wm = (WindowManager) (context.getSystemService(Context.WINDOW_SERVICE));
		DisplayMetrics dm = new DisplayMetrics();
		int mScreenHeigh = dm.heightPixels;
		return mScreenHeigh;
	}
}
