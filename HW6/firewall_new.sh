#!/bin/bash

packets='cat'

firewall_pkts=""

while read rule
do
	match_pkts=""

	rule=`echo "$rule" | tr -d ' ' | grep -o '^[^#]*'` | sed -r 's/[,]+/,/g' | sed -r 's/^[,]//g'    #grep -o '^[a-z]' | grep -o '$[0-9]' 
	if [[ "$rule" == "" ]]; then
		continue
	fi
	IFS=',' read -ra rule_array <<< "$rule"
	for filter in "${rule_array[@]}"
	do
		#echo "$packets" | valgrind --leak-check=full ./firewall.exe "$filter" 2>&1 | grep ERROR
		match_pkts=echo "$packets"
    	match_pkts=`./firewall.exe "$filter" < "$match_pkts"`
	done
	firewall_pkts+=`echo -e "${match_pkts}" | sed '/^[[:space:]]*$/d' | sort | uniq -c  | grep -E "^ *${#rule_array[@]} " | sed -e "s/^ *${#rule_array[@]} //"`
	firewall_pkts+="\n"
done 


echo -e "${firewall_pkts}" | sed '/^[[:space:]]*$/d' | tr -d ' ' | sort
