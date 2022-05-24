from subprocess import Popen, PIPE, STDOUT
import random

def test_sort(path, n):
	in_arr = [random.randint(0, n*10) for _ in range(0, n)]
	in_data = bytearray('\n'.join(map(str, in_arr)), 'ascii')

	p = Popen([path], stdout=PIPE, stdin=PIPE, stderr=PIPE)
	out, err = p.communicate(input=in_data)

	out_data = out.decode('ascii').strip().split('\n')
	out_arr = list(map(int, out_data))
	
	for i in range(0, len(out_arr) - 1):
		if out_arr[i] > out_arr[i+1]:
			name = str(random.randint(10000000, 99999999))
			path = '.' + name + '.test'
			file = open(path, 'wb')
			file.write(in_data)
			file.close()
			print('  TEST FAILED:', path)
			print('\ttesting data set dumped into', path)
			return

	print('  TEST PASSED:', path)

test_sort('./BubbleSort.x', 10000)
test_sort('./SelectionSort.x', 10000)
test_sort('./InsertionSort.x', 10000)