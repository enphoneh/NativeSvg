package com.aven.nativesvg;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.RectF;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.ImageView;

/**
 **/
public class svgImageView extends ImageView  implements NativeSvgUtils.NativeSvgListener{
    public svgImageView(Context context) {
        super(context);
        initParams();
        initView();
    }

    public svgImageView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initParams();
        initView();
    }

    public svgImageView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initParams();
        initView();
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public svgImageView(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        initParams();
        initView();
    }

    private void initView() {
        mTime = System.currentTimeMillis();
        NativeSvgUtils.registerNativeSvgListener(MainActivity.class.getName(), this);
        NativeSvgUtils.getNativeBitmap(SvgDarwable.planet);
    }

    private Path mPath;
    private int mColor;
    private Bitmap mBitmap;
    private Paint mPaint;
    private Canvas mCanvas;
    private long mTime;

    private void initParams() {
        mPath = new Path();
        mPaint = new Paint();
        mPaint.setAntiAlias(true);
        Bitmap.Config config = Bitmap.Config.ARGB_8888;
        mBitmap = Bitmap.createBitmap(512,512,config);
        mCanvas = new Canvas(mBitmap);
    }

    @Override
    public void onDataCallBack(char cmd, float[] params) {
        switch (cmd) {
            case 'M':
            case 'm':
                mPath.moveTo(params[0], params[1]);
                break;

            case 'C':
            case 'c':
            case 'S':
            case 's':
                mPath.cubicTo(params[0], params[1],params[2], params[3],params[4], params[5]);
                break;

            case 'Z':
            case 'z':
                mPath.close();
                break;
            case 'L':
            case 'l':
                mPath.lineTo(params[0], params[1]);
                break;
            case 'A':
            case 'a':
                mPath.arcTo(new RectF(params[0], params[1],params[2], params[3]),params[4], params[5]);
                break;
            case 'Q':
            case 'T':
            case 'q':
            case 't':
                mPath.quadTo(params[0], params[1],params[2], params[3]);
                break;
        }
    }

    @Override
    public void onPathFinish(String color) {
        mPaint.setColor(Color.parseColor(color));
        mCanvas.drawPath(mPath, mPaint);
        mPath.reset();
    }

    @Override
    public void onDataFinish() {
        Log.e("hyf", "pharse time = " + (System.currentTimeMillis() - mTime));
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        long time = System.currentTimeMillis();
        canvas.drawBitmap(mBitmap,0,0,new Paint());
        Log.e("hyf", "onDraw time = " + (System.currentTimeMillis() - time));
    }
}
