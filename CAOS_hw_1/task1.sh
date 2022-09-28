#!/bin/bash
IFS=:
while read file
do
	counter=0
		for path in $MANPATH;
		do	
			good_path=$path/man3/$file.3.gz
			not_at_all_good_path=$path/man3/$file.3
			
			if [ -e $good_path ];
			then
				echo $(gunzip -c $good_path | grep "#include" | sed -e 's/.*#include <//' | sed -e 's/>$//' | head -n 1)
				counter=$(($counter + 1))
			elif [ -e $not_at_all_good_path ];
			then
				#echo $not_at_all_good_path
				echo $(grep "#include" | sed -e 's/.*#include <//' | sed -e 's/>$//' | head -n 1)
				counter=$(($counter + 1))
			fi
		done
	if [ "$counter" -eq "0" ];
	then 
		echo "---"
	fi
done

#когда нет гз, когда нет библиотеки и когда нет файла
