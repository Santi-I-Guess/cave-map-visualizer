from random import randint

for i in range(20):
    a: int = randint(-20, 20)
    b: int = randint(-20, 20)
    c: int = randint(-20, 20)
    print(f"({a}, {b}, {c})", end="")
    if i == 19:
        print(";")
    else:
        print(",")
