import os
ColorMan=31
INR = 0
LifeLine = 1

questions = {
    1: "What is the Parent Company of CREAT?",
    2: "Who is the Business Head of CREAT??",
    3: "How Many Earned Leaves you get every year?",
    4: "Which Type of leaves you can Donate?",
    5: "In which office CREAT GGN is shifting?",
}

options = {
    1: ["A) Minda Kosei", "B) DensoTan Minda", "C) Uno Minda", "D) Spark Minda"],
    2: ["A) KJ San", "B) GPG San", "C) RR San", "D) MT San"],
    3: ["A) 7.5", "B) 14", "C) 21", "D) 28"],
    4: ["A) Earned Leaves", "B) Casual Leaves", "C) Parental Leaves", "D) Sick Leaves"],
    5: ["A) JMD Megapolis", "B) Magnum Towers", "C) Best Tech Buisness Park", "D) Vatika Business Park"],
}

answers = {
    1: "C",
    2: "A",
    3: "C",
    4: "D",
    5: "B",
}

os.system("echo \033[47m")
name = input("Enter your Name: ")
os.system('echo \033[43m')
print(f"Hi! {name} Welcome to KBL - Kaun Banega Lakhpati.")
print("You will be asked 5 Questions, you have to answer them correctly to win the round.")
print("There is only 1 Lifeline Named as \"MAAFI\".")
print("Winning each round will multiply your winning amount.")
print("Winning 1st round will win you 50 INR.")
print("The amount will get 10 times each round and one wrong answer will lead to Game Over with Half Winnning Amount only")

for i in range(1, 6):
    os.system('echo \033[40m')
    ColorMan+=1
    #os.system(f"color 3{c}")
    os.system(f"echo \033[{ColorMan}m")
    print(f"Question {i} : {questions[i]}")
    for option in options[i]:
        print(option)
    
    while True:
        if LifeLine==1:
            choice = input("Type A to Answer and B to Avail Lifeline: ").strip().upper()
        
        if choice == "B" and LifeLine > 0:
            LifeLine -= 1
            print(f"Lifeline Used!")
            user_answer = input("Your answer: ").strip().upper()
            if user_answer == answers[i]:
                if i == 1:
                    INR = 50
                else:
                    INR *= 10
                os.system('echo \033[42m')
                print(f"Right Answer! You have won {INR} rupees.")
            else:
                os.system('echo \033[41m')
                print("Wrong answer! You'll get another chance without lifeline.")
                user_answer = input("Your answer: ").strip().upper()
                if user_answer == answers[i]:
                    if i == 1:
                        INR = 50
                    else:
                        INR *= 10
                    os.system('echo \033[42m')
                    print(f"Right Answer! You have won {INR} rupees.")
                else:
                    os.system('echo \033[41m')
                    print("Oops! That's a Wrong Answer.")
                    print(f"GAME OVER, You can take {INR/2} rupees with you.")
                    exit()
            break
        # Code by @AbhijeetK1N6
        else:
            user_answer = input("Your answer: ").strip().upper()
            if user_answer == answers[i]:
                if i == 1:
                    INR = 50
                else:
                    INR *= 10
                os.system('echo \033[42m')
                print(f"Right Answer! You have won {INR} rupees.")
            else:
                os.system('echo \033[41m')
                print("Oops! That's a Wrong Answer.")
                print(f"GAME OVER, You can take {INR/2} rupees with you.")
                exit()
            break
else:
    os.system('echo \033[42m')
    print(f"Congratulations Lakhpati!!, You have won the KBL Game you can take {INR} rupees with you.")

