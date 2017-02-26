
taskset -c 0 ./task1/path 1 799 multi &
taskset -c 1 ./task2/path 799 3022 multi2 &

while [ 0 ]
do
	if [ -s ./shortest_way1.out -a -s ./shortest_way2.out ]
	then
		cp ./shortest_way1.out ./result
		cat ./shortest_way2.out >> ./result/shortest_way1.out
		exit
	fi
done

rm ./task1/shortest_way1.out
rm ./task1/shortest_way2.out
