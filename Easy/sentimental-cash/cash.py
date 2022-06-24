# TODO
from cs50 import get_float
from math import floor


def main():

    while(True):
        num = get_float("Change owed: ")
        if(num >= 0):
            break



    total = 0
    change = floor(num * 100)

    quarters = change // 25
    dimes = (change % 25) // 10
    nickels = ((change % 25) % 10) // 5
    pennies = ((change % 25) % 10) % 5


    total = quarters + dimes + nickels + pennies
    print(total)


if __name__ == "__main__":
    main()