#!/bin/bash
# bc

#Считываем массив построчно (яндекс осуждает)
declare -a array
declare -a answers
input_file="$1"
N=0
OLDIFS=$IFS
IFS=','

while read user
do
	array+=("$user")
	N=$(($N + 1))	
done < "$input_file"
IFS=$OLDIFS

#Закидываем в одномерный массив
declare -a matrix
counter=0

for element in "${array[@]}"
do
	for i in $(echo $element | tr "," "\n")
	do
		matrix+=("$i")
	done
done
echo ${matrix[@]}

counter=0
while [ $counter -lt $N ]
do
	#Ищем строку с max элементом
	
	let " step = ($N+1)*$counter + $counter "
	max=${matrix[$step]}
	index=$counter
	
	for ((i=$(($counter + 1)); i<$N; i++))
	do
		if (( $(echo "${matrix[$(( ($N+1)*$i + $counter ))]} > $max" |bc -l) ));
		then
			max=${matrix[$(( ($N+1)*$i + $counter ))]}
			index=$i
		fi
	done
	
	#Перестановка строк
	
	for ((j=0; j<$N; j++))
	do
		temp=${matrix[$(( ($N+1)*$counter + $j ))]}
		matrix[$(( ($N+1)*$counter + $j ))]=${matrix[$(( ($N+1)*$index + $j ))]}
		matrix[$(( ($N+1)*$index + $j ))]=$temp
	done
	
	temp=${matrix[$(( ($N+1)*$counter + $N ))]}
	matrix[$(( ($N+1)*$counter + $N ))]=${matrix[$(( ($N+1)*$index + $N ))]}
	matrix[$(( ($N+1)*$index + $N ))]=$temp
	
	#Нормализация уравнений
	
	for ((i=$counter; i<$N; i++))
	do
	
		temp=${matrix[$(( ($N+1)*$i + $counter ))]}
		
		for ((j=0; j<$N; j++))
		do
			matrix[$(( ($N+1)*$i + $j ))]=$(bc<<<"scale=12;${matrix[$(( ($N+1)*$i + $j ))]}/$temp")
		done
		
		matrix[$(( ($N+1)*$i + $N ))]=$(bc<<<"scale=12;${matrix[$(( ($N+1)*$i + $N ))]}/$temp")
		
		if (( $i == $counter ));
		then
			continue
		fi
		
		for ((j=0; j<$N; j++))
		do
			
			matrix[$(( ($N+1)*$i + $j ))]=$(bc<<<"scale=12;(${matrix[$(( ($N+1)*$i + $j ))]})-(${matrix[$(( ($N+1)*$counter + $j ))]})")
		done
		matrix[$(( ($N+1)*$i + $N ))]=$(bc<<<"scale=12;(${matrix[$(( ($N+1)*$i + $N ))]})-(${matrix[$(( ($N+1)*$counter + $N ))]})")
	done
	
	counter=$(($counter + 1))
done

#Обратная подстановка

k=$(($N - 1))
while [ $k -ge 0 ] 
do
	answers[$k]=${matrix[$(( ($N+1)*$k + $N ))]}
	for ((i=0; i<$k; i++))
	do
		spec=$(bc<<<"scale=12;(${answers[$k]})*(${matrix[$(( ($N+1)*$i + $k ))]})")
		matrix[$(( ($N+1)*$i + $N ))]=$(bc<<<"scale=12;(${matrix[$(( ($N+1)*$i + $N ))]})-($spec)")
	done
	k=$(($k - 1))
done

for element in "${answers[@]}"
do
	echo $element
done
