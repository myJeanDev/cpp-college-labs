#!/bin/bash

check_mark='\U2705'
cross_mark='\U274C'
timeout_duration=10

if [ ! -f "$1" ]; then
    echo "Provided argument is not a file. Please provide a .tar.gz file"
    exit 1
fi

filename=$1

submission_directory="${filename%.*}"
submission_directory="${submission_directory%.*}"

echo "1. Creating student submission directory..."

mkdir -p "$submission_directory"

echo -e "$check_mark Student submission directory $submission_directory created.\n"

echo "2. Untaring submission..."

tar -xvzf "$filename" -C "$submission_directory"               

echo -e "$check_mark Uncompressed submission.\n"

echo "3. Executing Makefile..."

makefile_path=$(find "$submission_directory" \( -name 'Makefile' \) -print -quit)

makefile_dir=""

if [ ! -z "$makefile_path" ]; then
        makefile_dir=$(dirname "$makefile_path")
        echo "Makefile directory is $makefile_dir"
else
        echo -e "$cross_mark Makefile not found in the submission."
fi

original_dir=$(pwd)

echo "Moving into $makefile_dir to execute make command..."

[ ! -z "$makefile_path" ] && cd "$makefile_dir" && make

if [ $? -eq 0 ]; then
        echo -e "$check_mark Make command succeeded\n"
else
        echo -e "$cross_mark Make failed with status $?\n"
fi

rm -f *.o *.txt

echo "4. Finding Executable..."

executable=""

if find . -maxdepth 1 -type f -name 'cipher' -executable | grep -q 'cipher'; then
    echo -e "$check_mark Found executable cipher\n"
    executable="./cipher"
else
    echo -e "$cross_mark Executable 'cipher' not found."
fi

executable_path=""

if [ ! -z "$executable" ]; then
        executable_path="$makefile_dir/$executable"
fi

echo -e "Moving back to $original_dir\n"

cd "$original_dir"

# Run through the test cases

execute_and_check_for_crash() {
    command_output=$("$@" 2>&1)
    status=$?

    if [ $status -eq 124 ]; then
        # Timeout occurred
        echo -e "$cross_mark Execution failed: Timeout after ${timeout_duration} seconds"
        return 1
    elif [ $status -eq 139 ]; then
        # Segmentation fault
        echo -e "$cross_mark Execution failed: Segmentation fault (core dumped)"
        return 1
    elif [ $status -gt 1 ]; then
        # Other errors
        echo -e "$cross_mark Execution failed with status $status"
        return 1
    else
        return 0
    fi
}

[ ! -f Test-Cases/empty.txt ] && touch Test-Cases/empty.txt

run_test_and_check_output() {
    argument_parse_output=$("${@:2}" 2>&1)
    status=$?
    
    if [ $status -eq 124 ]; then
        echo -e "$cross_mark Execution failed: Timeout after ${timeout_duration} seconds"
        return 2
    elif [ $status -eq 139 ]; then
        echo -e "$cross_mark Execution failed: Segmentation fault (core dumped)"
        return 2
    elif [ $status -gt 1 ]; then
        echo -e "$cross_mark Execution failed with status $status"
        return 2
    else
        if [[ "$argument_parse_output" == "$1" ]]; then
		    echo "Output = $argument_parse_output"
		    echo -e "$check_mark Status: PASSED (Found expected indication of failure: '$1')"
            return 0
        else
		    echo "Output = $argument_parse_output"
            echo -e "$cross_mark Status: FAILED (Did not find expected indication of failure: '$1')"
            return 1
        fi
    fi
}

cipher_type_validation_message="Invalid Function Type"
mode_type_validation_message="Invalid Mode Type"
input_file_validation_message="Input File Does Not Exist"
key_file_validation_message="Key File Does Not Exist"

echo -e "5. Cipher Type Argument Validation\n"

argument_validation_total=0

[ ! -z "$executable" ] && run_test_and_check_output "$cipher_type_validation_message" "$executable_path" A Test-Cases/Block-Cipher/1/bc-input-tc-1.txt out.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt E

if [ $? -eq 0 ]; then
        echo -e "$check_mark B/S Argument Validated\n"
        ((argument_validation_total++))
elif [ $? -eq 1 ]; then 
        echo -e "$cross_mark No Validation for B/S Argument\n"
else
        echo -e "$cross_mark An Error Occurred While Validating B/S Argument\n"
fi

echo -e "6. Mode of Operation Argument Validation\n"

[ ! -z "$executable" ] && run_test_and_check_output "$mode_type_validation_message" "$executable_path" B Test-Cases/Block-Cipher/1/bc-input-tc-1.txt out.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt X

if [ $? -eq 0 ]; then
        echo -e "$check_mark E/D Argument Validated\n"
        ((argument_validation_total++));
elif [ $? -eq 1 ]; then
        echo -e "$cross_mark No Validation for E/D Argument\n"
else
        echo -e "$cross_mark An Error Occurred While Validating E/D Argument\n"
fi

echo -e "==========> Rubric Criteria 1. Argument Validation Total = $argument_validation_total/2\n"

input_file_check_total=0
key_file_check_total=0

echo -e "7. Input File Existence Check\n"

[ ! -z "$executable" ] && run_test_and_check_output "$input_file_validation_message" "$executable_path" B xyz.txt out.txt Test-Case/Block-Cipher/1/bc-key-tc-1.txt E

if [ $? -eq 0 ]; then
        ((input_file_check_total+=2));
        echo -e "$check_mark Input File Existence Validation Passed\n"
elif [ $? -eq 1 ]; then
        echo -e "$cross_mark Input File Existence Validation Failed\n"
else
        echo -e "$cross_mark An Error Occurred While Checking Existence of Input File\n"
fi

echo -e "8. Key File Existence Check\n"

[ ! -z "$executable" ] && run_test_and_check_output "$key_file_validation_message" "$executable_path" B Test-Cases/Block-Cipher/1/bc-input-tc-1.txt out.txt xyz.txt E

if [ $? -eq 0 ]; then
        ((key_file_check_total+=2));
        echo -e "$check_mark Key File Existence Validation Passed\n"
elif [ $? -eq 1 ]; then
        echo -e "$cross_mark Key File Existence Validation Failed\n"
else
        echo -e "$cross_mark An Error Occurred While Checking Existence of Key File\n"
fi

echo -e "==========> Rubric Criteria 2. Input and Key File Existence Check Total = $(($input_file_check_total + $key_file_check_total))/4\n"

echo -e "8. Empty Input Check\n"

empty_output_total=0

# Block Cipher Empty Input

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/empty.txt "$submission_directory"/b-e-output-for-empty-input.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Empty: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred"
else
        if [ -f "$submission_directory"/b-e-output-for-empty-input.txt ] && [ ! -s "$submission_directory"/b-e-output-for-empty-input.txt ]; then
                echo -e "$check_mark Block Cipher Empty Input: Encryption Passed"
                ((empty_output_total++))
        else
                echo -e "$cross_mark Block Cipher Empty Input: Encryption Failed (No Output File or Non Empty Output)"
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/empty.txt "$submission_directory"/b-d-output-for-empty-input.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Empty: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-d-output-for-empty-input.txt ] && [ ! -s "$submission_directory"/b-d-output-for-empty-input.txt ]; then
                echo -e "$check_mark Block Cipher Empty Input: Decryption Passed\n"
                ((empty_output_total++))
        else
                echo -e "$cross_mark Block Cipher Empty Input: Decryption Failed (No Output File Or Non Empty Output)\n"
        fi
fi

# Stream Cipher Empty Input

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/empty.txt "$submission_directory"/s-e-output-for-empty-input.txt Test-Cases/Stream-Cipher/1/sc-key-tc-1.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Empty: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred"
else
        if [ -f "$submission_directory"/s-e-output-for-empty-input.txt ] && [ ! -s "$submission_directory"/s-e-output-for-empty-input.txt ]; then
                echo -e "$check_mark Stream Cipher Empty Input: Encryption Passed"
                ((empty_output_total++))
        else
                echo -e "$cross_mark Stream Cipher Empty Input: Encryption Failed (No Output File Or Non Empty Output)"
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/empty.txt "$submission_directory"/s-d-output-for-empty-input.txt Test-Cases/Stream-Cipher/1/sc-key-tc-1.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Empty: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/s-d-output-for-empty-input.txt ] && [ ! -s "$submission_directory"/s-d-output-for-empty-input.txt ]; then
                echo -e "$check_mark Stream Cipher Empty Input: Decryption Passed\n"
                ((empty_output_total++))
        else
                echo -e "$cross_mark Stream Cipher Empty Input: Decryption Failed (No Output File Or Non Empty Output)\n"
        fi
fi

echo -e "==========> Rubric Criteria 3. Empty Output Total = $empty_output_total/4\n"

# Block Cipher Test Cases

echo -e "9. Block Cipher Test Cases"

block_cipher_total=0

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/1/bc-input-tc-1.txt "$submission_directory"/b-e-output-tc-1.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 1: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-e-output-tc-1.txt ] && diff -q Test-Cases/Block-Cipher/1/bc-encrypted-output-tc-1.txt "$submission_directory"/b-e-output-tc-1.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 1: Encryption Passed"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 1: Encryption Failed"
                # diff Test-Cases/Block-Cipher/1/bc-encrypted-output-tc-1.txt "$submission_directory"/b-e-output-tc-1.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/1/bc-encrypted-output-tc-1.txt "$submission_directory"/b-d-output-tc-1.txt Test-Cases/Block-Cipher/1/bc-key-tc-1.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 1: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-d-output-tc-1.txt ] && diff -q Test-Cases/Block-Cipher/1/bc-decrypted-output-tc-1.txt "$submission_directory"/b-d-output-tc-1.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 1: Decryption Passed\n"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 1: Decryption Failed\n"
                # diff Test-Cases/Block-Cipher/1/bc-decrypted-output-tc-1.txt "$submission_directory"/b-d-output-tc-1.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/2/bc-input-tc-2.txt "$submission_directory"/b-e-output-tc-2.txt Test-Cases/Block-Cipher/2/bc-key-tc-2.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 2: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-e-output-tc-2.txt ] && diff -q Test-Cases/Block-Cipher/2/bc-encrypted-output-tc-2.txt "$submission_directory"/b-e-output-tc-2.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 2: Encryption Passed"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 2: Encryption Failed"
                # diff Test-Cases/Block-Cipher/2/bc-encrypted-output-tc-2.txt "$submission_directory"/b-e-output-tc-2.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/2/bc-encrypted-output-tc-2.txt "$submission_directory"/b-d-output-tc-2.txt Test-Cases/Block-Cipher/2/bc-key-tc-2.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 2: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-d-output-tc-2.txt ] && diff -q Test-Cases/Block-Cipher/2/bc-decrypted-output-tc-2.txt "$submission_directory"/b-d-output-tc-2.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 2: Decryption Passed\n"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 2: Decryption Failed\n"
                # diff Test-Cases/Block-Cipher/2/bc-decrypted-output-tc-2.txt "$submission_directory"/b-d-output-tc-2.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/3/bc-input-tc-3.txt "$submission_directory"/b-e-output-tc-3.txt Test-Cases/Block-Cipher/3/bc-key-tc-3.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 3: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-e-output-tc-3.txt ] && diff -q Test-Cases/Block-Cipher/3/bc-encrypted-output-tc-3.txt "$submission_directory"/b-e-output-tc-3.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 3: Encryption Passed"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 3: Encryption Failed"
                # diff Test-Cases/Block-Cipher/3/bc-encrypted-output-tc-3.txt "$submission_directory"/b-e-output-tc-3.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" B Test-Cases/Block-Cipher/3/bc-encrypted-output-tc-3.txt "$submission_directory"/b-d-output-tc-3.txt Test-Cases/Block-Cipher/3/bc-key-tc-3.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Block Cipher Test Case 3: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/b-d-output-tc-3.txt ] && diff -q Test-Cases/Block-Cipher/3/bc-decrypted-output-tc-3.txt "$submission_directory"/b-d-output-tc-3.txt > /dev/null; then
                echo -e "$check_mark Block Cipher Test Case 3: Decryption Passed\n"
                ((block_cipher_total+=9))
        else
                echo -e "$cross_mark Block Cipher Test Case 3: Decryption Failed\n"
                # diff Test-Cases/Block-Cipher/3/bc-decrypted-output-tc-3.txt "$submission_directory"/b-d-output-tc-3.txt
        fi
fi

echo -e "==========> Rubric Criteria 4. Block Cipher Total = $block_cipher_total/54\n"

# Stream Cipher Test Cases

echo -e "10. Stream Cipher Test Cases\n"

stream_cipher_total=0

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/Stream-Cipher/1/sc-input-tc-1.txt "$submission_directory"/s-e-output-tc-1.txt Test-Cases/Stream-Cipher/1/sc-key-tc-1.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Test Case 1: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/s-e-output-tc-1.txt ] && diff -q Test-Cases/Stream-Cipher/1/sc-encrypted-output-tc-1.txt "$submission_directory"/s-e-output-tc-1.txt > /dev/null; then
                echo -e "$check_mark Stream Cipher Test Case 1: Encryption Passed"
                ((stream_cipher_total+=9))
        else
                echo -e "$cross_mark Stream Cipher Test Case 1: Encryption Failed"
                # diff Test-Cases/Stream-Cipher/1/sc-encrypted-output-tc-1.txt "$submission_directory"/s-e-output-tc-1.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/Stream-Cipher/1/sc-encrypted-output-tc-1.txt "$submission_directory"/s-d-output-tc-1.txt Test-Cases/Stream-Cipher/1/sc-key-tc-1.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Test Case 1: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/s-d-output-tc-1.txt ] && diff -q Test-Cases/Stream-Cipher/1/sc-decrypted-output-tc-1.txt "$submission_directory"/s-d-output-tc-1.txt > /dev/null; then
                echo -e "$check_mark Stream Cipher Test Case 1: Decryption Passed\n"
                ((stream_cipher_total+=9))
        else
                echo -e "$cross_mark Stream Cipher Test Case 1: Decryption Failed\n"
                # diff Test-Cases/Stream-Cipher/1/sc-decrypted-output-tc-1.txt "$submission_directory"/s-d-output-tc-1.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/Stream-Cipher/2/sc-input-tc-2.txt "$submission_directory"/s-e-output-tc-2.txt Test-Cases/Stream-Cipher/2/sc-key-tc-2.txt E

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Test Case 2: Encryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/s-e-output-tc-2.txt ] && diff -q Test-Cases/Stream-Cipher/2/sc-encrypted-output-tc-2.txt "$submission_directory"/s-e-output-tc-2.txt > /dev/null; then
                echo -e "$check_mark Stream Cipher Test Case 2: Encryption Passed"
                ((stream_cipher_total+=9))
        else
                echo -e "$cross_mark Stream Cipher Test Case 2: Encryption Failed"
                # diff Test-Cases/Stream-Cipher/2/sc-encrypted-output-tc-2.txt "$submission_directory"/s-e-output-tc-2.txt
        fi
fi

[ ! -z "$executable" ] && execute_and_check_for_crash "$executable_path" S Test-Cases/Stream-Cipher/2/sc-encrypted-output-tc-2.txt "$submission_directory"/s-d-output-tc-2.txt Test-Cases/Stream-Cipher/2/sc-key-tc-2.txt D

if [ $? -ne 0 ]; then
        echo -e "$cross_mark Stream Cipher Test Case 2: Decryption Failed Due to Segmentation Fault (Core Dumped) or An Error Occurred\n"
else
        if [ -f "$submission_directory"/s-d-output-tc-2.txt ] && diff -q Test-Cases/Stream-Cipher/2/sc-decrypted-output-tc-2.txt "$submission_directory"/s-d-output-tc-2.txt > /dev/null; then
                echo -e "$check_mark Stream Cipher Test Case 2: Decryption Passed\n"
                ((stream_cipher_total+=9))
        else
                echo -e "$cross_mark Stream Cipher Test Case 2: Decryption Failed\n"
                # diff Test-Cases/Stream-Cipher/2/sc-decrypted-output-tc-2.txt "$submission_directory"/s-d-output-tc-2.txt
        fi
fi

echo -e "==========> Rubric Criteria 5. Stream Cipher Total = $stream_cipher_total/36\n"

echo "==========> Rubric Criteria Report <=========="
echo "Check arguments (function type and mode of operation): $argument_validation_total / 2 pts"
echo "Check if the input and key files exist: $(($input_file_check_total + $key_file_check_total)) / 4 pts"
echo "Empty input handling: $empty_output_total / 4 pts"
echo "Block Cipher Correctness: $block_cipher_total / 54 pts"
echo "Stream Cipher Correctness: $stream_cipher_total / 36 pts"
echo ""

# Calculate the total points
total_points=$(($argument_validation_total + $input_file_check_total + $key_file_check_total + $empty_output_total + $block_cipher_total + $stream_cipher_total))
echo -e "Total Points: $total_points / 100\n"

# Cleanup

echo "Deleting student submission directory"

rm -rf "$submission_directory"

echo -e "$check_mark Student submission directory deleted\n"

rm -f *.txt *.o Test-Cases/empty.txt