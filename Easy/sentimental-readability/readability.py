# TODO
import cs50
from math import floor
from cs50 import get_string
def main():
    text = get_string("Text: ")
    L = 0
    S = 0
    W = 0

    for i in range(len(text)):
        if(text[i].isalpha()):
            L +=1

    for i in range(len(text)):
        if(text[i] == ' '):
            W +=1
    W+=1

    for i in range(len(text)):
        if(text[i] == '!' or text[i] == '.' or text[i] == '?'):
            S+=1

    L = float((L / W) * 100)
    S = float((S / W) * 100)

    index = float(0.0588 * L - 0.296 * S - 15.8)
    i = int(floor(round(index)))

    if(i < 1):
        print("Before Grade 1")
    elif(i >=16):
        print("Grade 16+")
    else:
        print(f"Grade {i}")


if (__name__ == "__main__"):
    main()
