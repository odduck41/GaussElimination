import numpy as np
import random
import subprocess
import json

subprocess.run("cmake --build cmake-build-debug --target FSR_practice -j 6",
               capture_output=False,
               shell=True)
path = ["cmake-build-debug/FSR_practice"]

for _ in range(10):
    size = random.randint(1, 5)
    matrix = [[
        round(random.uniform(0, 15), random.randint(0, 3))
            for _ in range(size)
    ] for _ in range(size)]

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
        try:
            res = dict(json.loads(result.stdout))
        except json.decoder.JSONDecodeError:
            print("\033[1;31mPARSING ERROR\n")
            print(size)
            print(mat)
            print(f"Output:\n\n{result.stdout}")
            exit(0)
        matrix = np.matrix(matrix)
        res["Np"] = np.linalg.det(matrix)

        for key in res.keys():
            res[key] = round(float(res[key]), 4)

        if float(res["Gauss_method_result"]) != float(res["Minor_method_result"]):
            print("\033[1;31mERROR: GAUSS NOT EQUAL TO MINOR\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            exit(0)
        elif float(res["Gauss_method_result"]) != float(res["Np"]):
            print("\033[1;31mERROR: MY RESULT NOT EQUAL TO NUMPY\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            exit(0)
        print(f"\033[1;32mOK: {res}\033[0m")
    else:
        print("\033[1;31mERROR")
        print(mat)
        exit(0)