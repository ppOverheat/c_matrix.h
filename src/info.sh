#!/bin/bash

RED='\033[1;31m'
GR='\033[1;32m'
NC='\033[0m'

info() {
    if [ "$(grep "Failures: 0" test.log)" == "" ]
    then
        echo -e "\n${RED}FAILED TEST CASES${NC}:"
        echo -e "${RED}-------------------------------------------------${NC}"
        echo -e "$(grep -A3 failure log.xml > temp.txt)"
        echo -e "${RED}$(grep id temp.txt | sed 's/<id>//' | sed 's/<.id>//')${NC}"
        echo -e "$(rm -f temp.txt)"
        echo -e "${RED}-------------------------------------------------${NC}"
        echo -e "${RED}FAIL${NC}: $(grep "Checks" test.log)"
        echo -e "${RED}-------------------------------------------------${NC}"
        
	else
        echo -e "${GR}-------------------------------------------------${NC}"
        echo -e "${GR}SUCCESS${NC}: $(grep "Checks" test.log)"
        echo -e "${GR}-------------------------------------------------${NC}"
	fi
}

info
