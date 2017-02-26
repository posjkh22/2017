
rem build

gcc -o map_loc_multi_data map_loc_multi_data.c
./map_loc_multi_data

gcc -DNEXT -o map_loc_multi_data map_loc_multi_data.c
./map_loc_multi_data

gcc -o map_cnt_multi_data map_cnt_multi_data.c
./map_cnt_multi_data

gcc -DNEXT -o map_cnt_multi_data map_cnt_multi_data.c
./map_cnt_multi_data


rem  move

mv map_cnt_multi_data.in ..
mv map_cnt_multi_data2.in ..
mv map_loc_multi_data.in ..
mv map_loc_multi_data2.in ..
