#pragma once
#include <crt_CleanRTOS.h>
#include "crt_TestSignalPauseDetector.h"
#include "MessageReceiver.h"

namespace crt
{
    extern ILogger& logger;

class NecReceiver : public Task{
    enum State{WaitingForLeadSignal, WaitingForLeadPause, WaitingForBitPause};
    State state = WaitingForLeadSignal;

private:
    Queue<uint32_t, 30> pauseChannel;
    Queue<uint32_t, 30> signalChannel;
public:
    MessageReceiver& messageReceiver;

    NecReceiver(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, MessageReceiver& messageReceiver) :
        Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), pauseChannel(this), signalChannel(this), messageReceiver(messageReceiver)
        {

            start();
        }
        

    void signalDetected(uint32_t t_us) {
        if (t_us > T_LEAD_SIGNAL_MIN_US) {
            signalChannel.clear();
            pauseChannel.clear();
        }
        signalChannel.write(t_us);
        // if (!success) {
        //     logger.logText("Signal channel write failed: queue full");
        // }
    }

    void pauseDetected(uint32_t t_us) {
        pauseChannel.write(t_us);
        // if (!success) {
        //     logger.logText("Pause channel write failed: queue full");
        // }
    }


    void extractMessage (uint32_t &msg, uint32_t &nofBytes, uint32_t m, uint32_t n){
        // revert bits:
        msg = 0; 
        for(int i=0; i<n; i++){
            msg |=  (m&1)<<i;
            m >>= 1;
        }
        nofBytes = n/8;
    }

    const int T_LEAD_SIGNAL_MIN_US = 7000;
    const int T_LEAD_SIGNAL_MAX_US = 11000;
    const int T_LEAD_PAUSE_MIN_US = 3000;
    const int T_LEAD_PAUSE_MAX_US = 6000;
    const int T_BITPAUSE_MIN_US = 200;
    const int T_BITPAUSE_MAX_US = 2000;
    const int T_BITPAUSE_THRESHOLD_ZERO_ONE = 1100;

private:
    void main(){
        vTaskDelay(1000);
        uint32_t t_pauseUs = 0;
        uint32_t t_signalUs = 0;
        int32_t m = 0;
        int32_t n = 0;

        for(;;){
            switch(state){

                case WaitingForLeadSignal:
                    // logger.logText("Waiting for lead signal");
                    signalChannel.read(t_signalUs);
                    if(t_signalUs>T_LEAD_SIGNAL_MIN_US && t_signalUs < T_LEAD_SIGNAL_MAX_US){
                        state = WaitingForLeadPause;
                    }
                break;
                
                case WaitingForLeadPause:
                    // logger.logText("Waiting for lead pause");
                    pauseChannel.read(t_pauseUs);
                    if(t_pauseUs>T_LEAD_PAUSE_MIN_US && t_pauseUs<T_LEAD_PAUSE_MAX_US){
                        n = 0;
                        m = 0;
                        state = WaitingForBitPause;
                    }
                    else{
                        state = WaitingForLeadSignal;
                    }
                break;
                
                
                case WaitingForBitPause:
                    // logger.logText("Waiting for bit pause");
                    pauseChannel.read(t_pauseUs);
                    n++;
                    state = WaitingForBitPause;
                    if((t_pauseUs > T_BITPAUSE_MIN_US) && (t_pauseUs < T_BITPAUSE_MAX_US)){
                        m = m << 1;
                        if(t_pauseUs > T_BITPAUSE_THRESHOLD_ZERO_ONE){
                            m |= 1;
                        }
                        else{
                            n++;
                            state = WaitingForBitPause;
                        }
                    } 
                    else{
                        uint32_t msg = 0;
                        uint32_t nofBytes = 0;
                        extractMessage(msg, nofBytes, m, n);
                        messageReceiver.messageReceived(msg,nofBytes);
                        // logger.logText("Message received");
                        // logger.logUint32(nofBytes);
                        // logger.logUint32(msg);
                        // logger.logText("End of message");
                        state = WaitingForLeadSignal;
                    }
                break;
            


            }
        }
    }
}; // end class 
};// end namespace crt
