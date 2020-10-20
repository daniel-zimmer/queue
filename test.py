from ctypes import *
from random import randint

class Queue(Structure):
	_fields_ = [('len', c_int), ('capacity', c_int), ('head', c_int), ('tail', c_int), ('elems', c_void_p)]

	def __repr__(self):
		s = "len:  %d\ncap:  %d\nhead: %d\ntail: %d\n" % (self.len, self.capacity, self.head, self.tail)

		return s

libc = CDLL("./queue.so")

libc.QUEUE_create.argtypes = None
libc.QUEUE_create.restype = POINTER(Queue);

libc.QUEUE_push.argtypes = [POINTER(Queue), c_void_p]
libc.QUEUE_push.restype = POINTER(Queue);

libc.QUEUE_pop.argtypes = [POINTER(Queue)]
libc.QUEUE_pop.restype = c_void_p;

libc.QUEUE_delete.argtypes = [POINTER(Queue), c_void_p]
libc.QUEUE_delete.restype = None;

libc.QUEUE_len.argtypes = [POINTER(Queue)]
libc.QUEUE_len.restype = c_int;

libc.QUEUE_cap.argtypes = [POINTER(Queue)]
libc.QUEUE_cap.restype = c_int;

pyq = []

print("Creating queue")
q = libc.QUEUE_create()
print(q.contents)

steps = 10000

print("Pushing and Popping")
correct = 0
total = 0
for _ in range(steps):
	opCount = randint(1, 100)
	for _ in range(opCount):
		val = randint(1, (1<<64) - 1)
		q = libc.QUEUE_push(q, val)
		pyq.insert(0, val)

	opCount = randint(1, len(pyq)//30 + 1)
	for _ in range(opCount):
		expected = pyq.pop()
		actual = libc.QUEUE_pop(q)
		total += 1
		if expected != actual:
			print("failed! actual: %d; expected %d" % (actual, expected))
		else:
			correct +=1
	print("\r(%d/%d)" % (correct, total), end=" ")
print()

print(q.contents)

print("Popping until empty")
correct = 0
total = 0
while (libc.QUEUE_len(q) != 0):
	expected = pyq.pop()
	actual = libc.QUEUE_pop(q)
	total += 1
	if expected != actual:
		print("failed! actual: %d; expected %d" % (actual, expected))
	else:
		correct +=1
	print("\r(%d/%d)" % (correct, total), end=" ")
print()

print(q.contents)

print("Deleting queue")
libc.QUEUE_delete(q, None)
print("ok")
