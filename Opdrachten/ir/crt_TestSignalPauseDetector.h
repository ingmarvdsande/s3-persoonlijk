#pragma once
#include <crt_CleanRTOS.h>
#include "NecReceiver.h"
namespace crt
{
    extern ILogger& logger;

class TsoplrReceiver{
    public:
    int inputPin;
    bool isSignalPresent(){
        bool pinValue = digitalRead(inputPin);
        return !pinValue;
    }
    TsoplrReceiver() : inputPin(15){
        pinMode(inputPin, INPUT);
    }
};

class SignalPauseDetector : public Task {
enum State{WaitingForPause, WaitingForSignal};
State state = WaitingForPause;
private:
TsoplrReceiver tsoplrReceiver;
Timer sleepTimer;
NecReceiver& necReceiver;
public: 
    SignalPauseDetector(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, NecReceiver& necReceiver) :
            Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), sleepTimer(this), necReceiver(necReceiver)
            {
                start();
            }

private:

void main(){
    vTaskDelay(1000);
    uint32_t t_signalUs = 0;
    uint32_t t_pauseUs = 0;
    uint32_t T_MAX_PAUSE_US = 6000;
    for(;;){
        switch(state)
        {
            case WaitingForPause:
                sleepTimer.sleep_us(100);
                if(tsoplrReceiver.isSignalPresent()){
                    t_signalUs+=100;
                    state = WaitingForPause;
                } else {
                    necReceiver.signalDetected(t_signalUs);
                    // logger.logText("Signal detected");
                    // logger.logUint32(t_signalUs);
                    t_pauseUs = 0; 
                    state = WaitingForSignal;
                }
            break;

            case WaitingForSignal:
                sleepTimer.sleep_us(100);
                if(!tsoplrReceiver.isSignalPresent()){
                    t_pauseUs+=100;
                    if(t_pauseUs > T_MAX_PAUSE_US){
                        necReceiver.pauseDetected(t_pauseUs);
                        // logger.logText("PauseDetected detected");
                        // logger.logUint32(t_pauseUs);;
                        t_pauseUs = 0;
                        state = WaitingForSignal;
                    }
                    else{
                        state = WaitingForSignal;
                    }
                }
                else{
                necReceiver.pauseDetected(t_pauseUs);
                    // logger.logUint32(t_pauseUs);
                    t_signalUs = 0;
                    state = WaitingForPause;
                }   
               
               
            break;
        }
            
                
    }
}
};
}
