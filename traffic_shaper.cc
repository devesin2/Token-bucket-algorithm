#include<stdio.h>
#include<string.h>
#include<omnetpp.h>

using namespace omnetpp;

class Channel: public cSimpleModule
{
private:
    int max_tokens;
    int token_num;
    simtime_t timeout;
    cMessage *event;
    cQueue queue;
    int max_queue_size;

public:
    Channel();
    virtual ~Channel();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

Define_Module(Channel);

Channel::Channel()
{
    event = nullptr;
}

Channel::~Channel()
{
    cancelAndDelete(event);
}

/*
 * The initialize() function of the traffic shaper does the following task
 * 1. Initialize maximum token limit
 * 2. Initialize maximum size of the queue
 * 3. Schedule token event
 */
void Channel:: initialize() {
    max_tokens = par("token_limit");
    max_queue_size = par("queue_limit");
    token_num = 0;
    timeout = 0.1;
    queue.setName("my_queue");
    event = new cMessage("event");
    scheduleAt(simTime()+timeout, event);
}

/*
 *The handleMessage() function does the following task
 * 1. Handle the packets received from source
 * 2. Handle the token event
 * 3. Send the packets stored in queue according to the token value and no. of packets
 */
void Channel:: handleMessage(cMessage *msg) {
    if(msg == event) {
            /* Increment the token number and check if there are packets in the queue. */
            if (token_num < max_tokens) {
            token_num = token_num + 1;
            }

            /*
             * 1. Check if there are packet in the queue.
             * 2. Check if there are tokens available in the queue.
             * 3. If both the above specified condtions are true then send the packet to sink.
             */
            while(!queue.isEmpty() && token_num) {
                cMessage *new_msg;
                new_msg = (cMessage *)queue.pop();
                send(new_msg, "out");
                token_num = token_num - 1;
            }
            scheduleAt(simTime()+timeout, event);
    } else {
        /* Store the packets received in the queue. */
        EV << "Message received from source\n";
        if (queue.getLength() < max_queue_size) {
        EV <<"Inserting data in queue\n";
        queue.insert(msg);
        }

        /*
         * 1. Check if there are packet in the queue.
         * 2. Check if there are tokens available in the queue.
         * 3. If both the above specified condtions are true then send the packet to sink.
         */
        while(!queue.isEmpty() && token_num) {
            cMessage *new_msg;
            new_msg = (cMessage *)queue.pop();
            send(new_msg, "out");
            token_num = token_num - 1;
        }
    }
}

