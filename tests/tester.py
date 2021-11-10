import os
import subprocess
import shutil
import getopt
import sys
import glob

class colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    END = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def main(argv):
	try:
		opts, args = getopt.getopt(argv,"vsmd")
	except getopt.GetoptError:
		print ('Problem args tester.py')
		sys.exit(2)
	all_test = True if not opts else False
	for opt, arg in opts:
		vector_test = True if opt == "-v" else False
		stack_test = True if opt == "-s" else False
		map_test = True if opt == "-m" else False
		if opt == "-d" : shutil.rmtree("results"); shutil.rmtree("bin")

	dirs = os.listdir("tests")
	# if "main.cpp" in dirs : dirs.remove("main.cpp")
	# if "tester.py" in dirs : dirs.remove("tester.py")
	for dir in dirs:
		if all_test or (vector_test and dir == "vector") or (stack_test and dir == "stack") or (map_test and dir == "map"):
			sub_dirs = os.listdir("tests/" + dir)
			print(colors.OKBLUE + colors.BOLD + "============\n-> " + dir.upper() + " <-\n============" + colors.END)
			for sub_dir in sub_dirs:
				path_srcs_test = "tests/" + dir + "/" + sub_dir
				path_result = ("results/" + dir + "/" + sub_dir).replace('.cpp', '')
				path_bin = ("bin/" + dir + "/" + sub_dir).replace('.cpp', '')
				os.makedirs(path_bin, exist_ok = True)
				os.makedirs(path_result, exist_ok = True)
				if not os.path.exists(path_bin + "_mine") or (os.path.exists(path_bin + "_mine") and os.path.getctime(path_srcs_test) > os.path.getctime(path_bin + "_mine")):
					subprocess.run(("clang++ -D MINE -Werror -Wall -Wextra -Iinc tests/main.cpp " + path_srcs_test + " -o " + path_bin + "_mine").split(), capture_output=False)
				if not os.path.exists(path_bin + "_std") or (os.path.exists(path_bin + "_std") and os.path.getctime(path_srcs_test) > os.path.getctime(path_bin + "_std")):
					subprocess.run(("clang++ -Werror -Wall -Wextra -Iinc tests/main.cpp " + path_srcs_test + " -o " + path_bin + "_std").split(), capture_output=False)
				with open((path_result + "/stdout_mine"), "w") as outfile:
					subprocess.run((path_bin + "_mine ").split(), stdout=outfile)
				with open((path_result + "/stdout_std"), "w") as outfile:
					subprocess.run((path_bin + "_std").split(), stdout=outfile)
				with open((path_result + "/diff_stdout"), "w") as outfile:
					subprocess.run(("diff " + path_result + "/stdout_mine " + path_result + "/stdout_std").split(), stdout=outfile)
				if os.path.getsize(path_result + "/diff_stdout") == 0:
					print(colors.BOLD + path_result[path_result.rfind("/") + 1:] + colors.OKGREEN + " : [OK]" + colors.END)
				else:
					print(colors.BOLD + path_result[path_result.rfind("/") + 1:] + colors.FAIL + " : [NOK]" + colors.END)
					with open(path_result + "/diff_stdout", "r") as diff:
						print(diff.read())

if __name__ == "__main__":
   main(sys.argv[1:])