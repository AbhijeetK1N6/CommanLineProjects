"""
# Assign any Random Number to a Variable
# WAP to guess the assigned fixed number
# If rightly guessed Print Congrats, 
# Else Guide the player either he/she is far or
close from the pre defined number
# Number of Guesses must be limited to 5
# Print Number of guesses left, after every guess
# Print Game Over when all guesses are used
# After Game Finih Print Number of Guesses
"""

#               @AbhijeetK1N6

num=69
nog=5
print("You Only Have 5 Chances, Use it Wisely ;)")
while(nog>=0):
    if nog==0:
        print("----GAME OVER----")
        print("You Took",5-nog,"Guesses")
        break
    guess=int(input("Guess the Number Between 1 to 100"))

#  INCREMENT Starts
    if guess <= num-30 and guess>=1:
        print("Too Far..Please Increase\n")
        nog=nog-1
        print("Number of Guesses Left:-", nog)
        continue
    elif guess<=num-20 and guess>-30:
        print("Little Far..Please Increase\n")
        nog-=1
        print("Number of Guesss Left:",nog)
        continue
    elif guess<=num-10 and guess>num-20:
        print("Bit Close.. Please Increase\n")
        nog-=1
        print("Number of Guesss Left:",nog)
        continue
    elif guess<num and guess>num-10:
        print("So Close..Please Increase")
        nog-=1
        print("Number of Guesss Left:", nog)
        continue
        
#  DECREMENT STARTS if Guess>Num
    elif guess>=num+30:
        print("Too Far..Please Decrease\n")
        nog-=1
        print("Number of Guesss Left:", nog)
        continue
    elif guess>=num+20 and guess < num+30:
        print("Bit Far..Please Decrease\n")
        nog -= 1
        print("Number of Guesss Left:", nog)
        continue
    elif guess>=num+10 and guess<num+20:
        print("Bit Close..Please Decrease\n")
        nog -= 1
        print("Number of Guesss Left:", nog)
        continue
    elif guess>num and guess<num+10:
        print("So Close..Please Decrease\n")
        nog -= 1
        print("Number of Guesss Left:", nog)
        continue
        
#  When Rightly Guess
    elif guess==num:
        print("Congrats!! You Won..\n")
        print("You Took Only",6-nog,"Guesses\n")
        break
