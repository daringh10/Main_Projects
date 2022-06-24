import csv
import sys


def main():

    # TODO: Check for command-line usage
    argc = len(sys.argv)
    if (argc != 3):
        print("Usage: python dna.py data.csv sequence.txt")
        exit()


    # {John:{AGTC:17,GGG:5}}
    # TODO: Read database file into a variable
    d = {}
    str_file = sys.argv[1]
    with open(str_file,"r") as file:
      reader = csv.reader(file)
      DNA_dict = {}
      labels = []
      for row in reader:
          labels = row[1:]
          break
      for row in reader:
          temp_d = {}
          temp_row = row[1:]
          for i in range(len(labels)):
              temp_d[labels[i]] = int(temp_row[i])
          d[row[0]] = temp_d

    # TODO: Read DNA sequence file into a variable
    text_file = open(sys.argv[2], "r")
    data = text_file.read()
    sequence = data.rstrip("\n")
    # TODO: Find longest match of each STR in DNA sequence
    for item in labels:
        DNA_dict[item] = longest_match(sequence,item)

    # TODO: Check database for matching profiles
    match = False
    for key,dict in d.items():
        for str,val in dict.items():
            if(val != DNA_dict[str]):

                match = False
                break
            else:
                match = True
        if(match == True):
            print(key)
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
