
def sum_coroutine():
    total = 0
    while True:
        x = (yield total)
        total += x

def sum_func():
    co = sum_coroutine()
    next(co)
    result1 = co.send(10)
    print(f"result1 --> {result1}")
    result2 = co.send(20)
    print(f"result2 --> {result2}")


if __name__ == "__main__":
    sum_func()
