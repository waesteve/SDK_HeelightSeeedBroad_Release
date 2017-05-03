package com.mseen.tools;

import android.content.Context;

import java.io.File;
import java.util.HashMap;

/**
 * Created by jiapeng on 02/05/2017.
 */

public class HeePlayerManager {
    public enum AudioCommandName {
        SWITCH, MODEL1, MODEL2, MODEL3, MODEL4, LIGHT, MORE
    }

    private HashMap<AudioCommandName, Object> commandsMap = new HashMap<>();

    private AudioCommandPlayer audioCommandPlayer = null;

    private HeePlayerManager() {
        //        commandsMap.put(AudioCommandName.ChooseGroupA,0);
        //开关，日光，夜灯，手电，more

        commandsMap.put(AudioCommandName.SWITCH, Integer.valueOf(40));
        commandsMap.put(AudioCommandName.MODEL1, "TYPE=8;GROUP=0;CT=" + 2700 + ";V=" + 100 + ";");
        commandsMap.put(AudioCommandName.MODEL2, "TYPE=8;GROUP=0;CT=" + 6500 + ";V=" + 100 + ";");
        commandsMap.put(AudioCommandName.MODEL3, Integer.valueOf(17));
        commandsMap.put(AudioCommandName.MODEL4, Integer.valueOf(32));
//      commandsMap.put(AudioCommandName.MODEL2, );
//      commandsMap.put(AudioCommandName.MODEL2, Integer.valueOf(17));
//      commandsMap.put(AudioCommandName.MODEL3, 32);
    }


    private static class HeePlayerManagerHolder {
        public static final HeePlayerManager heePlayerManagerInstance = new HeePlayerManager();
    }

    private Context mContext = null;
    public static HeePlayerManager getHeePlayerManager(Context context) {
        HeePlayerManagerHolder.heePlayerManagerInstance.audioCommandPlayer = AudioCommandPlayer.getAudioCommandPlayer(context.getApplicationContext());
        HeePlayerManagerHolder.heePlayerManagerInstance.mContext = context.getApplicationContext();
        return HeePlayerManagerHolder.heePlayerManagerInstance;
    }

    public void playAudioCommand(AudioCommandName command) {
        Object commandObj = commandsMap.get(command);
        if (commandObj instanceof Integer) {
            playShortAudioCommand(((Integer) commandObj).intValue());
        } else if (commandObj instanceof String) {
            playLongAudioCommand((String) commandObj);
//            playLongAudioCommandByJNI((String) commandObj);
        }
    }

    public AudioCommandPlayerSettings getAudioCommandPlayerSettings() {
        return audioCommandPlayer.getAudioCommandPlayerSettings();
    }

    public void playShortAudioCommand(int command) {
        //move audio creator
        final File wavFile = new File(mContext.getCacheDir(), "temp.wav");
        wavFile.delete();
        audioCommandPlayer.createShortControlPackageAudioMainFromJNI(command, wavFile.getAbsolutePath());
        audioCommandPlayer.playAudioFileDescriptor(wavFile, AudioCommandPlayerSettings.MIN_MEDIUM_PLAYAUDIO_INTERVAL);
    }

    @Deprecated
    public void playLongAudioCommand(String dataStr) {
        //move audio creator
        final File wavFile = new File(mContext.getCacheDir(), "temp.wav");
        wavFile.delete();
//        playLongAudioCommandByCommands(wavFile, dataStr);
        audioCommandPlayer.playLongAudioCommandByJNI(wavFile, dataStr);

        audioCommandPlayer.playAudioFileDescriptor(wavFile, AudioCommandPlayerSettings.MIN_MEDIUM_PLAYAUDIO_INTERVAL);
    }


}