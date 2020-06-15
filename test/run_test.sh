#!/bin/bash

red=$(tput setaf 1)
green=$(tput setaf 2)
reset=$(tput sgr0)

echo "${green}Run testing${reset}"

./bin/test_math
if [[ $? != 0 ]]; then
  echo "${red}ERROR${reset}"
  exit 1;
fi

./bin/test_object
if [[ $? != 0 ]]; then
  echo "${red}ERROR${reset}"
  exit 1;
fi

./bin/test_utils
if [[ $? != 0 ]]; then
  echo "${red}ERROR${reset}"
  exit 1;
fi

echo "${green}PASSED${reset}"
