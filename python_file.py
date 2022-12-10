#Tiffany McDonnell
#12-9-22
#cs-210

import re
import string

#function that prints the different items on a file and the frequency it appears on the file
def printProduce():
    textFile = open("List.txt", "r") 
    item_List = textFile.readlines()
    no_duplicate_list = []
    
    for i in item_List:
        if i not in no_duplicate_list:
            no_duplicate_list.append(i)

    for x in no_duplicate_list:
        print((no_duplicate_list[no_duplicate_list.index(x)]).strip(), end=' ')
        print(item_List.count(x), "\n")

    textFile.close()

#function that reads a file and compares it to user input and print how many time the users input shows in the file
def readFile(v):

    textFile = open("List.txt", "r") 
    item_List = textFile.readlines()
    no_duplicate_list = []
    textFile.close()
    
    for i in item_List:
        if i not in no_duplicate_list:
            no_duplicate_list.append(i)

    for x in no_duplicate_list:
        if v in x:
            return item_List.count(x)

    return 0;

#function that writes a new file using data from a different file with the different items and the amount of time they appear on the file
def writeNewFile(v):

    textFile = open("List.txt", "r") 
    item_List = textFile.readlines()
    no_duplicate_list = []
    for i in item_List:
        if i not in no_duplicate_list:
            no_duplicate_list.append(i)
            no_duplicate_list.append(str(item_List.count(i)))
            no_duplicate_list.append("\n")
  
    textFile.close()

    f = open("frequency.dat", "w")
    f.writelines(no_duplicate_list)
    f.close();

    return 0