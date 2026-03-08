# CALCULATING DETERMINANT OF A MATRIX WITH GAUSSIAN ELIMINATION

This is my student project. The purpose is to calculate a matrix determinant using
[Gaussian elimination](https://en.wikipedia.org/wiki/Gaussian_elimination).

The matrix class is implemented in `matrix.c`. It uses `Mtype` as the element type.
`Mtype` represents a fraction.

Two determinant calculation methods are implemented: Gaussian elimination and
column expansion (along the first column). Both methods are implemented in
`matrix/calc/DetCalculation.c`.

## Program

#### Input:
N — the matrix size. Then N lines with N numbers each — the matrix.

#### Output:
The matrix determinant calculated with both methods, represented as JSON.

### Example

#### Input:
```
3
123.123 321.321 456.123
123.42 2.1 3
1.2 2.1 .5
```

#### Output:
```json
{
  "Gauss_method_result": "97751.0823660",
  "Minor_method_result": "97751.0823660"
}
```

## Testing

You can run the run.py script. It generates tests and checks them with NumPy.
The script supports command-line flags. Run

`.venv/bin/python3 run.py --help`

to see available options.

### Problems

If you run `run.py` several times with a maximum matrix size of 5 and 1000 tests,
you may notice that it passes about 550 tests. This happens because of long long
overflow.

A possible solution would be arbitrary-precision arithmetic, which is not
implemented in this project.