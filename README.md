# ComS327
Jadyn Gust Jagust@iastate.edu
Matt Karmelich matkarm@iastate.edu
Nick Soultz Ndsoultz@iastate.edu

Usage: 
run the file "sandfall" followed by "--fps" and the number you would like fps to be set too, default is 60.
If you would like to add sand, add three sets of numbers, x and y followed by the amout of sand youd like places at that location.
If you would like to place a sinkhole, give the x and y coordinates followed by a -1
Example usage: 
./sandfall --fps 30 
This will run the program on a 23 x 23 plane of 0s, with an fps of 30
./sandfall 5 10 6
This will run the program with a pile of 6 sand at the location 5 10, with the default fps of 60
./sandfall --fps 120 12 11 -1 8 8 8 14 14 2
This will run the program at 120 fps, with a sinkhole at 12 12, a sandpile of 8 at 8 8, and a sandpile of 2 at 14 14
