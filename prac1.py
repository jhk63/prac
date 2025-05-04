
def fibo(n):
	if n == 1 or n == 2:
		return 1
	return fibo(n - 1) + fibo(n - 2)


if __name__ == "__main__":
    for i in range(1, 41):
        print(i, ":", fibo(i))

