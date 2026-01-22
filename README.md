*This project has been created as part of the 42 curriculum by mhaizan.*

# Push_Swap

## Description

Push_swap is an algorithmic project that challenges you to sort a stack of integers using a limited set of operations. The goal is to sort stack A in ascending order using the minimum number of moves possible.

This implementation uses the **Radix Sort algorithm** adapted for two stacks. Radix sort works by sorting numbers bit by bit, from the least significant bit to the most significant bit, achieving consistent performance regardless of the initial order.

### Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap the first 2 elements of stack A |
| `pa` | Push the top element of stack B onto stack A |
| `pb` | Push the top element of stack A onto stack B |
| `ra` | Rotate stack A (first element becomes last) |
| `rra` | Reverse rotate stack A (last element becomes first) |

## Instructions

### Compilation

```bash
make        # Compile the program
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

### Execution

```bash
./push_swap <list of integers>
```

**Examples:**
```bash
./push_swap 3 2 1           # Sort 3 numbers
./push_swap 5 4 3 2 1       # Sort 5 numbers
./push_swap $(shuf -i 1-100 -n 100 | tr '\n' ' ')  # Sort 100 random numbers
```

**Count operations:**
```bash
./push_swap 3 2 1 | wc -l   # Count number of operations
```

### Error Handling

The program outputs `Error` to stderr for:
- Non-integer arguments
- Duplicate numbers
- Numbers exceeding INT_MAX/INT_MIN

## Performance

| Input Size | Operations | 42 Limit |
|------------|------------|----------|
| 3 numbers | ≤ 3 | - |
| 5 numbers | ≤ 12 | - |
| 100 numbers | ~1084 | < 1100 ✓ |
| 500 numbers | ~6784 | < 8500 ✓ |

## Algorithm: Radix Sort

1. **Indexing**: Convert values to positions (0 to n-1) based on their relative order
2. **Bit-by-bit sorting**: For each bit position (LSB to MSB):
   - If bit is 0 → push to stack B (`pb`)
   - If bit is 1 → rotate stack A (`ra`)
   - Push all elements back from B to A (`pa`)
3. After processing all bits, stack A is sorted

## Resources

### Documentation
- [Push_swap Tutorial](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
- [Radix Sort Explained](https://www.geeksforgeeks.org/radix-sort/)
- [42 Push_swap Subject](https://github.com/42-subjects)