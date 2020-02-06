#This is the PROTOTYPE for the Naive Propagation Illusory Parallel Calculator. (NPPC?)
#See README for information on purpose and basic structure.

#By Henry R. Wilson

#Returns e3 as appropriate sum of e1, e2
def add(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 + v1
    d3 = (d1**2 + d2**2)**0.5
    e3 = entry()
    e3.eset(v3,d3)
    ret = [e3]
    return ret

#Returns e3 as diff of e1, e2
def sub(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 - v1
    d3 = (d1**2 + d2**2)**0.5
    e3 = entry()
    e3.eset(v3,d3)
    ret = [e3]
    return ret

#Returns e3 as product of e1, e2
def mul(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 * v1
    d3 = ( (d2/v2)**2 + (d1/v1)**2 )**0.5 * v3
    e3 = entry()
    e3.eset(v3, d3)
    ret = [e3]
    return ret

#Returns e3 as quotient of e1, e2
def div(e1, e2):
    v1, d1 = e1.eget()
    v2, d2 = e2.eget()
    v3 = v2 / v1
    d3 = ( (d2/v2)**2 + (d1/v1)**2 )**0.5 * v3
    e3 = entry()
    e3.eset(v3, d3)
    ret = [e3]
    return ret

#Prints both then returns both
def two(e1, e2):
    print("E2:",e2,"\nE1:",e1)
    return [e2,e1]

#Stub function.
#This is not implementable in accordance
#with the design principle of pop 2, push N.
def pall(e1, e2):
    print("Not implemented!")
    print("Not possible to implement consistently with design principles.")
    return [e2, e1]

#Simply drop e1
def die(e1, e2):
    return [e2]

#Push both back, e1 BEFORE e2.
def swp(e1, e2):
    return [e1, e2]

#These NEED to stay in the same order as each other.
#              0     1     2     3     4     5     6
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
    def eset(self,v,d):
        self.value = v
        self.delta = d
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
        #Give prompt.
        try:
            command = input(">>")
        #Let the user know they should exit
        #by typing "exit" or "quit"
        except:
            print("Rude exit!")
            break;

        #Operator execution
        if command in opstrings:
            print("Executing", command+"...")
            #Make sure that the stack can have 2 entries popped at all.
            if len(stack) < 2:
                print("Insufficient stack size for operation!")
                continue
            else:
                #Determine actual operator.
                i = opstrings.index(command)
                op = operators[i]
                #Pop two elements.
                e1 = stack.pop()
                e2 = stack.pop()
                #Execute op.
                etuple = op(e1,e2)
                #Push everything in the returned list back onto stack
                for e in etuple:
                    stack.append(e)

        #Quit condition
        elif command == "quit" or command == "exit":
            exit = True
            continue
        #Help message
        elif command == "help":
            print("\tNPIPCP Operates on a stack system.")
            print("\tEnter operands in value, uncertainty pairs.")
            print("\tFor example: 2.33,4.2e-2")
            print("\tCommands:", opstrings)
            print("\tEach command pops two operands.")
            print("\tEach command pushes N operands back.")
            print("\tSpecial commands:")
            print("\ttwo: prints both operands, pushes both back.")
            print("\tdie: kills one operand, pushes the other back.")
            print("\tswp: pushes both back in opposite order.")

        #Value, delta entry
        #This is the only way to populate the stack
        else:
            #Note: this works as long as two proper floats
            #are separated by a comma. Whitespace does not affect things.
            try:
                #Parse value and delta out
                value, delta = command.split(',')
                value = float(value)
                delta = float(delta)
                #Buld element
                e = entry()
                e.eset(value,delta)
                #Push
                stack.append(e)
            except:
                print("Malformed command!")
    print("Goodbye!")
