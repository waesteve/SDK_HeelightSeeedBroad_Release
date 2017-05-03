package com.mseen.tools;

import android.app.Activity;
import android.content.Context;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.util.Log;

import java.io.File;
import java.io.FileDescriptor;

/**
 * Created by jiapeng on 5/18/15.
 */
class AudioCommandPlayer {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void createLongControlPackageAudioMainFromJNI(long value, String wavFile);

    public native void createShortControlPackageAudioMainFromJNI(int value, String wavFile);



    private AudioCommandPlayer() {

    }

    int mStreamType = AudioManager.STREAM_MUSIC;
    int mMaxVolumn = 0;
    int mCurVolumn = 0;

    private long prePlayAudioTime = 0L;

    private Context mContext = null;

    private MediaPlayer mp = null;

    private AudioManager mAudioManager = null;

    private IAudioCommandPlayerListener playerListener = null;

    private static AudioCommandPlayer mAudioCommandPlayer = null;

    private AudioCommandPlayerSettings mAudioCommandPlayerSettings = null;

    protected AudioCommandPlayerSettings getAudioCommandPlayerSettings() {
        return mAudioCommandPlayerSettings;
    }

    public void setPlayerListener(IAudioCommandPlayerListener playerListener) {
        this.playerListener = playerListener;
    }
    private void init(Context context){
        mContext = context;
        mAudioManager = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);
        mAudioCommandPlayerSettings = new AudioCommandPlayerSettings(context);
    }

    protected static class AudioCommandPlayerHolder{
        public static final AudioCommandPlayer audioCommandPlayerInstance = new AudioCommandPlayer();
    }

    static AudioCommandPlayer getAudioCommandPlayer(Context context) {
        if (mAudioCommandPlayer == null) {
            mAudioCommandPlayer = AudioCommandPlayerHolder.audioCommandPlayerInstance;
            mAudioCommandPlayer.init(context.getApplicationContext());
        }

        if (context instanceof Activity) {
            //应用在前台，使用音乐播放器的音量控制
            mAudioCommandPlayer.mStreamType = AudioManager.STREAM_MUSIC;
        } else {
            //TODO 判断APP是否在前台.
            mAudioCommandPlayer.mStreamType = AudioManager.STREAM_SYSTEM;
            mAudioCommandPlayer.mCurVolumn = mAudioCommandPlayer.mAudioManager.getStreamVolume(AudioManager.STREAM_SYSTEM);
            if (mAudioCommandPlayer.mCurVolumn == 0) {
                int tempVolumn = mAudioCommandPlayer.mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
                if (tempVolumn != 0) {
                    mAudioCommandPlayer.mStreamType = AudioManager.STREAM_MUSIC;
                }
            }
        }
        mAudioCommandPlayer.mCurVolumn = mAudioCommandPlayer.mAudioManager.getStreamVolume(mAudioCommandPlayer.mStreamType);
        mAudioCommandPlayer.mMaxVolumn = mAudioCommandPlayer.mAudioManager.getStreamMaxVolume(mAudioCommandPlayer.mStreamType);

        return mAudioCommandPlayer;
    }


    private void playAudioPart1() {
        if ((mCurVolumn / (float) mMaxVolumn) < 0.2f) {
            //TODO Toast need more clever
//            Toast.makeText(mContext, mContext.getString(R.string.notice_audio_tooLow), Toast.LENGTH_SHORT).show();
//            return;
            playerListener.noticeAudioTooSmall();
        }
        if (mp == null) {
            mp = new MediaPlayer();
        }
        if (mp.isPlaying()) {
            mp.stop();
            mp.release();
            mp = new MediaPlayer();
        }

        float volumeMax = mAudioCommandPlayerSettings.getAudioLevelScale();
        mp.setVolume(volumeMax, volumeMax);
        // mp.setDataSource(descriptor.getFileDescriptor());
        mp.setAudioStreamType(mAudioCommandPlayer.mStreamType);

        Log.d("audiolevel", "playShortAudioCommand: VolumnMax:" + volumeMax);

    }

    private void playAudioPart2() {
        mp.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {

            @Override
            public void onCompletion(MediaPlayer m) {
                mp.release();
                mp = null;
            }
        });
        mp.setOnErrorListener(new MediaPlayer.OnErrorListener() {
            @Override
            public boolean onError(MediaPlayer m, int what, int extra) {
                mp.release();
                mp = null;
                return false;
            }
        });

        mp.start();
    }

    private void playAudioFileDescriptor(FileDescriptor descriptor, long startOffset, long length, int interval) {
        if ((System.currentTimeMillis() - prePlayAudioTime) < interval) {
            return;
        }
        try {
            playAudioPart1();
            mp.setDataSource(descriptor, startOffset, length);
            mp.prepare();
            playAudioPart2();
        } catch (Exception e) {
            e.printStackTrace();
        }

        prePlayAudioTime = System.currentTimeMillis();
    }

    protected void playAudioFileDescriptor(File file, int interval) {
        if ((System.currentTimeMillis() - prePlayAudioTime) < interval) {
            return;
        }
        try {
            playAudioPart1();
            mp.setDataSource(file.getAbsolutePath());
            mp.prepare();
            playAudioPart2();
        } catch (Exception e) {
            e.printStackTrace();
        }
        prePlayAudioTime = System.currentTimeMillis();
    }

}
