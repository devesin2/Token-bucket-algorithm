# Token-bucket-algorithm

The objective of this project is to model, simulate, and analyze token bucket algorithm.
Station-A is sending packets towards Station-B via the Traffic Shaper. The traffic from Station-A is randomly generated following 
Poisson distribution. That is, the inter-arrival time between packets is Poisson distributed and hence is of variable packet rate. 
The traffic shaper will queue the incoming packets from A and then “schedule” them at a constant bit rate towards Station-B. Thus 
the traffic between Station A and the Traffic Shaper is VBR(Variable Bit Rate), while between the Traffic Shaper and Station-B is 
CBR(Constant Bit Rate). The traffic Shaper must be based on token bucket algorithm.

The queue inside the Traffic Shaper should be a FIFO queue with a fixed size and constant service time. Set the output rate of the 
Traffic Shaper to some constant value x pps (packets per second) while experiment with
  1. Different mean inter-arrival times from Station-A towards the Traffic Shaper.
  2. Different size of the token bucket (β) to control maximum burst size
  3. Different token rates (p)
  4. Etc.
  
  Reference for the project:
  ---------------------------
  1. Simulation manual of omnet++.
