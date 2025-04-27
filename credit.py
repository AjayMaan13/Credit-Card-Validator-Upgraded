# TODO
import math


def main():
    number = int(input("Number: "))
    count = len(str(number))

    # Check if the number passes the sum check
    if (check_sum(number, count) == False):
        print("INVALID")

    # Final check of the type of function
    else:
        check_type(number)


# This function is used to check the sum value of a card number
def check_sum(num, count):

    # These are all the variables used in the check_sum function
    total = 0
    even_sum = 0
    odd_sum = 0
    even_ten1 = 100
    even_ten2 = 10
    odd_ten1 = 10
    odd_ten2 = 1

    # This finds the sum of even places in the number
    j = 0
    while (j < 1 + (count / 2)):

        sum = 2 * int((num % even_ten1) / even_ten2)
        # This is used when the digit exceeds the value of 10 and we want to add only the unit places together
        if (sum > 9):

            even_sum = even_sum + int(sum / 10)
            even_sum = even_sum + int(sum % 10)

        # Normal case when sum is less than 10
        else:
            even_sum = even_sum + sum

        even_ten1 = even_ten1 * 100
        even_ten2 = even_ten2 * 100
        j = j + 1

    k = 0
    while (k < 1 + (count / 2)):
        odd_sum = odd_sum + int((num % odd_ten1) / odd_ten2)
        odd_ten1 = odd_ten1 * 100
        odd_ten2 = odd_ten2 * 100
        k = k + 1

    # assigning the total value of the sum
    total = even_sum + odd_sum

    # Final checking of the check_sum fucntion if it is a multiple of 10
    if ((total % 10) == 0):
        return True

    else:
        return False


def check_type(num):
    length = len(str(num))

    if length == 15:
        # Here number is the first 2 letter of the number
        number = int((num % 1000000000000000) / 10000000000000)
        if number == 34 or number == 37:
            print("AMEX")
            return True
        else:
            print("INVALID")
            return False

    # Checking if the number is VISA card number
    elif length == 13:
        if int((num % 10000000000000) / 1000000000000) == 4:
            print("VISA")
            return True
        else:
            print("INVALID")
            return False

    # Checking which category does the number confide in
    elif length == 16:
        number_2 = int((num % 10000000000000000) / 100000000000000)
        if number_2 == 51 or number_2 == 52 or number_2 == 53 or number_2 == 54 or number_2 == 55:
            print("MASTERCARD")
            return True

        number_1 = int((num % 10000000000000000) / 1000000000000000)
        if number_1 == 4:
            print("VISA")
            return True
        else:
            print("INVALID")
            return False
    else:
        print("INVALID")
        return False


if __name__ == "__main__":
    main()