# Unhinged

**Language**: C++  
**Date**: Mar 2022  
**Repository**: [github.com/awest25/Unhinged](https://github.com/awest25/Unhinged)

## Overview
Unhinged is a command-line user matching application that efficiently pairs individuals based on shared attributes. With its advanced data structures, the app was designed to handle a large user base, exemplified by testing on 100,000 sample users.

## Key Features
- **Radix Tree Implementation**: Custom-built radix tree (binary search tree) data structure to map strings to various data types.
- **Performance Optimization**: Achieved a 10x improvement in user matching performance using a blend of binary search trees and C++ Standard Library data structures.
- **User Profile Matching**: Attributes like jobs, hobbies, and traits are used to find the best match between users.

## User Profile Example

```
Abdullah Fowler
AbFow2483@charter.net
13
job,architect
hobby,canyoneering
hobby,slacklining
hobby,painting
trait,sly
trait,incurious
trait,excitable
```

## How It Works
Upon registration, users provide various attributes like job, hobbies, and traits. Unhinged then efficiently matches users based on shared attributes utilizing advanced data structures.

## Getting Started
1. Clone the repo: `git clone https://github.com/awest25/Unhinged.git`
2. Navigate to directory: `cd Unhinged`
3. Compile with GCC and run.
4. Respond to the prompt with a name in the sample user database.
5. You will be matched with users that have similar attributes.
