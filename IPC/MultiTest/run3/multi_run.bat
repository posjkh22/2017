
taskset -c 0 ./path1 1 799 multi &
taskset -c 1 ./path2 799 1596 multi2 &
taskset -c 2 ./path3 1596 3022 multi3 &

while [ 0 ]
do
	if [ -s ./shortest_way1.out -a -s ./shortest_way2.out -a -s ./shortest_way3.out ]
	then
		cp ./shortest_way1.out ./result
		cat ./shortest_way2.out >> ./result/shortest_way1.out
		cat ./shortest_way3.out >> ./result/shortest_way1.out
		break
	fi
done

rm shortest_way1.out
rm shortest_way2.out
rm shortest_way3.out
