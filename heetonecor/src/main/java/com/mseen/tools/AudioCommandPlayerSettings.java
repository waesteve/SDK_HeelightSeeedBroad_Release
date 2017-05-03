package com.mseen.tools;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Created by jiapeng on 02/05/2017.
 */

public class AudioCommandPlayerSettings {

    /**
     * SharedPeference
     */
    public static final String SP_SETTINGS = "SETTINGS";
    /**
     * SP key.
     */
    public static final String KEY_SETTINGS_AUDIOLEVLE = "KEY_SETTINGS_AUDIOLEVLE";

    public static final int AUDIO_LEVEL_LOW = 0;
    public static final int AUDIO_LEVEL_MEDIUM = 1;
    public static final int AUDIO_LEVEL_HIGH = 2;

    public static final int MIN_SHORT_PLAYAUDIO_INTERVAL = 300; // ms
    public static final int MIN_MEDIUM_PLAYAUDIO_INTERVAL = 600; // ms

    private int mAudioLevel = AUDIO_LEVEL_MEDIUM;

    private Context mContext = null;

    public AudioCommandPlayerSettings(Context mContext) {
        this.mContext = mContext;
    }

    /**
     * 设置默认的音阶大小
     *
     * @param audioLevel
     */
    public void setAudioLevel(int audioLevel) {
        SharedPreferences sp = mContext.getSharedPreferences(SP_SETTINGS, Context.MODE_PRIVATE);
        sp.edit().putInt(KEY_SETTINGS_AUDIOLEVLE, audioLevel).apply();
        mAudioLevel = audioLevel;
    }


    public int getAudioLevel() {
        SharedPreferences sp = mContext.getSharedPreferences(SP_SETTINGS, Context.MODE_PRIVATE);
        mAudioLevel = sp.getInt(KEY_SETTINGS_AUDIOLEVLE, AUDIO_LEVEL_MEDIUM);
        return mAudioLevel;
    }

    public float getAudioLevelScale() {
        switch (mAudioLevel) {
            case AUDIO_LEVEL_HIGH:
                return 1.0f;
            case AUDIO_LEVEL_LOW:
                return 0.1f;
            default:
                return 0.3f;
        }
    }

}
