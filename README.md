# Q-Learning
Q-Learning is a model-free reinforcement learning algorithm which learns the value of an action in a particular state. It can be used to teach a program to learn based on letting explore and finding the best actions to perform based on the state it is at. In this example of Q-Learning, I am using Q-Learning to teach a program to find the shortest path from point A to point B within a graph of nodes:

![graph](https://github.com/sababot/qlearning/blob/master/q-learning-graph.jpeg?raw=true)

Reward Matrix:
```
        0    1    2    3    4    5    6    7
        ------------------------------------
 
0  |   -1    0   -1   -1   -1   -1   -1   -1
   |
1  |    0   -1    0   -1    0    0   -1   -1
   |
2  |   -1    0   -1    0    0   -1   -1   100
   |
3  |   -1   -1    0   -1   -1   -1   -1   -1
   |
4  |   -1    0    0   -1   -1    0   -1   100
   |
5  |   -1    0   -1   -1    0   -1    0   -1
   |
6  |   -1   -1   -1   -1   -1    0   -1   -1
   |
7  |   -1   -1    0   -1    0   -1   -1   100
```

# Setup
Clone this repository and in order to compile the program just run:

```g++ main.cpp utils.cpp```

# Future Work
In the near future, I will use this algorithm (or an algorithm based on this algorithm) to train the computer to drive cars on a narrow road.
