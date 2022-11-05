#! /usr/bin/awk -f

BEGIN	{ 
		FS = "," 
		getline
		print "\n-------------------"
		mathSum = 0;
		readingSum = 0;
		writingSum = 0;
		count = 0;
	}

	{ 
		
		if ($4 == "standard") 
		{
			mathSum = mathSum + $6;
			readingSum = readingSum + $7;
			writingSum = writingSum + $8;
			count = count + 1;
		}
	}
END	{
	print "Among the students that has standard lunch:\nMath Average: " mathSum/count "\nReading average: " readingSum/count "\nWriting average: " writingSum/count "\n-------------------\n"
	}
