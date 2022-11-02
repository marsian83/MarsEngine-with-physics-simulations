import os
import sys
from typing import ParamSpecArgs

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
customCode = ""

customEntities = ["\n"] + customEntities
for i in range(len(customEntities)):
    entity = customEntities[i]
    if (entity != "\n" and entity != ""):
        customCode+="\n"
        if(True):
        # try:
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
                tmp = "few" if (len(parameters) < 2) else "many"
                print(f"\nToo {tmp} parameters passed into {name} at line {i}")
                print(
                    "Note the syntax :\n<Entity_name>(x,y)[<attribute1>,<attribute2>,<attribute3>...]")
                print(
                    "OR\n<Entity_name>(x,y,<path_to_sprite>)[<attribute1>,<attribute2>,<attribute3>...]")
                raise (exit(1))

            if (len(parameters) == 3):
                if (parameters[2][0] == '"' and parameters[2].endswith('"')):
                    parameters[2] = parameters[2][1, -1]
                parameters[2] = os.path.abspath(parameters[2])
                while('\\' in parameters[2]):
                    parameters[2] = parameters[2].replace('\\','/')
                if (not os.path.isfile(parameters[2])):
                    print(
                        f"file {parameters[2]} does not exist - assigned as sprite to {name} at line {i}")
                    raise (exit(1))

            if (len(parameters) == 2):
                customCode += f"CustomEntity {name}({parameters[0]},{parameters[1]});"
            if (len(parameters) == 3):
                customCode += f"CustomEntity {name}({parameters[0]},{parameters[1]}," +'"'+parameters[2]+'"'+");"

            for attribute in attributes:
                if (attribute == "gravity"):
                    customCode += f"{name}.toggleGravity();"
                elif (attribute == "wallcollisions"):
                    customCode += f"{name}.toggleWallcollisions();"
                elif (attribute == "inelasticity"):
                    customCode += f"{name}.toggleInelasticity();"
                elif (attribute == "gravitation"):
                    customCode += f"{name}.toggleGravitation();"
                elif (attribute.startswith("velocity")):
                    vel = attribute.split('velocity')[1]
                    if(not (vel.startswith('<') and vel.endswith('>'))):
                        print(f"Invalid declaration for velocity attribute for {name} at line {i}")
                        raise(exit(1))
                    vel = vel[1:-1]
                    vel = vel.split(':')
                    if (len(vel)!=2):
                        print(f"Velocity takes only 2 arguments velocity(Vx,Vy) - line {i}")
                        raise(exit(1))
                    customCode += f"{name}.setVelocity({vel[0]},{vel[1]});"
                elif (attribute.startswith("force")):
                    vel = attribute.split('force')[1]
                    if(not (vel.startswith('<') and vel.endswith('>'))):
                        print(f"Invalid declaration for force attribute for {name} at line {i}")
                        raise(exit(1))
                    vel = vel[1:-1]
                    vel = vel.split(':')
                    if (len(vel)!=2):
                        print(f"Force takes only 2 arguments force(Fx,Fy) - line {i}")
                        raise(exit(1))
                    customCode += f"{name}.setForce({vel[0]},{vel[1]});"
                elif (attribute.startswith("mass")):
                    vel = attribute.split('mass')[1]
                    if(not (vel.startswith('<') and vel.endswith('>'))):
                        print(f"Invalid declaration for mass attribute for {name} at line {i}")
                        raise(exit(1))
                    vel = vel[1:-1]
                    if (len(vel)!=1):
                        print(f"Mass takes only 1 argument mass(M) - line {i}")
                        raise(exit(1))
                    customCode += f"{name}.setMass({vel[0]});"
                elif (attribute.startswith("scale")):
                    vel = attribute.split('scale')[1]
                    if(not (vel.startswith('<') and vel.endswith('>'))):
                        print(f"Invalid declaration for scale attribute for {name} at line {i}")
                        raise(exit(1))
                    vel = vel[1:-1]
                    if (len(vel)!=1):
                        print(f"Scale takes only 1 argument scale(<scale>) - line {i}")
                        raise(exit(1))
                    customCode += f"{name}.setScale({vel[0]});"

        # except:
        #     print(f"\n\nCompilation Error caused by line {i}")
        #     raise (exit(1))


customfile = open("./Engine/custom.cpp", "w")
customfile.write(maincode.replace('//$%=CustomEntitiesHere', customCode))
customfile.close()
print(customCode)
os.system("cd Engine && build-custom.bat")
