import numpy as np
import random
import subprocess
import json

subprocess.run("cmake --build cmake-build-debug --target FSR_practice -j 6", shell=True)
path = ["cmake-build-debug/FSR_practice"]

for i in range(10):
    size = random.randint(1, 5)
    matrix = [[random.randint(0, 100) for _ in range(size)] for _ in range(size)]
    mat = str()
    for line in matrix:
        mat += " ".join(list(map(str, line)))
        mat += "\n"

    result = subprocess.run(
        path,
        input=f"{size}\n{mat}",
        capture_output=True,
        text=True
    )

    res = str()
    if result.returncode == 0:
        print("\033[1;m--------\033[0m")
        res = json.loads(result.stdout)

        matrix = np.matrix(matrix)
        res["Np"] = str(np.round(np.linalg.det(matrix)))
        if int(float(res["Gauss_method_result"])) != int(float(res["Minor_method_result"])):
            print("\033[1;31mERROR: GAUSS NOT EQUAL TO MINOR\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            exit(0)
        elif int(float(res["Gauss_method_result"])) != int(float(res["Np"])):
            print("\033[1;31mERROR: MY RESULT NOT EQUAL TO NUMPY\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            exit(0)
        print(f"\033[1;32mOK: {res}\033[0m")
    else:
        print("ERROR")
        print(mat)
        exit(0)