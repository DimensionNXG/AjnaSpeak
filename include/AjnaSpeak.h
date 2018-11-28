#pragma once
#include <thread>
#include <mutex>
#include <espeak/speak_lib.h>
#include "SpeakUtility.h"
class AjnaSpeak
{
    private:

    bool newMessage;
    SpeakUtility speakUtility;
    std::mutex mtx;
    std::thread real_time;
    std::thread sequential;

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

    AjnaSpeak(){};
    ~AjnaSpeak(){};



    void SpeakRealtime(const char *message)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        mtx.lock();
        newMessage = true;
        mtx.unlock();
        if(real_time.joinable())
            real_time.join();
        real_time = std::thread(&AjnaSpeak::RealtimeProcessing, this,message);
    }

    void SpeakSequential(const char *message)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        mtx.lock();
        newMessage = true;
        mtx.unlock();
        if(real_time.joinable())
            real_time.join();
        sequential = std::thread(&SpeakUtility::Speak,speakUtility,message,1);
        if(sequential.joinable())
            sequential.join();
    }

    void StopSpeak()
    {
        if(real_time.joinable())
            real_time.join();
        if(sequential.joinable())
            sequential.join();
    }
};
