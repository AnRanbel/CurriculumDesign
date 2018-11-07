package cn.edu.ctbu.curtaincontroller;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import static cn.edu.ctbu.curtaincontroller.ThemeActivity.app;

public class AboutUsActivity extends Activity {
    @Override
    protected void onCreate(Bundle saveInstanceState){
        super.onCreate(saveInstanceState);
        if(app!=null){
            if(app.thmeme==0){
                //使用默认主题
            }else {
                //使用自定义主题
                setTheme(app.thmeme);
            }
        }
        setContentView(R.layout.about_us);
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
    }
}
