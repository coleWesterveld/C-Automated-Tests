# Automated Testing for Assignments In C with Unity Framework

## 🚀 Overview
This was made to allow easy sharing of unit tests for assignments. 
Anyone can clone or fork and easily run tests on their own code or contribute testcases.

Then, put your code in private folder and run the makefile, and the project will automatically ensure your functions have the proper output for input.

This is **NOT** to share function definition code, only shared unit tests which I have made as easy as possible to test your code.

[Find out more about Unity here.](https://www.throwtheswitch.org/unity)
---

## 📁 Project Structure

```
/your_project/
├── build/                           # Build files (ignored in Git)
│   ├── lastnameFirstnameA1/         # Compiled object files for your project
│   └── Debug/                       # Debug build folder
│       └── lastnameFirstnameA1      # Debug build of your project
├── tests/                           # Unit tests (collaborative) moved to root
│   ├── unity.c                      # Unity framework source file - do not touch
│   ├── unity.h                      # Unity framework header file - do not touch
│   └── test_assignment.c            # Shared test cases
├── private/                         # Private code (DO NOT SHARE)
│   ├── lastnameFirstnameA1.c        # Your function definitions
│   ├── lastnameFirstnameA1Main.c    # Main source file
│   ├── givenAX.h                    # Header file (shared only with collaborators)
├── Makefile                         # For compilation & testing
├── README.md                        # Instructions for setting up
├── .gitignore                       # Ignore private files

```

---

## 🛠️ Setup & Usage

### 1️⃣ Clone or Download the Shared Test Files
```sh
git clone https://github.com/coleWesterveld/C-Automated-Tests.git
cd C-Automated-Tests
```

### 2️⃣ Setup Your Private Code
1. **Create a `private/` directory** if it doesn’t exist.
2. **Copy all assignment files into `private/`** 

### 3️⃣ Update the filename in the makefile
Modify **one lines** in `makefile` to match the correct assignment:
```make
SRC_NAME = lastnameFirstnameAX # Change to match your filename, ie. doeJaneA1
```
The makefile will use this assume your main file name (doeJaneA1Main) and your executable (doeJaneA1)
It will also interpret the extensions, so you **do not** have to add that to `SRC_NAME`

### 4️⃣ Add your tests 
The tests are created using the Unity test framework by ThrowTheSwitch
Go into `tests/test_assignment.c` and follow the instructions there
1. **include any files** which contain the prototypes of functions you will test, as well as any files you may need such as `math.h` or `string.h` if they are not already included in one of your header files
2. **Create test functions**: In your test function you will need to:
-  mock up inputs for your function you want to test
- call your function with those inputs
- compare then to an expected output using TEST_ASSERT_EQUAL_{var type here}(expected, actual);
You can see examples in the test file, or check the reference for all assertions [HERE](https://github.com/ThrowTheSwitch/Unity/blob/master/docs/UnityAssertionsReference.md)
3. **Run your tests** by adding `RUN_TEST(your_test)` in the appropriate part in main in `tests/test_assignment.c`

### 5️⃣ Make
There are a few options for make: 
```sh
make test
```
to run the tests 
If the tests pass, you’ll see:
```
==================== RUNNING TESTS ====================
✅ test_StringEquality: PASS
✅ test_ArrayEquality: PASS
✅ test_StructEquality: PASS
==================== END OF TESTS ====================
```
If any test fails, Unity will highlight the failed test in **red**.
You should also see the expected value and the actual value to help you debug.

```sh
make main
```
To quickly build and run your program. It will compile and link all your files into an executable and then immediately run the executable

```sh
make debug
```
To create an executable in `/build/Debug/` which can easily be run in VSCode by using Run and Debug from the left side extensions bar
You will likely need to setup a `launch.json` file, see the documentation [HERE](https://code.visualstudio.com/docs/cpp/launch-json-reference), but also here is an example of how it could look:

```sh
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Debug",
            "program": "${workspaceFolder}/build/Debug/lastnameFirstnameA1",
            "args": ["private/a1Data.txt"],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```

```sh
  make
```
will compile and link your project, and create an executable as `build/lastnameFirstnameA1` which can be run in the command line via 

```sh
  ./build/lastnameFirstnameA1 private/a1Data.txt
```
Of course replacing mock values with your actual ones. here we are passing `a1Data.txt` as a command line argument.

To remove compiled files and reset the build:
```sh
make clean
```


---

## ✅ Rules for Collaboration
- ✅ **You can share:** `tests/` directory (given header file & tests)
- ❌ **Do NOT share:** `private/` directory (your function implementations)

---

## 🔍 Example Test Case
You can test **strings, arrays, and structs** like this:

```c
#include "unity.h"
#include "../shared/givenA1.h"
#include <string.h>

void test_StringEquality(void) {
    TEST_ASSERT_EQUAL_STRING("Hello, World!", get_hello());
}

void test_ArrayEquality(void) {
    int expected[] = {1, 2, 3, 4, 5};
    int actual[5];
    get_numbers(actual, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 5);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_StringEquality);
    RUN_TEST(test_ArrayEquality);
    return UNITY_END();
}
```

---

## 📢 Troubleshooting

### Q: **When I run `make test` or `make debug` I get an error:**
```sh
make: *** No rule to make target `test'.  Stop.
```

**Ensure you are in the right directory.** when running any make command, it will execute the `makefile` in your current directory. if you are in `/private`, you could be running your `makefile` which does not have `test` and `debug`, and so you are getting an error. It is okay to leave _**your**_ `makefile` in `/private` to keep your whole assignment together, just make sure you `cd` into the root directory to run the correct `makefile`.

### Q: **I see compilation errors related to missing functions!**
✔ Ensure your **private C file** is correctly named (`private/lastnameFirstnameA1.c`).
✔ Make sure your functions are declared in `givenA1.h`.
You should **NOT** have to change any imports in your main or functions file, however when you reference files in `tests/test_assignment.c` you need to have the correct path. 
When using `#include`, you need the _relative_ path of your files, for example (in `tests/test_assignment.c`):
```sh
  #include "../private/givenA1.h"
```
when using a path for `fopen` for example, use the absolute path from your root directory. For example (in `tests/test_assignment.c`):
```sh
  fptr = fopen("private/givenA1.h", "r");
```

### Q: **I see linking errors related to missing files!**
✔ Ensure your **private C file** is correctly named (`private/lastnameFirstnameA1.c`).
✔ Make sure your functions are declared in `givenA1.h`.

### Q: **Tests are not running!**
✔ Ensure you have `gcc` and `make` installed:
```sh
gcc --version
make --version
```
✔ Run `make clean && make test` to rebuild everything.

---

## 🚀 Summary
- ✅ **Change only `lastnameFirstnameAX`** in `Makefile` for new assignments.
- ✅ **Keep private code separate** and only share `tests/`.
- ✅ **Run `make test`** to validate your functions.
- ✅ **Run `make main`** to to quickly compile and execute.
- ✅ **GitHub (optional)**: Use `git pull` to get the latest tests.

---

**NOTE:** my reccomendation is to run your assignment inside private and using `make main` _most of the time_, however before you go to hand your code in you should put it in a separate folder/environment (best thing would be the same enviroment the graders are using) and run it there to ensure that your `makefile` works as intended and you didn't mess up the directories.

---

This setup makes it **easy to collaborate** while keeping assignments private.
