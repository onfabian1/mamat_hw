#!/bin/bash
rm -f url.txt
wget -q https://www.premierleague.com/players
grep -oP "/players/([0-9]+)/(([a-zA-Z]+)|([a-zA-Z]+)-([a-zA-Z]+))/overview" players > url.txt
total=$(grep -oP "/players/([0-9]+)/(([a-zA-Z-]+))/overview" players | wc -l) 
echo Total Players: $total >> results.csv
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' url.txt
while read -r line
do
	x=$(wget -qO- $line | grep -P "([mM]idfielder)+" | wc -w)
	if [ $x -gt 0 ]
	then
		echo $line, Midfielder, $x >> results.csv
	fi
done < url.txt
