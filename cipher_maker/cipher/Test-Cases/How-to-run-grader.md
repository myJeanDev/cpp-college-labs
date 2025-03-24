a. After unzipping the test cases folder, pull out submission-grader.sh from the Test-Cases folder and place submission-grader.sh in the same parent folder as your submission (`.tar.gz`) file and the `Test-Cases` folder. Let's say you have a directory called `PA1`. It should look like the following:

	PA1/
	├── Test-Cases
	├── submission-grader.sh
	├── ABC-XYZ.tar.gz

b. Make sure that `submission-grader.sh` is executable (you can check this by running `ls -al` command). If it's not then run: 

	chmod +x submission-grader.sh

c. Your `.tar.gz` file will be given as an argument to the grader. Essentially, run it like this while you're in the `PA1` folder as shown in step `1`:

	./submission-grader.sh ABC-XYZ.tar.gz

Where `ABC-XYZ.tar.gz` is your submission.

d. Example Output from the grader:

```bash
1. Creating student submission directory...
✅ Student submission directory Faruk-Tanjim created.

2. Untaring submission...
./
./block.cpp
./utility.cpp
./block.h
./main.cpp
./cipher
./Makefile
./stream.cpp
./stream.h
./utility.h
✅ Uncompressed submission.

3. Executing Makefile...
Makefile directory is Faruk-Tanjim
Moving into Faruk-Tanjim to execute make command...
// instructions from the Makefile are omitted
✅ Make command succeeded

4. Finding Executable...
✅ Found executable cipher

Moving back to ... // directory name omitted

5. Cipher Type Argument Validation

Output = Invalid Cipher Type
✅ Status: PASSED (Found expected indication of failure: 'invalid')
✅ B/S Argument Validated

6. Mode of Operation Argument Validation

Output = Invalid Mode of Operation
✅ Status: PASSED (Found expected indication of failure: 'invalid')
✅ E/D Argument Validated

==========> Rubric Criteria 1. Argument Validation Total = 2/2

7. Input File Existence Check

Output = xyz.txt does not exist
✅ Status: PASSED (Found expected indication of failure: 'does not exist')
✅ Input File Existence Validation Passed

8. Key File Existence Check

Output = xyz.txt does not exist
✅ Status: PASSED (Found expected indication of failure: 'does not exist')
✅ Key File Existence Validation Passed

==========> Rubric Criteria 2. Input and Key File Existence Check Total = 4/4

8. Empty Input Check

✅ Block Cipher Empty Input: Encryption Passed
✅ Block Cipher Empty Input: Decryption Passed

✅ Stream Cipher Empty Input: Encryption Passed
✅ Stream Cipher Empty Input: Decryption Passed

==========> Rubric Criteria 3. Empty Output Total = 4/4

9. Block Cipher Test Cases
✅ Block Cipher Test Case 1: Encryption Passed
✅ Block Cipher Test Case 1: Decryption Passed

✅ Block Cipher Test Case 2: Encryption Passed
✅ Block Cipher Test Case 2: Decryption Passed

✅ Block Cipher Test Case 3: Encryption Passed
✅ Block Cipher Test Case 3: Decryption Passed

==========> Rubric Criteria 4. Block Cipher Total = 54/54

10. Stream Cipher Test Cases

✅ Stream Cipher Test Case 1: Encryption Passed
✅ Stream Cipher Test Case 1: Decryption Passed

✅ Stream Cipher Test Case 2: Encryption Passed
✅ Stream Cipher Test Case 2: Decryption Passed

==========> Rubric Criteria 5. Stream Cipher Total = 36/36

==========> Rubric Criteria Report <==========
Check arguments (function type and mode of operation): 2 / 2 pts
Check if the input and key files exist: 4 / 4 pts
Empty input handling: 4 / 4 pts
Block Cipher Correctness: 54 / 54 pts
Stream Cipher Correctness: 36 / 36 pts

Total Points: 100 / 100

Deleting student submission directory
✅ Student submission directory deleted
```
