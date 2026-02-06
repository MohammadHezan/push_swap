# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammad-hezan <mohammad-hezan@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 21:32:00 by mhezan            #+#    #+#              #
#    Updated: 2026/02/06 13:00:02 by mohammad-he      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# PUSH_SWAP - MAKEFILE
# ==============================================================================
#
# This Makefile compiles the push_swap program, a sorting algorithm
# implementation that sorts integers using two stacks with minimal operations.
#
# Usage:
#   make        - Build the program
#   make clean  - Remove object files
#   make fclean - Remove object files and executable
#   make re     - Rebuild from scratch
#
# ==============================================================================

# ======================== PROGRAM NAME =======================================
# The final executable name that will be generated
NAME = push_swap

# ======================== COMPILER SETTINGS ===================================
# CC      - The C compiler to use (cc is the system default C compiler)
# CFLAGS  - Compiler flags:
#   -Wall   : Enable all standard warnings
#   -Wextra : Enable extra warnings not covered by -Wall
#   -Werror : Treat all warnings as errors (required by 42 norm)
#   -I srcs : Add srcs directory to include path for header files
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

# ======================== SOURCE FILES ========================================
# List of all source files organized by functionality:
#
# srcs/main.c    - Program entry point, initialization, and flow control
# srcs/parse.c   - Command-line argument parsing and validation
# srcs/split.c   - String splitting utility (for quoted argument handling)
# srcs/utils.c   - Helper functions (output, memory management, error handling)
# algo/push.c    - Stack operation implementations (sa, pa, pb, ra, rra)
# algo/sort.c    - Main sorting algorithm (Radix Sort for large inputs)
# algo/sort_small.c - Optimized sorting for small inputs (2-5 elements)
SRCS = srcs/main.c \
       srcs/parse.c \
       srcs/split.c \
       srcs/utils.c \
       algo/push.c \
       algo/sort.c \
       algo/sort_small.c

# ======================== OBJECT FILES ========================================
# Automatically generate object file names from source files
# Example: srcs/main.c becomes srcs/main.o
OBJS = $(SRCS:.c=.o)

# ======================== BUILD RULES =========================================

# Default target - builds the executable
# The 'all' target depends on $(NAME), which triggers the linking step
all: $(NAME)

# Linking rule - creates the final executable
# $(CC)      - Use the configured compiler
# $(CFLAGS)  - Apply compiler flags
# $(OBJS)    - Link all object files
# -o $(NAME) - Output the executable with the specified name
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation rule - compiles .c files to .o files
# Pattern rule: %.o depends on %.c and the header file
# $< - The first prerequisite (the .c file)
# $@ - The target (the .o file)
# -c - Compile only, do not link
%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

# ======================== CLEANING RULES ======================================

# Remove object files only
# rm -f - Force remove without prompting, ignore if files don't exist
clean:
	rm -f $(OBJS)

# Full clean - remove both object files and the executable
# Depends on 'clean' to first remove object files
fclean: clean
	rm -f $(NAME)

# Rebuild from scratch
# First runs fclean, then runs all
re: fclean all

# ======================== PHONY TARGETS =======================================
# .PHONY declares targets that are not actual files
# This prevents conflicts if files named 'all', 'clean', etc. exist
.PHONY: all clean fclean re
