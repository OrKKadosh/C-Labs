#! /usr/bin/awk -f

BEGIN	{ FS = " "} 
	{ if (/English/) 
		{ count = count + 1 }
	}
END	{ print "Count = " count }
