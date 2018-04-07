#!/bin/bash

seq 100000 199999 | nc localhost 9000 & 
seq 200000 299999 | nc localhost 9000 & 
seq 300000 399999 | nc localhost 9000 & 
seq 400000 499999 | nc localhost 9000 & 
seq 500000 599999 | nc localhost 9000 & 
seq 600000 699999 | nc localhost 9000 & 
seq 700000 799999 | nc localhost 9000 & 
seq 800000 899999 | nc localhost 9000 & 
seq 900000 999999 | nc localhost 9000 & 
seq 1000000 1099999 | nc localhost 9000 &
