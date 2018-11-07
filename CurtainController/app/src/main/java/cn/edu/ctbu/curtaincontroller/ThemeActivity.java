package cn.edu.ctbu.curtaincontroller;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

//** 切换app主题 */
public class ThemeActivity extends Activity {

    public static MyApplication app;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app=(MyApplication)ThemeActivity.this.getApplication();
        if(app.thmeme==0){
            //使用默认主题
        }else {
            //使用自定义主题
            setTheme(app.thmeme);
        }
        setContentView(R.layout.change_theme);
        initView();
    }

    private void initView() {
        ImageView back_img=(ImageView)findViewById(R.id.back);
        back_img.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });

        View theme_1=findViewById(R.id.skin_01);
        theme_1.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                app.thmeme=R.style.AppTheme;
                finish();
                overridePendingTransition(0,0); //切换Activity时没有过渡动画
                Intent i=new Intent(ThemeActivity.this,MainActivity.class);
                startActivity(i);
            }
        });

        View theme_2=findViewById(R.id.skin_02);
        theme_2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                app.thmeme=R.style.AppTheme_2;
                finish();
                overridePendingTransition(0,0); //切换Activity时没有过渡动画
                Intent i=new Intent(ThemeActivity.this,MainActivity.class);
                startActivity(i);
            }
        });

        View theme_3=findViewById(R.id.skin_03);
        theme_3.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                app.thmeme=R.style.AppTheme_3;
                finish();
                overridePendingTransition(0,0); //切换Activity时没有过渡动画
                Intent i=new Intent(ThemeActivity.this,MainActivity.class);
                startActivity(i);
            }
        });

        View theme_4=findViewById(R.id.skin_04);
        theme_4.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                app.thmeme=R.style.AppTheme_4;
                finish();
                overridePendingTransition(0,0); //切换Activity时没有过渡动画
                Intent i=new Intent(ThemeActivity.this,MainActivity.class);
                startActivity(i);
            }
        });

        View theme_5=findViewById(R.id.skin_05);
        theme_5.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                app.thmeme=R.style.AppTheme_5;
                finish();
                overridePendingTransition(0,0); //切换Activity时没有过渡动画
                Intent i=new Intent(ThemeActivity.this,MainActivity.class);
                startActivity(i);
            }
        });
    }
}
