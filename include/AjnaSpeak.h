#pragma once
#include <thread>
#include <mutex>
#include <espeak/speak_lib.h>
#include <unistd.h>
#include "SpeakUtility.h"
class AjnaSpeak
{
    private:

    bool newMessage;
    SpeakUtility speakUtility;
    std::mutex mtx;
    std::thread real_time;
    std::thread sequential;
 bool IsRealTime=false;
    void RealtimeProcessing(const char *message)
    {
        mtx.lock();
        newMessage = false;
        mtx.unlock();
        speakUtility.Speak(message,0);
        while(espeak_IsPlaying() && !newMessage)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        espeak_Cancel();

    }

    public:

    AjnaSpeak(){}
    ~AjnaSpeak(){}


    void SpeakNotSequential(char *message)
    {
        if(espeak_IsPlaying() && IsRealTime)
        {
            espeak_Cancel();
            speakUtility.Speak(message,1);
        }
        else
        {
            speakUtility.Speak(message,0);
        }
            IsRealTime=true;
    }
    void SpeakRealtime(char *message)
    {
        if(espeak_IsPlaying() && IsRealTime)
        {
            espeak_Cancel();
            speakUtility.Speak(message,1);
        }
        else
        {
            speakUtility.Speak(message,0);
        }
            IsRealTime=true;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//        mtx.lock();
//        newMessage = true;
//        mtx.unlock();
//        if(real_time.joinable())
//            real_time.join();
//        real_time = std::thread(&AjnaSpeak::RealtimeProcessing, this,message);
    }

    void SpeakSequential(char *message)
    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//        mtx.lock();
//        newMessage = true;
//        mtx.unlock();
//        if(real_time.joinable())
//            real_time.join();
//        sequential = std::thread(&SpeakUtility::Speak,speakUtility,message,1);
//        if(sequential.joinable())
//            sequential.join();


//        if(!speakUtility.IsSpeaking())
//        {
//            speakUtility.Speak(message,1);
//        }
//        else
//        {
//            usleep(1000);
//            SpeakSequential(message);
//        }
        if(!espeak_IsPlaying())
         {
             speakUtility.Speak(message,1);
         }
         else if(espeak_IsPlaying())
         {
            if(!IsRealTime)
            {
                 usleep(1000);
                 SpeakSequential(message);
            }
            else
            {
                espeak_Cancel();
                speakUtility.Speak(message,1);
            }
         }
        IsRealTime=false;
    }

    void StopSpeak()
    {
        if(real_time.joinable())
            real_time.join();
        if(sequential.joinable())
            sequential.join();
    }
};
