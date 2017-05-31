#!/usr/bin/python

import random

""" convert time raw format to (second, microsecond) """
""" starting from 09:30:00.000000 """
def convert_from_raw_time(time):
    hour = (int)(time[0:2])
    minute = (int)(time[3:5])
    second = (long)(time[6:8])
    second += (hour - 9) * 3600 - 1800
    second += minute * 60
    microsecond = (long)(time[-6:])
    return second, microsecond

""" convert (second, microsecond) to time raw format """
def convert_to_raw_time(sec, ms):
    hour = sec / 3600 + 9
    sec = sec % 3600
    minute = sec / 60 + 30
    if (minute >= 60):
        hour += 1
        minute = minute % 60
    sec = sec % 60
    time = ""
    time += str(hour).zfill(2) + ':'
    time += str(minute).zfill(2) + ':'
    time += str(sec).zfill(2) + '.'
    time += str(ms).zfill(6)    
    return time

""" customized greater function for sorted """
def greater(a, b):
    sec_a, ms_a = convert_from_raw_time(a[11:26])
    sec_b, ms_b = convert_from_raw_time(b[11:26])
    if (sec_a > sec_b):
        return 1
    elif (ms_a > ms_b):
        return 1
    return -1

""" add time lag to partial data from A to generate B """
def add_B_with_lag(lag, line):
    ratio = 0.7
    p = random.uniform(0, 1)
    newline = ""
    if p <= ratio:
        newline = line
        time = newline[11:26]
        sec, ms = convert_from_raw_time(time)
        ms += lag;
        if ms > 1000000:
            ms = ms % 1000000
            sec += 1
        if sec >= 0 and ms >= 0:
            time = convert_to_raw_time(sec, ms)
            letters = list(newline)
            letters[-1] = 'B'
            letters[11:26] = time
            newline = "".join(letters)
    return newline

""" generate the input file for C++ program """
def generate_data_from_raw(date, raw_filename):
    data =[]
    lag = random.randint(0, 99)
    print "The time lag is", lag;
    f = open(raw_filename)
    lines = f.readlines();
    for line in lines[1:]:
        if line[-1] == '\n':
            line = line[:-1]
        line.strip()
        line += ",A"
        data.append(line)
        newline = add_B_with_lag(lag, line)
        if (newline != ""):
            data.append(newline)
    data = sorted(data, cmp=greater)
    filename = date + '_' + 'data.txt'
    with open(filename, "w") as outfile:
        outfile.write('Time,Ticker,Price,Size,Exchange\n')
        outfile.write("\n".join(data))

if __name__ == "__main__":
    import sys
    date = sys.argv[1]
    raw_filename = sys.argv[2];
    generate_data_from_raw(date, raw_filename)
