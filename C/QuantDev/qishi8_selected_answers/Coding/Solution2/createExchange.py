#!/usr/bin/env python

import sys
import random #for sampling the data
import re #for regex finding and substitution

#create a new input data set with Exchange A and B(a positive/negative time lag is added on B) from raw data; I also add time and price noise randomly on the created trading record for exchange B. 'input_file' is the given raw dataset, 'time_lag' is an integer value assigned to Exchange B to create a time lag.
def create_new_data(input_file,time_lag):
	
	exchangeAB = open('input_20170418.txt','w') # create a new file that contains trading records in Exchange A and B
	
	with open(input_file) as exchangeA: #open the provided raw data file
		title = exchangeA.readline().rstrip()+',Exchange\n' #write the title to file 'input_20170418.txt'
		exchangeAB.write(title)

		#read a line from the provided raw data and add "A" for the Exchange information; Furthermore, construct a trading record with a time lag for exchange B and write it in a new line
		next(exchangeA)
		for line in exchangeA:
			if random.random() < 0.1: # Sample the raw data --> to get a small-sized input_file
				exchangeAB.write(line.rstrip()+',A\n')
				if random.random() < 0.5: #For a given trading record in Exchange A, create a new trading record for Exchange B with probability 0.5
					microsec = int(re.findall('[0-9]+',line)[6]) + time_lag # add a time lag
					if microsec > 999999 or microsec < 0: #avoid the records that are close to integer seconds for simplicity 
						continue
					
					newline = re.sub('([0-9]){6}',str(microsec).zfill(6),line) #replace the microsecond with a new one with a time lag
					
					if random.random()<0.2: # add time noise randomly
						sec = int(re.findall('[0-9]+',line)[5]) + random.randint(5,10) # add a time noise (5-10) onto second
						sec = 59 if (sec>=60) else sec
						re.sub(':([0-9]){2}\.',':'+str(sec).zfill(2)+'.',newline)

					if random.random()<0.2: # add price noise randomly
						price = float(re.findall('[0-9]+\.[0-9]+',line)[1])+random.randint(10,50) # add a price noise (10-50) onto price
						re.sub('([A-Z]){4}\,[0-9]+','GOOG'+str(price),newline)

					exchangeAB.write(newline.rstrip()+',B\n') # write new contents to created file "input_20170418.txt"


	exchangeAB.close()
	


# main function for implementing the function - "create_new_data" to create new data sets consisting of Exchange A and B
if __name__ == '__main__':
	
	try:
		input_file = sys.argv[1] #arguments for the "create_new_data" function
		time_lag = int(sys.argv[2])
	except:
		print("Oops! Please type the correct file name:")
		input_file = raw_input("Raw data set name: \n")
		time_lag = raw_input("Time lag: \n")

	create_new_data(input_file, time_lag)  # call the "create_new_data" function

