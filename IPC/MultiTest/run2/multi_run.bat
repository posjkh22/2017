
::taskset -c 0,2 ./path1 1 799 multi &
::taskset -c 1,3 ./path2 799 3022 multi2 &
./path1 1 799 multi
./path2 799 3022 multi2

while [ 0 ]
do
	if [ -s ./shortest_way1.out -a -s ./shortest_way2.out ]
	then
		cp ./shortest_way1.out ./result
		cat ./shortest_way2.out >> ./result/shortest_way1.out
		break
	fi
done

rm shortest_way1.out
rm shortest_way2.out
