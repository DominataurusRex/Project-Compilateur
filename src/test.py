"""
Programme pour lancer les différents banc de tests
Effectue un `make` automatiquement
"""
from pathlib import Path
from subprocess import run
from sys import argv


def make_test(folder: str) -> tuple[int, int, int, int, int]:
    """
    Peremt d'effectuer les tests sur le fichier `folder` dans `/test`
    """
    result_code = [0, 0, 0, 0, 0]
    for file in [f.name for f in Path(f"test/{folder}").iterdir() if not f.is_dir()]:
        result = run(
            f"./bin/tpcc ./test/{folder}/{file}",shell=True, capture_output=True, check=False
        )
        print(result.stderr.decode("utf-8"), end="")
        stdout_file = result.stdout.decode("utf-8")
        print(stdout_file, end="")
        if "warnin" in stdout_file:
            result_code[4] += 1
        if result.returncode > 3:
            result_code[3] += 1
        else:
            result_code[result.returncode] += 1
    return result_code


def test_all() -> dict[str, tuple[int, int, int, int, int]]:
    """
    Permet de tester tout les fichiers contenu dans `/test`
    """
    result_test = {}
    for file in [f.name for f in Path("test").iterdir() if f.is_dir()]:
        result_test[file] = make_test(file)
    return result_test


def main() -> int:
    """
    Fonction principal
    """
    result = run("make", shell=True, capture_output=True, check=False)
    if result.returncode != 0:
        print("\033[31;1mProbleme de compilation !\033[0m")
        print(result.stderr.decode("utf-8"), end="")
        return 0
    print("\033[32;1mMise a jour !\033[0m")
    result_test = {}
    if len(argv) == 1:
        result_test = test_all()
    else:
        for file in argv[1:]:
            path = Path(f"test/{file}")
            if path.exists() and path.is_dir():
                result_test[file] = make_test(file)
    for key, value in result_test.items():
        print(f"Fichier ‘test/{key}’")
        print(f"\tCorrect        : {value[0]}")
        print(f"\tEr. Syntaxique : {value[1]}")
        print(f"\tEr. Semantique : {value[2]}")
        print(f"\tEr. Autre      : {value[3]}")
        print(f"\tGen. Warning   : {value[4]}")
        print(f"\n\tSomme ---------> {sum(value)}\n\n")
    return 0



if __name__ == "__main__":
    main()
