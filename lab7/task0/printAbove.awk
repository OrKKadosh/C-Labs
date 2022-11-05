#! /usr/bin/awk -f

BEGIN	{ FS = " "} 
	{ if ($4 > 87) 
		{ print $0 }
	}
