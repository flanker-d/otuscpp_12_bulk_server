#!/bin/bash

seq 0 300 | nc localhost 9000 & 
cat test1 | nc localhost 9000 & 
cat test2 | nc localhost 9000 & 
cat test3 | nc localhost 9000 & 
cat test4 | nc localhost 9000 &

