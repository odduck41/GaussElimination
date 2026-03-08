import argparse

import numpy as np
import random
import subprocess
import json
import pathlib


def compile_program():
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

def get_arguments() -> dict:
    arguments = argparse.ArgumentParser()
    arguments.add_argument("-t", "--tests",
                       dest="tests",
                       type=int,
                       help="Amount of tests(default=10)")

    arguments.add_argument("-s", "--size",
                           dest="size",
                           type=int,
                           help="Fixes sizes of matrices(default=-1)")

    arguments.add_argument("-m", "--max",
                           dest="max",
                           type=int,
                           help="Set max size of generating matrices(default=5)")

    args = dict(vars(arguments.parse_args()))

    if args["max"] is None:
        args["max"] = 5
    if args["size"] is None:
        args["size"] = -1
    if args["tests"] is None:
        args["tests"] = 10

    return args

def run_test(size=-1, max_sz=-1) -> int:
    path = ["cmake-build-debug/FSR_practice"]

    if size == -1:
        size = random.randint(1, max_sz)

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

    if result.returncode == 0:
        print("\033[1;m--------\033[0m")
        try:
            res = dict(json.loads(result.stdout))
        except json.decoder.JSONDecodeError:
            print("\033[1;31mPARSING ERROR\n")
            print(size)
            print(mat)
            print(f"Output:\n\n{result.stdout}")
            return 1
        matrix = np.matrix(matrix)
        res["Np"] = np.linalg.det(matrix)

        for key in res.keys():
            res[key] = str(round(float(res[key]), 5))

        if res["Gauss_method_result"] != res["Minor_method_result"]:
            print("\033[1;31mERROR: GAUSS RESULT NOT EQUAL TO MINOR\n")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            return 1
        elif res["Gauss_method_result"] != res["Np"]:
            print(f"{"\033[1;31mERROR: GAUSS RESULT NOT EQUAL TO NUMPY":<120}", end="")
            if res["Gauss_method_result"] == res["Minor_method_result"]:
                print("\033[1;33mWARNING: PROBABLY ROUNDING ERROR\033[0m")
            print("\033[1;31m", end="")
            print(size)
            print(mat)
            print(f"Result:\n{res}")
            if res["Gauss_method_result"] == res["Minor_method_result"]:
                return 2
            return 1
        output = f"\033[1;32mOK: {res}"
        print(f"{output:<120}PASSED\033[0m")
    else:
        print("\033[1;31mERROR")
        print(mat)
        return 1

    return 0


def main() -> int:
    compile_program()
    args = get_arguments()
    amount = args["tests"]
    passed = 0
    warnings = 0
    errors = 0
    for _ in range(amount):
        result = run_test(args["size"], args["max"])
        passed += result == 0
        errors += result == 1
        warnings += result == 2

    print(f"\033[1;32m\n\nPassed {passed} tests of {amount}.\033[0m")
    print(f"\033[1;31m{errors} errors.\033[0m")
    print(f"\033[1;33m{warnings} warnings.\033[0m\n")
    return 0



if __name__ == "__main__":
    exit(main())

