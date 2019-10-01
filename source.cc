#include<stdio.h>
#include<string.h>
#include<cmath>
#include<string>
#include<omnetpp.h>

using namespace omnetpp;

class Source: public cSimpleModule
{
private:
    cMessage *event;
    simtime_t timeout;
    int pConstant;
    int pLambda;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Source);


/*
 * initialize() function of the source does the following:
 *      a. Create an event to send the packets on different intervals.
 *      b. Initialize the variables used in poisson distribution.
 *      c. Schedule the event.
 */
 void Source:: initialize() {
    event = new cMessage("event");
    pConstant = 10;
    pLambda = 5;
    scheduleAt(simTime(), event);
}

/*
 * handleMessage() function of the source does the following:
 *      a. Handle the event timeout
 *      b. Send the packet out at a variable bit rate using poisson distribution
 */
void Source:: handleMessage(cMessage *msg) {
    if (msg == event) {

        /* Calculate random time to send next job based on poisson distribution. */
                double pRandomTime = exp(pConstant * log(pLambda) - lgamma(pConstant + 1.0) - pLambda);

        scheduleAt(simTime()+pRandomTime, event);

        if(pConstant == 0)
                {
                    pConstant = 10;
                }
                else
                {
                pConstant = pConstant -1;
                }

        cMessage *msg = new cMessage("source_msg");
        send(msg,"out");
    }
}
