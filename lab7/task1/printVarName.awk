#! /usr/bin/awk -f

#in Terminal
awk 'BEGIN { for(i = 0; i < ARGC - 1; i++) { printf "ARGV[%d] = %s\n", i, ARGV[i] } } ' v1 v2 v3 v4
