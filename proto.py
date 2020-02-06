#This is the PROTOTYPE for the Naive Propagation Illusory Parallel Calculator. (NPPC?)
#See README for information on purpose and basic structure.

#By Henry R. Wilson
#WTFPL License

def add(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 + v1
    d3 = (d1**2 + d2**2)**0.5
    e3 = entry()
    e3.eset(v3,d3)
    ret = [e3]
    return ret

def sub(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 - v1
    d3 = (d1**2 + d2**2)**0.5
    e3 = entry()
    e3.eset(v3,d3)
    ret = [e3]
    return ret

def mul(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 * v1
    d3 = ( (d2/v2)**2 + (d1/v1)**2 )**0.5 * v3
    e3 = entry()
    e3.eset(v3, d3)
    ret = [e3]
    return ret

def div(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 / v1
    d3 = ( (d2/v2)**2 + (d1/v1)**2 )**0.5 * v3
    e3 = entry()
    e3.eset(v3, d3)
    ret = [e3]
    return ret

def two(e1, e2):
    print("E2:",e2,"\nE1:",e1)
    return [e2,e1]

def pall(e1, e2):
    print("Not implemented!")
    print("Not possible to implement consistently with design principles.")
    return [e2, e1]

def die(e1, e2):
    return [e2]

def swp(e1, e2):
    return [e1, e2]

#              0     1     2     3     4     5     6     7
opstrings = ('add','sub','mul','div','two','die','swp')
operators = ( add,  sub,  mul,  div,  two,  die,  swp )
#two and all print so many entries
#die removes bottom entry
#swp replaces bottom two entries with each other

class entry:
    #Has value and uncertainty
    def __init__(self):
        self.value = 0.0
        self.delta = 0.0
    #Can be set
    def eset(self,a,b):
        self.value = a
        self.delta = b
    #Can be got
    def eget(self):
        return (self.value, self.delta)
    #ToString func
    def __str__(self):
        return str(self.value)+", "+str(self.delta)


if __name__ == "__main__":
    print("Welcome to NPIPCP!")

    stack = [] #Use append and pop to modify
    exit = False
    while(not exit):
        try:
            command = input(">>")
        except:
            print("Rude exit!")
            break;

        #Operator execution
        if command in opstrings:
            print("Executing", command+"...")
            if len(stack) < 2:
                print("Insufficient stack size for operation!")
                continue
            else:
                i = opstrings.index(command)
                op = operators[i]
                e1 = stack.pop()
                e2 = stack.pop()
                #Execute
                etuple = op(e1,e2)
                #This seems to get the right order every time. Does it?
                for e in etuple:
                    stack.append(e)

        #Quit condition
        elif command == "quit" or command == "exit":
            exit = True
            continue
        elif command == "help":
            print("\tNPIPCP Operates on a stack system.")
            print("\tEnter operands in value, uncertainty pairs.")
            print("\tCommands:", opstrings)
            print("\tEach command pops two operands.")
            print("\tEach command pushes N operands back.")
            print("\tSpecial commands:")
            print("\ttwo: prints both operands, pushes both back.")
            print("\tdie: kills one operand, pushes the other back.")
            print("\tswp: pushes both back in opposite order.")

        #Value, delta entry
        else:
            try:
                value, delta = command.split(',')
                value = float(value)
                delta = float(delta)
                e = entry()
                e.eset(value,delta)
                stack.append(e)
                #print("Added to stack!")
            except:
                print("Malformed command!")
    print("Goodbye!")
