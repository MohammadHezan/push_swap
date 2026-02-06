*This project has been created as part of the 42 curriculum by mhaizan.*

<!-- Project Banner -->
<div align="center">
  <h1>🔄 Push_Swap</h1>
  <p><em>An efficient sorting algorithm using two stacks with limited operations</em></p>
  
  ![42 Badge](https://img.shields.io/badge/42-Project-blue)
  ![Language](https://img.shields.io/badge/Language-C-green)
  ![Norminette](https://img.shields.io/badge/Norminette-Passing-success)
  ![Score](https://img.shields.io/badge/Score-84%2F100-brightgreen)
  
  <p><strong>A 42 School Algorithm Project by mhaizan</strong></p>
  <img width="201" height="170" alt="Screenshot from 2026-02-06 12-50-05" src="https://github.com/user-attachments/assets/2a9c6e0c-a707-4d51-8806-073e49727ae8" />

</div>

---

## 📋 Table of Contents

1. [Description](#-description)
2. [Instructions](#-instructions)
3. [42 School Rules & Requirements](#-42-school-rules--requirements)
4. [The Challenge](#-the-challenge)
5. [Understanding Stacks](#-understanding-stacks)
6. [Available Operations](#-available-operations)
7. [Algorithm Selection](#-algorithm-selection)
8. [The Radix Sort Algorithm](#-the-radix-sort-algorithm)
9. [Small Input Optimization](#-small-input-optimization)
10. [Project Architecture](#-project-architecture)
11. [Performance Analysis](#-performance-analysis)
12. [Code Walkthrough](#-code-walkthrough)
13. [Error Handling](#-error-handling)
14. [Memory Management](#-memory-management)
15. [Testing](#-testing)
16. [What I Learned](#-what-i-learned)
17. [Resources](#-resources)

---

## 📝 Description

**Push_swap** is an algorithmic project from the 42 School curriculum that challenges students to sort a stack of integers using a limited set of operations. The project's goal is to implement an efficient sorting algorithm that minimizes the number of operations needed to sort any given input.

### Project Goal

The primary objective is to sort **Stack A** in ascending order using only the allowed stack operations (`sa`, `pb`, `pa`, `ra`, `rra`, etc.). The challenge lies in finding the most efficient sequence of operations, as the project is graded based on how few operations are used.

### Brief Overview

This implementation uses a **hybrid sorting approach**:

- **For small inputs (2-5 elements)**: Optimized, hardcoded sorting strategies that minimize operations
- **For large inputs (6+ elements)**: A **Radix Sort algorithm** adapted for two stacks, which processes numbers bit by bit

The radix sort approach was chosen because:
- It provides **consistent, predictable performance** regardless of input order
- It works naturally with the two-stack constraint (elements are partitioned by bit value)
- It achieves operation counts well within the 42 grading benchmarks

### Key Features

- ✅ Handles any valid 32-bit signed integers (INT_MIN to INT_MAX)
- ✅ Validates input for duplicates, non-integers, and overflow
- ✅ Optimized for small inputs (3 elements: max 2 operations, 5 elements: max 12 operations)
- ✅ Efficient radix sort for large inputs (100 elements: ~1,084 operations, 500 elements: ~6,784 operations)
- ✅ Fully Norminette compliant
- ✅ No memory leaks

---

## 📖 Instructions

### Prerequisites

Before compiling, ensure you have:
- **GCC** or **Clang** compiler
- **Make** build system
- A Unix-like operating system (Linux, macOS, or WSL on Windows)

### Compilation

Clone the repository and compile using the Makefile:

```bash
# Clone the repository
git clone https://github.com/yourusername/push_swap.git
cd push_swap

# Compile the program
make

# The executable 'push_swap' will be created in the root directory
```

#### Makefile Rules

| Command | Description |
|---------|-------------|
| `make` or `make all` | Compile the program |
| `make clean` | Remove object files (`.o` files) |
| `make fclean` | Remove object files and the executable |
| `make re` | Recompile everything from scratch |

### Installation

No installation is required. After compilation, the `push_swap` executable can be run directly from the project directory.

### Execution

The program accepts integers as command-line arguments:

```bash
# Basic usage with separate arguments
./push_swap 4 67 3 87 23

# Alternative: numbers as a single quoted string
./push_swap "4 67 3 87 23"
```

#### Output

The program outputs one operation per line to **stdout**:

```bash
$ ./push_swap 3 2 1
sa
rra
```

#### Counting Operations

To count the number of operations:

```bash
./push_swap 3 2 1 | wc -l
```

#### Testing with Random Numbers

```bash
# Generate and sort 100 random numbers
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# Generate and sort 500 random numbers
ARG=$(shuf -i 1-10000 -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

#### Edge Cases

```bash
# Single element - no output (already sorted)
./push_swap 42

# Already sorted - no output
./push_swap 1 2 3 4 5

# Two elements - outputs "sa" if needed
./push_swap 2 1
```

#### Error Handling

Invalid inputs produce `Error` on stderr:

```bash
./push_swap 1 2 1      # Duplicate - Error
./push_swap 1 abc 2    # Non-integer - Error
./push_swap 9999999999 # Overflow - Error
```

---

## 🎯 Introduction

**Push_swap** is one of the most challenging algorithmic projects in the 42 curriculum. The goal is deceptively simple: sort a stack of integers. However, the constraints make it a fascinating puzzle that requires deep understanding of data structures, algorithm design, and optimization techniques.

### Why This Project Matters

This project teaches several fundamental concepts in computer science:

- **Algorithm Complexity**: Understanding Big O notation and why it matters
- **Data Structures**: Working with stacks and their operations
- **Optimization**: Finding the most efficient solution within constraints
- **Problem Decomposition**: Breaking complex problems into manageable pieces
- **Edge Case Handling**: Dealing with special inputs gracefully

The skills learned here directly apply to real-world software engineering, where choosing the right algorithm can mean the difference between software that runs in milliseconds versus hours.

---

## 📜 42 School Rules & Requirements

### The Norm (Norminette)

All code must comply with **42's coding standard** called "The Norm". This ensures consistent, readable code across all students:

| Rule | Description |
|------|-------------|
| **Function Length** | Maximum 25 lines per function |
| **Functions per File** | Maximum 5 functions per `.c` file |
| **Line Length** | Maximum 80 characters per line |
| **Variable Declaration** | All variables declared at the start of functions |
| **No `for` loops** | Only `while` loops are allowed |
| **No comments inside functions** | Comments only in headers |
| **Header Files** | Must have include guards (`#ifndef`, `#define`, `#endif`) |
| **Global Variables** | Forbidden (except `const` in some cases) |
| **Allowed Functions** | Only `write`, `read`, `malloc`, `free`, `exit` (no printf!) |

### Mandatory Part Requirements

The project **must** implement:

```
Program name    : push_swap
Turn in files   : Makefile, *.h, *.c (in organized folders)
Makefile rules  : NAME, all, clean, fclean, re
Arguments       : Stack A as integers (first argument = top of stack)
External functs : read, write, malloc, free, exit
Libft allowed   : No (must implement own utilities)
Description     : Sort stack A in ascending order using operations
```

### Allowed Operations (Subject-Defined)

The subject **strictly defines** these operations only:

| Operation | Description | Subject Definition |
|-----------|-------------|-------------------|
| `sa` | Swap A | Swap the first 2 elements at the top of stack A |
| `sb` | Swap B | Swap the first 2 elements at the top of stack B |
| `ss` | Swap Both | `sa` and `sb` at the same time |
| `pa` | Push A | Take the first element at the top of B and put it at the top of A |
| `pb` | Push B | Take the first element at the top of A and put it at the top of B |
| `ra` | Rotate A | Shift up all elements of stack A by 1 (first element becomes last) |
| `rb` | Rotate B | Shift up all elements of stack B by 1 |
| `rr` | Rotate Both | `ra` and `rb` at the same time |
| `rra` | Reverse Rotate A | Shift down all elements of stack A by 1 (last element becomes first) |
| `rrb` | Reverse Rotate B | Shift down all elements of stack B by 1 |
| `rrr` | Reverse Rotate Both | `rra` and `rrb` at the same time |

### Error Handling Requirements

The program must display `Error` followed by a newline (`\n`) on **stderr** in the following cases:

- ❌ Some arguments aren't integers
- ❌ Some arguments are bigger than an integer (`> INT_MAX` or `< INT_MIN`)
- ❌ There are duplicates
- ❌ Arguments contain non-numeric characters (except `+`/`-` for signs)

### Grading Benchmarks (Operations Limits)

To get **full points**, your program must sort within these operation limits:

| Input Size | Maximum Operations | Points |
|------------|-------------------|--------|
| 3 numbers | ≤ 3 operations | Required |
| 5 numbers | ≤ 12 operations | Required |
| 100 numbers | < 700 operations | 5 points |
| 100 numbers | < 900 operations | 4 points |
| 100 numbers | < 1100 operations | 3 points |
| 100 numbers | < 1300 operations | 2 points |
| 100 numbers | < 1500 operations | 1 point |
| 500 numbers | < 5500 operations | 5 points |
| 500 numbers | < 7000 operations | 4 points |
| 500 numbers | < 8500 operations | 3 points |
| 500 numbers | < 10000 operations | 2 points |
| 500 numbers | < 11500 operations | 1 point |

### Bonus Part: Checker Program

The bonus part requires implementing a **checker** program that:

1. Takes stack A as arguments (same as push_swap)
2. Reads operations from **stdin** (one per line)
3. Executes each operation on the stacks
4. Outputs:
   - `OK` if stack A is sorted and B is empty
   - `KO` otherwise
   - `Error\n` on invalid input

**Note**: This implementation focuses on the mandatory part only.

### What Makes a Valid Submission

✅ **Compiles** with `-Wall -Wextra -Werror` flags  
✅ **No memory leaks** (check with `valgrind`)  
✅ **No crashes** (segfault, bus error, double free, etc.)  
✅ **Handles edge cases** (empty input, single number, already sorted)  
✅ **Follows the Norm** (run `norminette` on all files)  
✅ **Makefile works** correctly with all required rules  
✅ **Meets operation benchmarks** for full points

---

## 🎮 The Challenge

### The Problem Statement

You are given:
- **Stack A**: Contains a random sequence of unique integers
- **Stack B**: Initially empty
- **Limited Operations**: Only specific operations are allowed (no random access!)

Your mission: Sort Stack A in **ascending order** using the **minimum number of operations**.

### Why Is This Hard?

Unlike arrays where you can access any element directly (`array[i]`), stacks only allow access to the **top element**. This limitation forces creative algorithmic thinking.

Consider sorting `[3, 1, 2]`:
- In an array, you could simply swap indices - easy!
- With stacks, you must carefully orchestrate push, swap, and rotate operations

### The Constraints

| Constraint | Description |
|------------|-------------|
| **Input Range** | Any valid 32-bit signed integer (-2,147,483,648 to 2,147,483,647) |
| **No Duplicates** | Each number must be unique |
| **Output** | Print each operation on a new line |
| **Error Handling** | Print "Error\n" to stderr for invalid input |

---

## 📚 Understanding Stacks

### What Is a Stack?

A stack is a **Last-In-First-Out (LIFO)** data structure. Think of it like a stack of plates:
- You can only add a plate to the **top**
- You can only remove a plate from the **top**

```
    ┌─────┐
    │  5  │  ← Top (most recently added)
    ├─────┤
    │  3  │
    ├─────┤
    │  1  │
    ├─────┤
    │  7  │  ← Bottom (first added)
    └─────┘
```

### Stack Operations in This Project

In push_swap, we implement stacks using arrays for efficiency:

```c
typedef struct s_stack
{
    int *arr;    // Dynamic array holding elements
    int size;    // Current number of elements
} t_stack;
```

**Why Arrays Instead of Linked Lists?**

| Aspect | Array | Linked List |
|--------|-------|-------------|
| **Memory Access** | O(1) random access | O(n) traversal needed |
| **Cache Performance** | Excellent (contiguous memory) | Poor (scattered memory) |
| **Implementation** | Simpler for rotations | More pointer management |
| **Memory Overhead** | Just the data | Extra pointer per node |

For this project, arrays provide better performance for the rotation operations we frequently use.

---

## 🔧 Available Operations

The project defines exactly these operations (no more, no less):

### Swap Operations

| Operation | Description | Visualization |
|-----------|-------------|---------------|
| `sa` | Swap first 2 elements of Stack A | `[2,1,3]` → `[1,2,3]` |
| `sb` | Swap first 2 elements of Stack B | (same logic) |
| `ss` | `sa` and `sb` simultaneously | (both stacks) |

### Push Operations

| Operation | Description | Visualization |
|-----------|-------------|---------------|
| `pa` | Push top of B onto A | A:`[2,3]` B:`[1]` → A:`[1,2,3]` B:`[]` |
| `pb` | Push top of A onto B | A:`[1,2,3]` B:`[]` → A:`[2,3]` B:`[1]` |

### Rotate Operations

| Operation | Description | Visualization |
|-----------|-------------|---------------|
| `ra` | Rotate A up (first → last) | `[1,2,3]` → `[2,3,1]` |
| `rb` | Rotate B up | (same logic) |
| `rr` | `ra` and `rb` simultaneously | (both stacks) |

### Reverse Rotate Operations

| Operation | Description | Visualization |
|-----------|-------------|---------------|
| `rra` | Rotate A down (last → first) | `[1,2,3]` → `[3,1,2]` |
| `rrb` | Rotate B down | (same logic) |
| `rrr` | `rra` and `rrb` simultaneously | (both stacks) |

### Visual Example: Sorting [3, 2, 1]

```
Initial:        After sa:       After rra:
A: [3, 2, 1]    A: [2, 3, 1]    A: [1, 2, 3] ✓
B: []           B: []           B: []

Operations: sa, rra (2 operations)
```

---

## 🤔 Algorithm Selection

### Why Not Simple Sorting Algorithms?

| Algorithm | Time Complexity | Why Not Suitable |
|-----------|-----------------|------------------|
| **Bubble Sort** | O(n²) | Too many operations for large inputs |
| **Selection Sort** | O(n²) | Requires finding minimum - expensive with stacks |
| **Quick Sort** | O(n log n) avg | Pivot selection with limited operations is complex |
| **Merge Sort** | O(n log n) | Requires extra space management |

### Why Radix Sort?

**Radix Sort** is perfect for push_swap because:

1. **Predictable Performance**: Always O(n × k) where k = number of bits
2. **Simple Operations**: Only needs to check if a bit is 0 or 1
3. **No Comparisons**: Doesn't compare elements directly
4. **Stack-Friendly**: Naturally uses two "buckets" (our two stacks!)

### My Hybrid Approach

I use different strategies based on input size:

| Input Size | Algorithm | Reason |
|------------|-----------|--------|
| 2 elements | Single `sa` | Trivial case |
| 3 elements | Hardcoded optimal | Only 6 permutations possible |
| 4-5 elements | Selection-based | More efficient than radix for tiny inputs |
| 6+ elements | Radix Sort | Scales efficiently |

---

## 🔢 The Radix Sort Algorithm

### Understanding Binary Numbers

Every integer can be represented in binary (base 2):

```
Decimal  →  Binary
   0     →   000
   1     →   001
   2     →   010
   3     →   011
   4     →   100
   5     →   101
```

### The Key Insight

Numbers with the same bit at a position share a property. By grouping numbers by each bit position, we can sort them!

### Step 1: Index Normalization

**Problem**: Input can be any integers like `[-50, 1000000, 42]`
**Solution**: Convert to indices based on relative order

```
Original:  [-50, 1000000, 42]
Sorted:    [-50, 42, 1000000]
Indices:   [0,   2,  1]  (position in sorted order)

After indexing: [0, 2, 1]Readme Requirements
A README.md file must be provided at the root of your Git repository. Its purpose is
to allow anyone unfamiliar with the project (peers, staff, recruiters, etc.) to quickly
understand what the project is about, how to run it, and where to find more information
on the topic.
The README.md must include at least:
• The very first line must be italicized and read: This project has been created as part
of the 42 curriculum by <login1>[, <login2>[, <login3>[...]]].
• A “Description” section that clearly presents the project, including its goal and a
brief overview.
• An “Instructions” section containing any relevant information about compilation,
installation, and/or execution.
• A “Resources” section listing classic references related to the topic (documentation, articles, tutorials, etc.), as well as a description of how AI was used —
specifying for which tasks and which parts of the project.
➠ Additional sections may be required depending on the project (e.g., usage
examples, feature list, technical choices, etc.).
Any required additions will be explicitly listed below.
Your README must be written in English.
```

**Why Index?**
- Indices are always 0 to n-1
- Binary representation is minimal (log₂(n) bits)
- Works uniformly regardless of actual values

### Step 2: Bit-by-Bit Sorting

For each bit position (starting from the least significant bit):

1. **Examine** the current bit of each element
2. **If bit = 0**: Push to Stack B (`pb`)
3. **If bit = 1**: Keep in Stack A (rotate with `ra`)
4. **After processing all**: Push everything back from B to A (`pa`)

### Detailed Example: Sorting [3, 0, 4, 1, 2]

**After Indexing**: Values are already indices!

```
Index:  Binary (3 bits):
  0  →  000
  1  →  001
  2  →  010
  3  →  011
  4  →  100
```

**Initial State**: A = [3, 0, 4, 1, 2], B = []

---

**Pass 1: Check Bit 0 (rightmost bit)**

| Element | Binary | Bit 0 | Action | Result |
|---------|--------|-------|--------|--------|
| 3 | 011 | 1 | ra | A=[0,4,1,2,3] |
| 0 | 000 | 0 | pb | A=[4,1,2,3] B=[0] |
| 4 | 100 | 0 | pb | A=[1,2,3] B=[4,0] |
| 1 | 001 | 1 | ra | A=[2,3,1] |
| 2 | 010 | 0 | pb | A=[3,1] B=[2,4,0] |

Push back: A = [0, 4, 2, 3, 1], B = []

---

**Pass 2: Check Bit 1 (middle bit)**

| Element | Binary | Bit 1 | Action | Result |
|---------|--------|-------|--------|--------|
| 0 | 000 | 0 | pb | A=[4,2,3,1] B=[0] |
| 4 | 100 | 0 | pb | A=[2,3,1] B=[4,0] |
| 2 | 010 | 1 | ra | A=[3,1,2] |
| 3 | 011 | 1 | ra | A=[1,2,3] |
| 1 | 001 | 0 | pb | A=[2,3] B=[1,4,0] |

Push back: A = [0, 4, 1, 2, 3], B = []

---

**Pass 3: Check Bit 2 (leftmost bit)**

| Element | Binary | Bit 2 | Action | Result |
|---------|--------|-------|--------|--------|
| 0 | 000 | 0 | pb | A=[4,1,2,3] B=[0] |
| 4 | 100 | 1 | ra | A=[1,2,3,4] |
| 1 | 001 | 0 | pb | A=[2,3,4] B=[1,0] |
| 2 | 010 | 0 | pb | A=[3,4] B=[2,1,0] |
| 3 | 011 | 0 | pb | A=[4] B=[3,2,1,0] |

Push back: A = [0, 1, 2, 3, 4], B = [] ✓ **SORTED!**

---

### The Code Implementation

```c
void radix_sort(t_stack *a, t_stack *b)
{
    int max_bits;
    int size;
    int bit;
    int i;

    // Step 1: Convert values to indices (0 to n-1)
    index_stack(a);
    
    // Step 2: Calculate bits needed (log2 of max value)
    max_bits = get_max_bits(a);
    
    // Step 3: Process each bit position
    bit = 0;
    while (bit < max_bits)
    {
        size = a->size;
        i = 0;
        while (i < size)
        {
            // Check if current bit is 0 or 1
            // (a->arr[0] >> bit) shifts right to target bit
            // & 1 isolates that single bit
            if (((a->arr[0] >> bit) & 1) == 0)
                pb(a, b);  // Bit is 0: push to B
            else
                ra(a, 1);  // Bit is 1: keep in A (rotate)
            i++;
        }
        // Push everything back from B to A
        while (b->size > 0)
            pa(a, b);
        bit++;
    }
}
```

### Complexity Analysis

| Aspect | Complexity | Explanation |
|--------|------------|-------------|
| **Time** | O(n × b) | n elements × b bits |
| **Space** | O(n) | Stack B can hold all elements |
| **Operations** | ~n × b × 2 | pb/ra per element per bit, plus pa's |

For n = 500: b ≈ 9 bits → ~9000 operations (well under 11500 limit!)

---

## 🔬 Small Input Optimization

### Why Optimize for Small Inputs?

Radix sort has overhead that makes it inefficient for tiny inputs. For 3 elements, radix might use 15+ operations, while an optimized solution uses at most 2!

### Sorting 3 Elements: sort_three()

With 3 elements, there are exactly **6 possible permutations**. I handle each optimally:

```
Permutation    Operations Needed    Moves
[1, 2, 3]  →  (already sorted)     0
[1, 3, 2]  →  sa, ra               2
[2, 1, 3]  →  sa                   1
[2, 3, 1]  →  rra                  1
[3, 1, 2]  →  ra                   1
[3, 2, 1]  →  sa, rra              2
```

**Maximum: 2 operations** (vs 15+ for radix sort!)

### Sorting 4-5 Elements: sort_small()

Strategy: **Push smallest elements to B, sort remaining 3, push back**

```
Example: [5, 3, 1, 4, 2]

Step 1: Find minimum (1), rotate to top, push to B
        ra, ra → [1, 4, 2, 5, 3]
        pb     → A:[4, 2, 5, 3] B:[1]

Step 2: Find minimum (2), rotate to top, push to B
        ra     → [2, 5, 3, 4]
        pb     → A:[5, 3, 4] B:[2, 1]

Step 3: Sort remaining 3 with sort_three()
        ra     → A:[3, 4, 5]

Step 4: Push back from B
        pa, pa → A:[1, 2, 3, 4, 5] ✓
```

### Rotation Optimization

When moving an element to the top, choose the shorter path:

```
Stack: [_, _, _, X, _, _]  (X at position 3, size 6)
       
Position 3 is in first half (3 <= 6/2 = 3)
→ Use ra (rotate forward): 3 operations

Stack: [_, _, _, _, X, _]  (X at position 4, size 6)

Position 4 is in second half (4 > 6/2 = 3)  
→ Use rra (rotate backward): 2 operations (6 - 4 = 2)
```

---

## 🏗️ Project Architecture

### Directory Structure

```
push_swap/
├── Makefile           # Build automation
├── push_swap.h        # Header file with declarations
├── README.md          # This documentation
├── srcs/              # Source files for core functionality
│   ├── main.c         # Entry point and flow control
│   ├── parse.c        # Input parsing and validation
│   ├── split.c        # String splitting utility
│   └── utils.c        # Helper functions
└── algo/              # Algorithm implementations
    ├── push.c         # Stack operations (sa, pa, pb, ra, rra)
    ├── sort.c         # Radix sort algorithm
    └── sort_small.c   # Optimized sorting for small inputs
```

### Module Responsibilities

| Module | Purpose | Key Functions |
|--------|---------|---------------|
| **main.c** | Program flow | `main()`, `sort_stack()` |
| **parse.c** | Input validation | `parse_args()`, `is_valid_number()` |
| **split.c** | String handling | `ft_split()`, `free_split()` |
| **utils.c** | Utilities | `error_exit()`, `is_sorted()`, `get_max_bits()` |
| **push.c** | Operations | `sa()`, `pa()`, `pb()`, `ra()`, `rra()` |
| **sort.c** | Main algorithm | `radix_sort()`, `index_stack()` |
| **sort_small.c** | Optimization | `sort_three()`, `sort_small()` |

### Data Flow

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   INPUT     │────▶│   PARSE     │────▶│  VALIDATE   │
│  (argv)     │     │ (split.c)   │     │ (parse.c)   │
└─────────────┘     └─────────────┘     └─────────────┘
                                               │
                                               ▼
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│   OUTPUT    │◀────│    SORT     │◀────│  STACK A    │
│ (operations)│     │(sort*.c)    │     │ (populated) │
└─────────────┘     └─────────────┘     └─────────────┘
```

---

## 🚀 Installation & Usage

### Prerequisites

- GCC compiler (or clang)
- Make build system
- Unix-like environment (Linux, macOS, WSL)

### Compilation

```bash
# Clone the repository
git clone https://github.com/yourusername/push_swap.git
cd push_swap

# Compile the program
make

# Clean object files
make clean

# Full clean (objects + executable)
make fclean

# Recompile from scratch
make re
```

### Basic Usage

```bash
# Sort a list of numbers (as separate arguments)
./push_swap 4 67 3 87 23

# Sort numbers (as a single quoted string)
./push_swap "4 67 3 87 23"

# Both formats produce the same output
```

### Advanced Usage

```bash
# Count the number of operations
./push_swap 4 67 3 87 23 | wc -l

# Generate and sort 100 random numbers
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l

# Verify sorting with checker (if available)
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG

# Test with edge cases
./push_swap 1                    # Single element (no output)
./push_swap 1 2 3 4 5            # Already sorted (no output)
./push_swap 2147483647 -2147483648  # INT_MAX and INT_MIN
```

### Input Formats Supported

| Format | Example | Notes |
|--------|---------|-------|
| Separate arguments | `./push_swap 3 2 1` | Most common |
| Single quoted string | `./push_swap "3 2 1"` | Useful for scripts |
| Mixed signs | `./push_swap -5 0 +3` | Positive sign optional |
| Large range | `./push_swap -2147483648 2147483647` | Full int range |

---

## 📊 Performance Analysis

### Operation Count Results

| Input Size | Average Ops | Worst Case | 42 Benchmark |
|------------|-------------|------------|--------------|
| 3 | 1-2 | 2 | ≤ 3 ✅ |
| 5 | 6-8 | 12 | ≤ 12 ✅ |
| 100 | ~1,084 | ~1,100 | < 1,500 ✅ |
| 500 | ~6,784 | ~7,000 | < 11,500 ✅ |

### Performance Visualization

```
Operations vs Input Size:

     │
11500│                                    ─── 42 Limit (500)
     │
 7000│                              ■
     │                        ■
 5000│                  ■
     │            ■
 3000│      ■
     │ ■
 1000│──────────────────────────────────── 42 Limit (100)
     │
     └────────────────────────────────────
       100   200   300   400   500   Input Size
```

### Why These Results?

**For 100 elements:**
- Bits needed: ⌈log₂(100)⌉ = 7 bits
- Operations per pass: ~200 (100 pb/ra + 100 pa)
- Total: ~7 × 200 = 1,400 theoretical max
- Actual: ~1,084 (some numbers need fewer bits)

**For 500 elements:**
- Bits needed: ⌈log₂(500)⌉ = 9 bits
- Operations per pass: ~1,000
- Total: ~9 × 1,000 = 9,000 theoretical max
- Actual: ~6,784 (optimization helps)

---

## 📖 Code Walkthrough

### Entry Point: main.c

```c
int main(int argc, char **argv)
{
    t_stack a;
    t_stack b;
    char    **split;

    // 1. Handle no arguments (not an error)
    if (argc < 2)
        return (0);
    
    // 2. Initialize to NULL for safe cleanup
    init_vars(&a, &b, &split);
    
    // 3. Parse and validate input
    if (!parse_args(argc, argv, &a, &split))
        error_exit(&a, &b, split);
    
    // 4. Already sorted? Exit early
    if (is_sorted(&a))
    {
        free_split(split);
        free_stacks(&a, NULL);
        return (0);
    }
    
    // 5. Allocate stack B
    b.arr = malloc(sizeof(int) * a.size);
    b.size = 0;
    if (!b.arr)
        error_exit(&a, &b, split);
    
    // 6. Sort and cleanup
    sort_stack(&a, &b);
    free_split(split);
    free_stacks(&a, &b);
    return (0);
}
```

### Input Parsing: parse.c

The parsing process validates:

1. **Format**: Must be valid number strings
2. **Range**: Must fit in 32-bit signed integer
3. **Uniqueness**: No duplicate values

```c
// Validation flow for each number
if (!is_valid_number(args[i]))      // Check format
    return (0);
num = ft_atol(args[i]);             // Convert to long
if (num > INT_MAX || num < INT_MIN) // Check overflow
    return (0);
if (has_duplicate(a, num, i))       // Check uniqueness
    return (0);
```

### Stack Operations: push.c

Each operation follows a pattern:

```c
void ra(t_stack *a, int print)
{
    int tmp;
    int i;

    // Guard clause: need at least 2 elements
    if (a->size < 2)
        return;
    
    // Save first element
    tmp = a->arr[0];
    
    // Shift all elements up
    i = 0;
    while (i < a->size - 1)
    {
        a->arr[i] = a->arr[i + 1];
        i++;
    }
    
    // Place saved element at end
    a->arr[a->size - 1] = tmp;
    
    // Print if requested
    if (print)
        ft_putstr("ra\n");
}
```

---

## ⚠️ Error Handling

### Invalid Input Cases

| Input | Error Reason |
|-------|--------------|
| `./push_swap abc` | Non-numeric argument |
| `./push_swap 1 2 1` | Duplicate values |
| `./push_swap 9999999999` | Exceeds INT_MAX |
| `./push_swap ""` | Empty string |
| `./push_swap "  "` | Only whitespace |
| `./push_swap 1 -` | Invalid format |
| `./push_swap ++1` | Invalid format |

### Error Output

All errors produce the same output:
```
Error
```
Written to **stderr** (file descriptor 2), not stdout.

### Why Uniform Error Messages?

- **Security**: Don't reveal what specifically failed
- **Simplicity**: Easier for automated testing
- **42 Requirement**: Subject specifies this behavior

---

## 💾 Memory Management

### Allocation Strategy

```
1. Parse Phase:
   - Split array (if single string input)
   - Stack A array

2. Sort Phase:
   - Stack B array
   - Temporary index array (in index_stack)

3. Cleanup Phase:
   - Free everything before exit
```

### Preventing Memory Leaks

```c
void error_exit(t_stack *a, t_stack *b, char **split)
{
    // Free in reverse order of allocation
    free_split(split);
    free_stacks(a, b);
    write(2, "Error\n", 6);
    exit(1);
}
```

### Safe Freeing Pattern

```c
void free_stacks(t_stack *a, t_stack *b)
{
    // Check pointer before accessing
    if (a && a->arr)
    {
        free(a->arr);
        a->arr = NULL;  // Prevent double-free
    }
    if (b && b->arr)
    {
        free(b->arr);
        b->arr = NULL;
    }
}
```

---

## 🧪 Testing

### Basic Tests

```bash
# Test sorting
./push_swap 3 2 1
# Expected: sa, rra (or equivalent)

# Test already sorted
./push_swap 1 2 3
# Expected: (no output)

# Test single element
./push_swap 42
# Expected: (no output)
```

### Error Tests

```bash
# Test duplicate
./push_swap 1 1
# Expected: Error

# Test non-number
./push_swap 1 abc 2
# Expected: Error

# Test overflow
./push_swap 9999999999999
# Expected: Error
```

### Performance Tests

```bash
# Test 100 random numbers (should be < 1500 operations)
ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l

# Test 500 random numbers (should be < 11500 operations)
ARG=$(shuf -i 1-10000 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l
```

### Automated Testing Script

```bash
#!/bin/bash
# test_push_swap.sh

echo "Testing push_swap..."

# Test 1: Basic sorting
result=$(./push_swap 3 2 1 | wc -l)
if [ $result -le 3 ]; then
    echo "✅ Basic sort: PASS ($result ops)"
else
    echo "❌ Basic sort: FAIL ($result ops)"
fi

# Test 2: 100 numbers
for i in {1..10}; do
    ARG=$(shuf -i 1-1000 -n 100 | tr '\n' ' ')
    result=$(./push_swap $ARG | wc -l)
    if [ $result -lt 1500 ]; then
        echo "✅ 100 numbers test $i: PASS ($result ops)"
    else
        echo "❌ 100 numbers test $i: FAIL ($result ops)"
    fi
done

echo "Testing complete!"
```

---

## 📚 What I Learned

### Technical Skills

1. **Algorithm Design**: Choosing the right algorithm for constraints
2. **Bit Manipulation**: Using shifts and masks for efficient operations
3. **Memory Management**: Proper allocation, tracking, and freeing
4. **Edge Case Handling**: Anticipating and handling special inputs
5. **Code Organization**: Modular design with clear responsibilities

### Problem-Solving Approach

1. **Understand the problem** before coding
2. **Research existing solutions** (radix sort, etc.)
3. **Start simple**, then optimize
4. **Test incrementally** with small inputs first
5. **Measure performance** to validate improvements

### Debugging Techniques

- Print stack state at each step (during development)
- Use valgrind for memory leak detection
- Test edge cases systematically
- Compare operation counts with theoretical limits

---

## 🔗 Resources

### Algorithm References

- [Radix Sort - GeeksforGeeks](https://www.geeksforgeeks.org/radix-sort/) - Comprehensive explanation of radix sort algorithm
- [Bit Manipulation Guide](https://www.hackerearth.com/practice/basic-programming/bit-manipulation/basics-of-bit-manipulation/tutorial/) - Understanding bitwise operations used in this project
- [Stack Data Structure](https://www.geeksforgeeks.org/stack-data-structure/) - Fundamentals of stack operations and implementation

### push_swap Specific Resources

- [Push_swap Tutorial by Jamie Dawson](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a) - Detailed walkthrough of push_swap strategies
- [42 Docs - push_swap](https://harm-smits.github.io/42docs/projects/push_swap) - Official 42 documentation and hints

### Tools for Testing

- [push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer) - Visualize your sorting algorithm in action
- [push_swap Tester](https://github.com/LeoFu9487/push_swap_tester) - Automated testing for operation count validation

### Official Documentation

- [42 Push_swap Subject PDF](https://github.com/42-subjects) - The official project requirements
- [The Norm v4](https://github.com/42School/norminette) - 42's coding standard that all code must follow

---

## 🤖 AI Usage Disclosure

In accordance with 42's policy on AI transparency, here is a description of how AI tools were used in this project:

### AI Tools Used

- **GitHub Copilot / Claude** - AI coding assistant

### Tasks Where AI Was Used

| Task | AI Involvement | Description |
|------|----------------|-------------|
| **Code Documentation** | ✅ Used | AI assisted in writing comprehensive comments and documentation for all source files, explaining the purpose of each function and the logic behind the implementation |
| **README Writing** | ✅ Used | AI helped structure and write this README file, including explanations of the algorithm, usage instructions, and technical documentation |
| **Code Review** | ✅ Used | AI was used to review code for potential improvements and to ensure clarity |

### Tasks Where AI Was NOT Used

| Task | AI Involvement | Description |
|------|----------------|-------------|
| **Algorithm Design** | ❌ Not Used | The choice of radix sort and the optimization strategies were researched and decided independently |
| **Core Implementation** | ❌ Not Used | All sorting algorithms, stack operations, and parsing logic were written by the student |
| **Debugging** | ❌ Not Used | All bugs were identified and fixed through manual testing and debugging |
| **Understanding Concepts** | ❌ Not Used | Understanding of stacks, radix sort, and bit manipulation came from studying the referenced resources |

### Why This Approach?

The AI was used as a **documentation tool** rather than a code-writing tool. The goal was to:

1. **Improve code readability** - Professional comments help others (and future me) understand the code
2. **Create comprehensive documentation** - A detailed README helps peers, evaluators, and recruiters understand the project
3. **Maintain learning integrity** - The actual problem-solving and coding was done without AI assistance

This approach ensures that the learning objectives of the project were met while producing professional-quality documentation.

---

## 🏆 Conclusion

Push_swap is more than just a sorting exercise—it's a deep dive into algorithmic thinking. The constraint of limited operations forces you to truly understand data structures rather than relying on built-in functions.

The key insights from this project:

1. **Constraints breed creativity**: Limited operations led to discovering radix sort
2. **Optimization matters**: Small input optimization drastically improves results
3. **Understanding beats memorization**: Knowing *why* radix sort works is crucial
4. **Testing is essential**: Edge cases reveal bugs that normal inputs hide

I hope this documentation helps others understand both the project and the underlying computer science concepts!

---

<div align="center">
  <p><strong>Made with ❤️ at 42 Amman</strong></p>
  <p><em>mhaizan - 2026</em></p>
</div>
