import sys
import os

verificationTimesAll = []
synthesisTimesAll = []

def parseFile(f_in, f_out):
      	data = f_in.read().split("\n")

        verificationTimes = [float(x.split("Time for verification: ")[1].split("s")[0]) for x in data if "Time for verification: " in x]
        synthesisTimes = [float(x.split("Time for synthesis: ")[1].split("s")[0]) for x in data if "Time for synthesis: " in x]
	verificationTimesAll.append(verificationTimes)
	synthesisTimesAll.append(synthesisTimes)
	totalTime = int([x.split("Total time: ")[1].strip() for x in data if "Total time: " in x][0])

        # Print the column headers
        f_out.write("iteration,verification time (s),synthesis time (s),total time (s)\n")

        # Format the very first line of data. There are 1 less synthesis times as verification times, so we leave
        # this first cell blank. Write the total time on this line
        f_out.write( "0,%f,,%d\n" %(verificationTimes[0], totalTime))

        # Now output the rest of the verification and synthesis times
        for i in range(len(synthesisTimes)):
                f_out.write("%d,%f,%f,\n" %(i+1, verificationTimes[i+1], synthesisTimes[i]))
	f_out.write("\n\n")

def addAllResults(f_out):
	# Write all the synthesis and verification times separately (makes plotting some things easier in Excel)
	f_out.write("\n\nVERIFICATION TIMES\n\n")
	for i in range(max([len(l) for l in verificationTimesAll])):
		for l in verificationTimesAll:
			if i < len(l):
				f_out.write("%f," % l[i])
			else:
				f_out.write(",")
		f_out.write("\n")
        f_out.write("\n\nSYNTHESIS TIMES\n\n")
        for i in range(max([len(l) for l in synthesisTimesAll])):
                for l in synthesisTimesAll:
                        if i < len(l):
                                f_out.write("%f," % l[i])
                        else:
                                f_out.write(",")
		f_out.write("\n")

if __name__ == "__main__":
	if len(sys.argv) != 3:
		print "usage: python parseResultFiles.py <path_to_result_files> <output_filename>"
		sys.exit(-1)
	directory = sys.argv[1]
    	newFileName = sys.argv[2]
    	resultFiles = []
	
	for dirName, subdirList, fileList in os.walk(directory):
        	for fileName in fileList:
            		if ".out" in fileName:
                		fullFileName = "%s/%s" %(dirName, fileName)
                		resultFiles.append(fullFileName)

	f_out = open(os.path.join(dirName, newFileName), "w")
	for resultFile in resultFiles:
        	f_in = open(resultFile, "r")
		parseFile(f_in, f_out)
		f_in.close()
	addAllResults(f_out)
	f_out.close()
