#!/bin/bash

./BubbleSort.x < test/in.dat > .tmp/BubbleSort.dat
diff test/exp.dat .tmp/BubbleSort.dat --color -q
	
./InsertionSort.x < test/in.dat > .tmp/InsertionSort.dat
diff test/exp.dat .tmp/InsertionSort.dat --color -q
	
./SelectionSort.x < test/in.dat > .tmp/SelectionSort.dat
diff test/exp.dat .tmp/SelectionSort.dat --color -q