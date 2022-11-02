import os
import sys

if (not os.path.isfile(sys.argv[1])):
    print("File does not exist")
    raise (exit(1))

if (not sys.argv[1].endswith('.marsng')):
    print("Unidentified file type")
    raise (exit(1))
else:
    print(f"Loading {sys.argv[1]}")

mainfile = open("./Engine/main.cpp")
maincode = (mainfile.read())
mainfile.close()

customCode = open(sys.argv[1])
customEntities = customCode.readlines()
customCode.close

customEntities = ["\n"] + customEntities
for i in range(len(customEntities)):
    entity = customEntities[i]
    if (entity != "\n" and entity != ""):
        try:
            name = entity.split('(')[0]

            parameters = entity.split("(")[1].split(")")[0].split(",")

            attributes = entity.split("[")[1].split("]")[0].split(",")

            if (not name.isalnum()):
                print(
                    f"\nInvalid variable name at line {i} - Variables can only have alphanumeric names")
                raise (exit(1))

            if (not entity.count('[') == entity.count(']') == 1):
                print(f"\nInvalid syntax at line {i}")
                raise (exit(1))

            if (not entity.count('(') == entity.count(')') == 1):
                print(f"\nInvalid syntax at line {i}")
                raise (exit(1))

            if (len(parameters) not in [2, 3]):
                tmp = "few" if (len(parameters)<2) else "many";
                print(f"\nToo {tmp} parameters passed into {name} at line {i}")
                print(
                    "Note the syntax :\n<Entity_name>(x,y)[<attribute1>,<attribute2>,<attribute3>...]")
                print(
                    "OR\n<Entity_name>(x,y,<path_to_sprite>)[<attribute1>,<attribute2>,<attribute3>...]")

        except:
            print(f"\n\nCompilation Error caused by line {i}")
            raise (exit(1))


# customfile = open("./Engine/custom.cpp", "w")
# customfile.write(maincode.replace('//$%=CustomEntitiesHere', customEntities))
# customfile.close()

# os.system("cd Engine && build-custom.bat")
