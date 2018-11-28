/*
 * gcc -W -o standalone_espeak standalone_espeak.cpp  -lespeak

 * */

#include <stdio.h>
#include <string.h>
#include <espeak/speak_lib.h>
#include <thread>
#include <mutex>

#include <iostream>

#include "my_speak_lib.h"

/* Must be called before any synthesis functions are called.
   This specifies a function in the calling program which is called when a buffer of
   speech sound data has been produced.

   The callback function is of the form:

int SynthCallback(short *wav, int numsamples, espeak_EVENT *events);

   wav:  is the speech sound data which has been produced.
      NULL indicates that the synthesis has been completed.

   numsamples: is the number of entries in wav.  This number may vary, may be less than
      the value implied by the buflength parameter given in espeak_Initialize, and may
      sometimes be zero (which does NOT indicate end of synthesis).

   events: an array of espeak_EVENT items which indicate word and sentence events, and
      also the occurance if <mark> and <audio> elements within the text.  The list of
      events is terminated by an event of type = 0.


   Callback returns: 0=continue synthesis,  1=abort synthesis.
*/
//don't delete this callback function.
//int SynthCallback(short *wav, int numsamples, espeak_EVENT *events)
//{

//    return 0;
//}

bool newMessage;
AjnaSpeak roboSpeak;
std::mutex mtx;
std::thread real_time;
std::thread sequential;

void RealtimeProcessing(const char *message)
{
    mtx.lock();
    newMessage = false;
    mtx.unlock();
    roboSpeak.Speak(message,0);
    while(/*espeak_IsPlaying() && */!newMessage)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

void SpeakRealtime(const char *message)
{
    mtx.lock();
    newMessage = true;
    mtx.unlock();
    if(real_time.joinable())
        real_time.join();
    real_time = std::thread(RealtimeProcessing,message);
}

void SpeakSequential(const char *message)
{
    mtx.lock();
    newMessage = true;
    mtx.unlock();
    if(real_time.joinable())
        real_time.join();
    sequential = std::thread(&AjnaSpeak::Speak,roboSpeak,message,1);
    if(sequential.joinable())
        sequential.join();
}

int main(void)
{



    ////    std::thread first(&RobotSpeak::Speak,roboSpeak, " 123 hello, hello, hello world",1);
    ////    std::thread second(&RobotSpeak::Speak,roboSpeak, " 456 hello, hello, hello world",0);
    ////    roboSpeak.EndSpeak();
    ////    first.join();
    ////    second.join();

    ////    std::thread second(&RobotSpeak::Speak,roboSpeak, " 456 hello, hello, hello world",0);
    //    roboSpeak.Speak("456 hello, hello, hello world",0);
    //    std::this_thread::sleep_for(std::chrono::seconds(2));

    //    roboSpeak.Speak("789 hello, hello, hello world",1);
//    mtx.lock();
//    newMessage = true;
//    mtx.unlock();
//    std::thread real_time1(SpeakRealtime,"First Realtime 1 2 3");
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    mtx.lock();
//    newMessage = true;
//    mtx.unlock();
//    real_time1.join();
//    std::thread real_time2(SpeakRealtime,"Second Realtime 1 2 3");
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    mtx.lock();
//    newMessage = true;
//    mtx.unlock();
//    real_time2.join();
    SpeakRealtime("First Realtime 1 2 3");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    SpeakRealtime("Second Realtime 1 2 3");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    SpeakSequential("Third Sequential 1 2 3");
    SpeakRealtime("Fourth Realtime 1 2 3");
    SpeakSequential("Fifth Sequential 1 2 3");
    if(real_time.joinable())
        real_time.join();
    if(sequential.joinable())
        sequential.join();
    return 0;
}
