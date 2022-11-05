#! /usr/bin/awk -f

BEGIN	{
		OFS = " --- "
		FS = "," 
		getline
		print "\n-------------------"
		print "Haikus with the word happy in it's first part"
	}

	{ 
		if ($2~/happy/) 
		{
			print $2 , $3 , $4
		}
	}
