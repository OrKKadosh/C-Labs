#! /usr/bin/awk -f

BEGIN	{
		FS = "," 
		getline
		print "\n-------------------"
		count = 0
	}

	{ 
		if (/fun|fan/) 
		{
			count = count + 1
		}
	}
END	{
	print "The number of Poems that contains the word fun or fan is: " count
	}
