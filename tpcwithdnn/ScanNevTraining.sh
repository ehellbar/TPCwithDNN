#!/bin/bash

Nev_arr=(500 1000 1500 2000 5000);

for i in "${!Nev_arr[@]}" ; do
	echo "python steer_analysis.py --Nev ${Nev_arr[$i]}";
	python steer_analysis.py --Nev ${Nev_arr[$i]};
done

echo "Done!";
