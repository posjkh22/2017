awk 'BEGIN {FS = ","}
	{ print $1, $2}' map_data.csv > map_data.in


make all

./graph > txt
