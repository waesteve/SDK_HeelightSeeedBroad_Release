package com.mseen.tools;
import android.content.Context;

import java.io.File;

/**
 * 声控码发射器.
 * Created by jiapeng on 02/05/2017.
 */

public class TonecorPlayerManager {

    private AudioCommandPlayer audioCommandPlayer = null;

    private TonecorPlayerManager() {
    }


    private static class HeePlayerManagerHolder {
        public static final TonecorPlayerManager heePlayerManagerInstance = new TonecorPlayerManager();
    }

    private Context mContext = null;

    /**
     * 获取一个单例TonecorPlayerManager
     * @param context
     * @return
     */
    public static TonecorPlayerManager getTonecorPlayerManager(Context context) {
        HeePlayerManagerHolder.heePlayerManagerInstance.audioCommandPlayer = AudioCommandPlayer.getAudioCommandPlayer(context.getApplicationContext());
        HeePlayerManagerHolder.heePlayerManagerInstance.mContext = context.getApplicationContext();
        return HeePlayerManagerHolder.heePlayerManagerInstance;
    }

    /**
     * 播放器设置
     * @return
     */
    public AudioCommandPlayerSettings getAudioCommandPlayerSettings() {
        return audioCommandPlayer.getAudioCommandPlayerSettings();
    }


    /**
     * 设置声音异常提示（播放器崩溃，声音太小等）
     * @param playerListener
     */
    public void setPlayerListener(IAudioCommandPlayerListener playerListener) {
        HeePlayerManagerHolder.heePlayerManagerInstance.audioCommandPlayer.setPlayerListener( playerListener);
    }

    /**
     * 发送9bit 控制码
     * @param command
     */
    public void playShortAudioCommand(int command) {
        //move audio creator
        final File wavFile = new File(mContext.getCacheDir(), "temp.wav");
        wavFile.delete();
        audioCommandPlayer.createShortControlPackageAudioMainFromJNI(command, wavFile.getAbsolutePath());
        audioCommandPlayer.playAudioFileDescriptor(wavFile, AudioCommandPlayerSettings.MIN_MEDIUM_PLAYAUDIO_INTERVAL);
    }

    /**
     * 发送36bit 控制码
     * @param value
     */
    public void playLongAudioCommand(long value) {
        //move audio creator
        final File wavFile = new File(mContext.getCacheDir(), "temp.wav");
        wavFile.delete();

        audioCommandPlayer.createLongControlPackageAudioMainFromJNI(value, wavFile.getAbsolutePath());

        audioCommandPlayer.playAudioFileDescriptor(wavFile, AudioCommandPlayerSettings.MIN_MEDIUM_PLAYAUDIO_INTERVAL);
    }


}