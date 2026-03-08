import numpy as np
import random
import subprocess
import json
import pathlib

if not pathlib.Path("cmake-build-debug").exists():
    command = subprocess.run("cmake -DCMAKE_BUILD_TYPE=Debug \
                      -DCMAKE_MAKE_PROGRAM=ninja \
                      -G Ninja -S . \
                      -B cmake-build-debug", shell=True)
    if command.returncode != 0:
        print("\033[1;31mERROR")
        subprocess.run("rm -rf cmake-build-debug", shell=True)
        exit(0)


subprocess.run("cmake --build cmake-build-debug --target FSR_practice -j 6",
               capture_output=False,
               shell=True)

path = ["cmake-build-debug/FSR_practice"]

amount = int(20)
passed = 0

for _ in range(amount):
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
            continue
            exit(0)
        matrix = np.matrix(matrix)
        res["Np"] = np.linalg.det(matrix)

        for key in res.keys():
            res[key] = round(float(res[key]), 5)

        if res["Gauss_method_result"] != res["Minor_method_result"]:
            print("\033[1;31mERROR: GAUSS RESULT NOT EQUAL TO MINOR\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            continue
            exit(0)
        elif res["Gauss_method_result"] != res["Np"]:
            print("\033[1;31mERROR: GAUSS RESULT NOT EQUAL TO NUMPY\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            continue
            exit(0)
        output = f"\033[1;32mOK: {res}"
        print(f"{output:<120}PASSED\033[0m")
        passed += 1
    else:
        print("\033[1;31mERROR")
        print(mat)
        continue
        exit(0)

print(f"\033[1;32m\n\nPassed {passed} tests of {amount}.\033[0m")