/*
 * gcc -W -o standalone_espeak standalone_espeak.cpp  -lespeak

 * */

#include <stdio.h>
#include <string.h>



#include <iostream>

#include "SpeakUtility.h"
#include "AjnaSpeak.h"


#ifndef LIB_WITH_UNITY
int main(void)
{

    AjnaSpeak speaker;

    speaker.SpeakRealtime("30");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    speaker.SpeakRealtime("28");
    speaker.SpeakSequential("Target Detected at 27300 meters");
    speaker.SpeakSequential("Target hostile");
    speaker.SpeakSequential("Weapons free");
    speaker.SpeakRealtime("26");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    speaker.SpeakRealtime("24");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    speaker.SpeakRealtime("22");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    speaker.SpeakRealtime("20");

    speaker.StopSpeak();
    return 0;
}
#endif
