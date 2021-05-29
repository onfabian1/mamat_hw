#!/bin/bash

packets=`cat`

firewall_pkts=""

while read rule
do
	match_pkts=`echo "$packets"`
	#rule=`echo "$rule" | sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
	rule=`echo "$rule" | tr -d ' ' | sed '/^$/d' | grep -o '^[^#]*' | sed -r 's/'[,]+'/,/g' | sed -r 's/'^[,]'//g'`   #grep -o '^[a-z]' | grep -o '$[0-9]'`
	if [[ "$rule" == "" ]]; then
		continue
	fi

	IFS=',' read -ra arr <<< "$rule"
	for filter in "${arr[@]}"
	do
		match_pkts=`echo "$match_pkts" | ./firewall.exe "$filter"`
	done
	firewall_pkts+=`echo -e "${match_pkts}" | sed '/^[[:space:]]*$/d' | sort -u ` #| uniq -c  | grep -E "^ *${#arr[@]} " | sed -e "s/^ *${#rarr[@]} //"`
	firewall_pkts+="\n"

done <"$1"


echo -e "${firewall_pkts}" | sed '/^$/d' | tr -d ' ' | sort -u
