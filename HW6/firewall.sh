#!/bin/bash

packets='cat'

firewall_pkts=""

while read rule
do
	
	rule=`echo "$rule" | tr -d ' ' | sed '/^$/d' | grep -o '^[^#]*'`
	#rule=`echo "$rule" | tr -d ' ' | grep -o '^[^#]*'` | sed -r 's/[,]+/,/g' | sed -r 's/^[,]//g'    #grep -o '^[a-z]' | grep -o '$[0-9]' 
	if [[ -n $rule ]]; then
	IFS=',' read -ra arr <<< "$rule"
	match_pkts=`echo "$packets" | ./firewall.exe "${arr[0]}" | ./firewall.exe "${arr[1]}"` 
	match_pkts=`echo "$match_pkts"| ./firewall.exe "${arr[2]}" | ./firewall.exe "${arr[3]}"`
	#for filter in "${rule_array[@]}"
	#do
		#echo "$packets" | valgrind --leak-check=full ./firewall.exe "$filter" 2>&1 | grep ERROR
		#match_pkts=echo "$packets"
    	#match_pkts=`./firewall.exe "$filter" < "$match_pkts"`
	#done
	firewall_pkts+=`echo -e "${match_pkts}" |  tr -d ' ' | sort -u`
	firewall_pkts+="\n"
	fi
	
done < "$1"


echo -e "${firewall_pkts}" | sed '/^[[:space:]]*$/d' | tr -d ' ' | sort -u
