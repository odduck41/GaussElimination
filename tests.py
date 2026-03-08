import numpy as np
import random
import subprocess

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
    if result.returncode == 0:
        print(result.stdout)
    print(f"Np: {np.linalg.det(matrix)}")