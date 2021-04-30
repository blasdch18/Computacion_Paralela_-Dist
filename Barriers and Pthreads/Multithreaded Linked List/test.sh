#!/bin/bash
threads=(1 2 4 8)
search_pct1=0.999
insert_pct1=0.0005
search_pct2=0.8
insert_pct2=0.1

for i in "${threads[@]}"; do
	echo "One mutex at the list******************"
	echo "num of threads"
	echo $i
	./pth_one_mutex $i $search_pct1 $insert_pct1
	echo " "
	
	echo "More inserts and deletes---------------"
	./pth_one_mutex $i $search_pct2 $insert_pct2
	echo " "
done

for i in "${threads[@]}"; do
	echo "One mutex per node*********************"
	echo "num of threads"
	echo $i
	./pth_mute_node $i $search_pct1 $insert_pct1
	echo " "
	
	echo "More inserts and deletes---------------"
	./pth_mute_node $i $search_pct2 $insert_pct2
	echo " "
done


for i in "${threads[@]}"; do
	echo "Read write locks************************"
	echo "num of threads"
	echo $i
	./pth_read_write $i $search_pct1 $insert_pct1
	echo " "
	
	echo "More inserts and deletes----------------"
	./pth_read_write $i $search_pct2 $insert_pct2
	echo " "
done