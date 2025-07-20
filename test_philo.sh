#!/bin/bash

echo "Test 1: 2 philosophers, enough time"
./philo 2 800 200 200
sleep 2

echo "Test 2: 5 philosophers, enough time"
./philo 5 800 200 200
sleep 2

echo "Test 3: 5 philosophers, short time_to_die"
./philo 5 300 200 200
sleep 2

echo "Test 4: 1 philosopher"
./philo 1 800 200 200
sleep 2

echo "Test 5: Invalid arguments"
./philo 0 800 200 200
./philo 5 -800 200 200