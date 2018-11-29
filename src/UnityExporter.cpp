// Copyright 2018 Dimension NXG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "UnityExporter.h"
#ifdef LIB_WITH_UNITY

extern "C" void AjnaSpeak_Stop()
{
    speaker.StopSpeak();

}

extern "C" void AjnaSpeak_Sequential(char* message)
{
    if (message)
        speaker.SpeakSequential(message);
}

extern "C" bool AjnaSpeak_NotSequential(char* message)
{
    //if (message)
       // speaker.SpeakNotSequential(message);
    return true;
}


extern "C" bool AjnaSpeak_Realtime(char* message)
{
    if (message)
        speaker.SpeakRealtime(message);
    return true;
}
#endif


