DATE = {'A': 'MON', 'B': 'TUE', 'C': 'WED', 'D': 'THU', 'E': 'FRI', 'F': 'SAT', 'G': 'SUN'}

# read first two lines
twoLine = []
for ix in range(2):
	twoLine.append(input())

one, two = twoLine
# find first common captical letter
for ix in range(min(len(one), len(two))):
	fir = one[ix]
	snd = two[ix]
	if fir.isupper() and fir == snd:
		date = DATE[fir]
		break

# find second common character
flag = 0
for ix in range(min(len(one), len(two))):
	fir = one[ix]
	snd = two[ix]
	if fir.isupper() and fir == snd:
		if flag == 0:
			flag = 1
		else:
			hour = int(fir, base = 24) 
			break

 # read last two lines
twoLine = []
for ix in range(2):
	twoLine.append(input())

one, two = twoLine
for ix in range(min(len(one), len(two))):
	fir = one[ix]
	snd = two[ix]
	if fir.isalpha() and fir == snd:
		break
minute = ix

print("%s %02d:%02d" %(date, hour, minute))