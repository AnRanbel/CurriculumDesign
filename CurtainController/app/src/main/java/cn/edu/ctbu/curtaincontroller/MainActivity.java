package cn.edu.ctbu.curtaincontroller;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Looper;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AlertDialog;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

import static cn.edu.ctbu.curtaincontroller.ThemeActivity.app;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if(app!=null){
            if(app.thmeme==0){
                //使用默认主题
            }else {
                //使用自定义主题
                setTheme(app.thmeme);
            }
        }
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showDialog();
            }
        });

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);
    }

    /** 连接设备对话框 */
    private void showDialog(){
        final Timer t=new Timer();
        AlertDialog.Builder builder=new AlertDialog.Builder(this);
        builder.setIcon(R.mipmap.button_wifi_press);
        builder.setTitle("正在连接");
        builder.setMessage("正在连接，请勿关闭对话框");
        builder.setCancelable(true);
        builder.setPositiveButton("取消",
                new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        Toast.makeText(getApplicationContext(),"已取消连接",Toast.LENGTH_SHORT).show();
                        t.cancel();
                    }
                });
        final AlertDialog dialog=builder.create();
        dialog.show();
        //5秒后对话框消失
        t.schedule(new TimerTask() {
            @Override
            public void run() {
                dialog.dismiss();
                Looper.prepare();
                Toast.makeText(getApplicationContext(),"已成功连接",Toast.LENGTH_SHORT).show();
                Looper.loop();
                t.cancel();
            }
        },5000);
    }

    /** 点击返回键，关闭侧边栏 */
    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    /**
     * 此方法用于初始化菜单，其中menu参数就是即将要显示的Menu实例。
     * 返回true则显示该menu,false 则不显示;
     * 只会在第一次初始化菜单时调用)
     * 可另外添加item
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    /** 主界面头部工具条右部菜单被点击时调用 */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Intent i=new Intent(MainActivity.this,ThemeActivity.class);
            startActivity(i);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /** 侧边栏菜单被点击时调用 */
    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.nav_use_help) {
            Intent i=new Intent(MainActivity.this,UseHelpActivity.class);
            startActivity(i);
        } else if (id == R.id.nav_about_us) {
            Intent i=new Intent(MainActivity.this,AboutUsActivity.class);
            startActivity(i);
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }
}
