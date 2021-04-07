#!/bin/bash
wget  https://www.premierleague.com/players
grep -P "/players/([0-9]+)/(([a-zA-Z]+)|([a-zA-Z]+)-([a-zA-Z]+))/overview" players
