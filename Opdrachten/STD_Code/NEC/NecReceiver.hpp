#include <iostream>
#include <chrono>
#include "freertos.hpp"


class NecReceiver : public rtos::task<> {
    public:
        void pauseDetected(t_pauseUs);
        void signalDetected(t_signalUs);

        MessageReceiver& messageReceiver;

        rtos::channel signalChannel;
        rtos::channel pauseChannel;

    private:
        enum state_t = {WaitingForLeadSignal, WaitingForLeadPause, WaitingForBitPause};
        state_t state = WaitingForLeadSignal;

        T_LEADSIGNAL_MIN_US = 7000;
        T_LEADSIGNAL_MAX_US = 11000;
        T_LEADPAUSE_MIN_US = 3000;
        T_LEADPAUSE_MAX_US = 6000;
        T_BITPAUSE_MIN_US = 200;
        T_BITPAUSE_MAX_US = 2000;
        T_BITPAUSE_THRESHOLD_ZERO_ONE = 1100;

        NecReceiver(MessageReceiver& messageReceiver):
            messageReceiver(messageReceiver),
            signalChannel(this, "signalChannel"),
            pauseChannel(this, "pauseChannel")
        {}

        void extractMessage (uint64& msg, uint& nofBytes, uint64 m, uint n)
        {
            // revert bits:
            msg = 0; mloc=m;
            for (int i=0; i<n; i++)
            {
                msg<<(mloc&1);
                mloc=mloc>>1;
            }
            nofBytes = n/8;
        }

        void main() {
            for(;;) {
                    switch(state) {
                        case WaitingForLeadSignal;
                        t_signalUs = signalChannel.read();
                        if (t_signalUs > T_LEADSIGNAL_MIN_US && t_signalUs < T_LEADSIGNAL_MAX_US)
                            {
                            state = WaitingForLeadPause;
                            t_pauseUs = pauseChannel.read();
                            if (t_pauseUs > T_LEADPAUSE_MIN_US && t_pauseUs < T_LEADPAUSE_MAX_US)
                                {
                                n=0;
                                m=0;
                                state = WaitingForBitPause;
                                t_pauseUs = pauseChannel.read();
                                if (t_pauseUs > T_BITPAUSE_MIN_US && t_pauseUs < T_BITPAUSE_MAX_US)
                                    {
                                        m<<1;
                                        if (t_pauseUs > T_BITPAUSE_THRESHOLD_ZERO_ONE)
                                            {
                                            m|=1;
                                            n++
                                            state = WaitingForBitPause;
                                            }
                                        else
                                            {
                                                n++;
                                                state = WaitingForBitPause;
                                            }
                                    }
                                else
                                    {
                                    extractMessage(msg, nofBytes, m, n);
                                    messageReceiver.messageReceived(msg, nofBytes);
                                    state = WaitingForLeadSignal;
                                    }
                                }
                            else
                                {
                                state = WaitingForLeadSignal;
                                }
                            }
                    }
            }
        }
};