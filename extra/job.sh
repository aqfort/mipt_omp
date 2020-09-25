#!/bin/bash

for ((i = 50; i <= 500; i += 10))
do
./a.out $i
done

for ((i = 550; i <= 1000; i += 50))
do
./a.out $i
done

./a.out 1500
./a.out 2000
