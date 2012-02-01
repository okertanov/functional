#!/bin/bash

convert image-0.jpg \
	-pointsize 48 -draw "text 10,550 '--XX--'" \
	-scale 91% -quality 30 image-XX.jpg 

for((i=0;$i<10;i=$(($i+1))));do
	ii=$(($i+1))
	Y=$(($ii*40))
	echo -n "$i "
	convert image-$i.jpg \
		-pointsize 48 -draw "text 10,$Y '--$i--'" \
		-scale 99% -quality 30 image-$ii.jpg 
done
