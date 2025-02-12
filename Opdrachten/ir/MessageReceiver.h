#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Logger.h>
#include "NecReceiver.h"

namespace crt
{
    extern ILogger& logger;

class MessageReceiver : public Task
	{
private:
    Queue<uint64_t, 20> messageQueue; 
public:
    MessageReceiver(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber) :
        Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), messageQueue(this)
    {
        start();
    }

    void messageReceived(uint32_t msg, uint32_t nofBytes)
    {
        uint64_t combinedValue = (uint64_t)msg | (((uint64_t)nofBytes) << 32);
        messageQueue.write(combinedValue);
    }

    void convert32bitTobitString(uint32_t value, char* buffer, int bufferLength)
    {
        int nofCharsToegevoegd = 0;
        for(int i=0; i<32; i++)
        {
            buffer[nofCharsToegevoegd++] = (value & (1<<31)) ? '1' : '0';
            value <<= 1;
            if(i %8 == 7){
                buffer[nofCharsToegevoegd++] = ' ';
            }
        }
        buffer[nofCharsToegevoegd] = 0;
    }

    void performAction(uint32_t msg) {
    switch (msg) {
        case 0x1:
            logger.logText("Action: Turning light ON");
            
            break;
        case 0x2: 
            logger.logText("Action: Turning light OFF");
            break;
        default:
            logger.logText("Unknown action for message:");
            logger.logUint32(msg);
            break;
    }
}
	private:
    void main(){
        vTaskDelay(1000);
        char bitString[39];
        for(;;){
            vTaskDelay(1);
            uint64_t messageData;
            messageQueue.read(messageData);
            uint32_t msg = messageData & 0xFFFFFFFF;
            uint32_t nofBytes = messageData >> 32;
            logger.logText("Message received");
            logger.logUint32(nofBytes);
            logger.logUint32(msg);
            
            convert32bitTobitString(msg, bitString, 33);
            logger.logText(bitString);
            logger.logText("End of message");

            performAction(msg);
        }
    }
	}; 
};// end namespace crt

