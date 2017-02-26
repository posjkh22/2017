
::build
make all
chmod 755 path

::move & copy
cp path ../Bin


cp path ../Test
cp map_loc_data.in ../Test
cp map_cnt_data.in ../Test
chmod 755 path

cp path ../MultiTest
cp map_cnt_multi_data.in ../MultiTest
cp map_loc_multi_data.in ../MultiTest
chmod 755 path

::multi_run test
cp path ../MultiTest/task1
cp map_cnt_multi_data.in ../MultiTest/task1
cp map_loc_multi_data.in ../MultiTest/task1

cp path ../MultiTest/task2
cp map_cnt_multi_data.in ../MultiTest/task2
cp map_loc_multi_data.in ../MultiTest/task2

