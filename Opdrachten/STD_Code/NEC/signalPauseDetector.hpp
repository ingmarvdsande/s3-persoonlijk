#include <iostream>
#include <chrono>
#include "rtos.hpp"
#include "hwlib.hpp"
#include "NecReceiver.hpp"

class TsopReceiver : public rtos::task<> {
    public:
        bool isSignalPresent();
};


class SignalPauseDetector : public rtos::task<> {
    enum state_t = {WaitingForPause, WaitingForSignal};

    private:
        state_t state    = WaitingForPause;
        
        NecReceiver& necReceiver;
        TsopReceiver& tsopReceiver;

        SignalPauseDetector(NecReceiver& necReceiver, TsopReceiver& tsopReceiver):
            necReceiver(necReceiver),
            tsopReceiver(tsopReceiver),
        {}

        T_MAX_PAUSE_US = 6000;
        
        void main() {
            for(;;) {
                switch(state) {
                    case WaitingForPause:
                        wait(100)
                        if(tstopReceiver.isSignalPresent())
                            {
                            t_signalUs+=100;
                            state = WaitingForPause;
                            }
                        else
                            {
                            necReceiver.pauseDetected(t_pauseUs);
                            t_signalUs = 0;
                            state = WaitingForSignal;
                            wait(100);
                            if (!tsopReceiver.isSignalPresent())
                                {
                                t_pauseUs+=100;
                                if (t_pauseUs > T_MAX_PAUSE_US)
                                    {
                                    necReceiver.pauseDetected(t_pauseUs);
                                    t_PauseUs = 0;
                                    state = WaitingForSignal;
                                    }
                                else
                                    {
                                    state = WaitingForSignal;
                                    }
                                }
                            else
                                {
                                necReceiver.pauseDetected(t_pauseUs);
                                t_signalUs = 0;
                                state = WaitingForPause;
                                }
                            }


                }
            }
        }
};
