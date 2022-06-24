# TODO
valid = 0
height = -1
while valid == 0 or height >= 9 or height <= 0: #loop until the user enters a valid int
    try:
        height = int(input('Height: '))
        valid = 1 #if this point is reached, x is a valid int
    except ValueError:
        print('Please only input digits')





spaces = height - 1
for i in range(height):
    hash_dist = height - spaces
    for j in range(spaces):
        print(" ",end="")
    for j in range(hash_dist):
        print("#",end="")
    print("  ",end="")
    for j in range(hash_dist):
        print("#",end="")
    print()

    spaces -=1

