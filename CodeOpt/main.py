f = open("input.txt","r")
fout = open("output.txt","w")
list_of_lines = f.readlines()
dictValues = dict()
constantFoldedList = []

print("Quadruple form after Constant Folding - ")
print("-------------------------------------")
fout.write("Quadruple form after Constant Folding - n")
fout.write("-------------------------------------\n")

for i in list_of_lines:
    i = i.strip("\n")
    op,arg1,arg2,res = i.split()
    if(op in ["+","-","*","/"]):
        if(arg1.isdigit() and arg2.isdigit()):
            result = eval(arg1+op+arg2)
            dictValues[res] = result
            output_line = f"= {result} NULL {res}"
            print(output_line)
            fout.write(output_line + "\n")
            constantFoldedList.append(["=",result,"NULL",res])
        elif(arg1.isdigit()):
            if(arg2 in dictValues):
                result = eval(arg1+op+str(dictValues[arg2]))
                dictValues[res] = result
                output_line = f"= {result} NULL {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                output_line = f"{op} {arg1} {arg2} {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append([op,arg1,arg2,res])
        elif(arg2.isdigit()):
            if(arg1 in dictValues):
                result = eval(str(dictValues[arg1])+op+arg2)
                dictValues[res] = result
                output_line = f"= {result} NULL {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                output_line = f"{op} {arg1} {arg2} {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append([op,arg1,arg2,res])
        else:
            flag1=0
            flag2=0
            arg1Res = arg1
            if(arg1 in dictValues):
                arg1Res = str(dictValues[arg1])
                flag1 = 1
            arg2Res = arg2
            if(arg2 in dictValues):
                arg2Res = str(dictValues[arg2])
                flag2 = 1
            if(flag1==1 and flag2==1):
                result = eval(arg1Res+op+arg2Res)
                dictValues[res] = result
                output_line = f"= {result} NULL {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append(["=",result,"NULL",res])
            else:
                output_line = f"{op} {arg1Res} {arg2Res} {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append([op,arg1Res,arg2Res,res])
    elif(op=="="):
        if(arg1.isdigit()):
            dictValues[res]=int(arg1)
            output_line = f"= {arg1} NULL {res}"
            print(output_line)
            fout.write(output_line + "\n")
            constantFoldedList.append(["=",arg1,"NULL",res])
        else:
            if(arg1 in dictValues):
                output_line = f"= {dictValues[arg1]} NULL {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append(["=",dictValues[arg1],"NULL",res])
            else:
                output_line = f"= {arg1} NULL {res}"
                print(output_line)
                fout.write(output_line + "\n")
                constantFoldedList.append(["=",arg1,"NULL",res])
    else:
        output_line = f"{op} {arg1} {arg2} {res}"
        print(output_line)
        fout.write(output_line + "\n")
        constantFoldedList.append([op,arg1,arg2,res])

print("\n")
print("Constant folded expression - ")
print("--------------------")
fout.write("\n")
fout.write("Constant folded expression - \n")
fout.write("--------------------\n")

for i in constantFoldedList:
    if(i[0]=="="):
        output_line = f"{i[3]} {i[0]} {i[1]}"
        print(output_line)
        fout.write(output_line + "\n")
    elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
        output_line = f"{i[3]} = {i[1]} {i[0]} {i[2]}"
        print(output_line)
        fout.write(output_line + "\n")
    elif(i[0] in ["if","goto","label","not"]):
        if(i[0]=="if"):
            output_line = f"{i[0]} {i[1]} goto {i[3]}"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="goto"):
            output_line = f"{i[0]} {i[3]}"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="label"):
            output_line = f"{i[3]} :"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="not"):
            output_line = f"{i[3]} = {i[0]} {i[1]}"
            print(output_line)
            fout.write(output_line + "\n")

print("\n")
print(" After dead code elimination - ")
print("------------------------------")
fout.write("\n")
fout.write(" After dead code elimination - \n")
fout.write("------------------------------\n")

for i in constantFoldedList:
    if(i[0]=="="):
        pass
    elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
        output_line = f"{i[3]} = {i[1]} {i[0]} {i[2]}"
        print(output_line)
        fout.write(output_line + "\n")
    elif(i[0] in ["if","goto","label","not"]):
        if(i[0]=="if"):
            output_line = f"{i[0]} {i[1]} goto {i[3]}"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="goto"):
            output_line = f"{i[0]} {i[3]}"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="label"):
            output_line = f"{i[3]} :"
            print(output_line)
            fout.write(output_line + "\n")
        if(i[0]=="not"):
            output_line = f"{i[3]} = {i[0]} {i[1]}"
            print(output_line)
            fout.write(output_line + "\n")

f.close()
fout.close()
print(f"\nResults have been written to out.txt")