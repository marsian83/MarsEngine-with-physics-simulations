mainfile = open("./Engine/main.cpp")
arg = (mainfile.read())
mainfile.close()

arg = "rasi29a[gravity,inelasticity]"

try:
    varname = arg.split('[')[0]
    foo = arg.split("[")[1].split("]")[0].split(",")
    if (not varname.isalnum()):
        print("Invalid variable name at line {i} - Variables can only have alphanumeric names")
        raise (exit(1))
    if ( not arg.count('[') == arg.count(']') == 1):
        print("Invalid syntax at line {i}")
        raise(exit(1))
    print(varname,  foo)
except:
    print("Compilation Error")
    raise (exit(1))
