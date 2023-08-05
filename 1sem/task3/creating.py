import subprocess

print("Enter the diapason")
letter_1 = input()
letter_2 = input()
print("Enter exceptions. If no more exceptions can be provided, print Stop")
exception_list = []
while True:
	exception = input()
	if (exception == "Stop"):
		break
	exception_list.append(exception)
for i in range(ord(letter_2) - ord(letter_1) + 1):
	name = chr(ord(letter_1) + i) + '.cpp'
	if chr(ord(letter_1) + i) not in exception_list:
		subprocess.run(['touch', name])
