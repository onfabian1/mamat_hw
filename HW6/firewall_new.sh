#!/bin/bash

packets=`cat`

firewall_pkts=""

while read rule
do
	match_pkts=""
	#rule=`echo "$rule" | sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
	rule=`echo "$rule" | tr -d ' ' | sed '/^$/d' | grep -o '^[^#]*' | sed 's/'[,]+'/,/g' | sed 's/'^[,]'//g'`   #grep -o '^[a-z]' | grep -o '$[0-9]'`
	if [[ "$rule" == "" ]]; then
		continue
	fi

	IFS=',' read -ra arr <<< "$rule"
			#echo "$packets" | valgrind --leak-check=full ./firewall.exe "${arr[0]}" 2>&1 
		 #   echo "$packets" | valgrind --leak-check=full ./firewall.exe "${arr[1]}" 2>&1 
		  #  echo "$packets" | valgrind --leak-check=full ./firewall.exe "${arr[2]}" 2>&1 
		  #  echo "$packets" | valgrind --leak-check=full ./firewall.exe "${arr[3]}" 2>&1 
	match_pkts=`echo "$packets" | ./firewall.exe "${arr[0]}" | ./firewall.exe "${arr[1]}"` 
	match_pkts=`echo "$match_pkts"| ./firewall.exe "${arr[2]}" | ./firewall.exe "${arr[3]}"`
	firewall_pkts+=`echo -e "${match_pkts}" | sed '/^[[:space:]]*$/d' | sort -u ` #| uniq -c  | grep -E "^ *${#arr[@]} " | sed -e "s/^ *${#rarr[@]} //"`
	firewall_pkts+="\n"

done <"$1"


echo -e "${firewall_pkts}" | sed '/^$/d' | tr -d ' ' | sort -u
