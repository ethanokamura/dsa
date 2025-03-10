set up

check next transition

if nfa
  check next transition if -1
  copy string
  for loop for each epsilon outcome




nondeterministic
states 9
inputs 2
start 0
accepting 4 6
transitions
0 1 0
1 2 1
2 3 -1
3 4 1
2 5 -1
5 6 0



create a queue of inputs
while !q.empty
  input = q.front
  handle transition from current state to next state
  if (epsilon transition with new current state)
    follow all the paths with a copy of that queue to see if it accepts
  q.pop
check if accepted