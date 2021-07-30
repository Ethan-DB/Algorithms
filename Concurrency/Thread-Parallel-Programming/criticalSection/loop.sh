#!/bin/bash
echo > output
for varible1 in {1..1000}
do
  ./test >> output
done
