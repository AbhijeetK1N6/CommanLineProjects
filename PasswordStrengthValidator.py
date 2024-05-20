def CheckPassword(strr, n):

    #CONDITIONS
    Atleast4Char = False
    AtleastOneNumeric = False
    AtleastOneCaps = False
    NoSpaces = True
    StartCharNotNum = False

    if n>4:
        Atleast4Char = True                     #Condition 1 Satisfied

        if (ord(strr[0])>=65 and ord(strr[0])<=90) or (ord(strr[0])>=97 and ord(strr[0])<=122):
            StartCharNotNum = True              #Condition 5 Satisfied 

            for i in range (n):
                if strr[i] == " " or strr[i] == "/":
                    NoSpaces = False            #Condition 4 Satisfied
                if ord(strr[i])>=65 and ord(strr[i])<=90:
                    AtleastOneCaps = True       #Condition 3 Satisfied
                if ord(strr[i])>=48 and ord(strr[i])<=57:
                    AtleastOneNumeric = True    #Condition 2 Satisfied

            if Atleast4Char==True and AtleastOneNumeric==True and AtleastOneCaps==True and NoSpaces==True and StartCharNotNum==True:
                print("Good Password, You can use it")
            else: print("Not Good, try more complex password")

        else: print("INAVLID")
    else: print("INVALID")
    
if __name__ == "__main__":
    s = list(input("Enter your Password :- "))
    CheckPassword(s,len(s))
