# URL Hash Table with Open Addressing
[![C++11+](https://img.shields.io![License](https://img.shields.io/badge/License-Academic-greens](https://img.shields.io)

A high-performance C++ hash table implementation for storing and searching URLs using open addressing collision resolution.

## Overview
This project implements a configurable hash table system that benchmarks Division vs. Universal hashing combined with Linear vs. Quadratic probing to determine optimal configurations for URL storage and retrieval.


### Problem Statement
Efficiently storing and retrieving URL strings presents several key challenges:
- Non-linear collision patterns with different hash functions
- Clustering behavior varies significantly between probing methods
- Performance degradation at high load factors (α > 0.7)
- Trade-offs between memory usage and lookup speed
- This project addresses these challenges through a configurable system that compares multiple hash function and probing strategies.

### Architecture
#### Hash Table Design: Four Configurations
- The system provides four distinct configurations combining two hash functions and two probing methods:
- Division Hashing + Linear Probing - Simplest, fast for low load factors
- Division Hashing + Quadratic Probing - Better clustering reduction
- Universal Hashing + Linear Probing - Better distribution, still simple
- Universal Hashing + Quadratic Probing - Best overall performance

### Hash Functions
#### Division Hashing
- Method: Polynomial rolling hash with base 31
  - Formula: hash = (hash * 31 + char) % tableSize
  - Advantages: Fast computation, works with any table size
  - Disadvantages: Potential clustering with certain data patterns

#### Universal Hashing
- Method: Horner's rule with base-256 encoding
  - Formula: hₐ,ᵦ(x) = ((a * #(x) + b) mod k*Hsize) / k
  - Parameters: a=31415, b=27183, k=1000003
  - Advantages: Uniform distribution, collision-resistant, theoretical guarantees
  - Disadvantages: Slightly higher computation cost

#### Probing Methods
- Linear Probing
  - Formula: h(k,i) = (h(k) + i) mod m
  - Best for: Low load factors (α < 0.5)
  - Advantages: Cache-friendly, simple implementation
  - Disadvantages: Primary clustering at high loads
- Quadratic Probing
  - Formula: h(k,i) = (h(k) + i²) mod m
  - Best for: Medium-high load factors (0.5 < α < 0.9)
  - Advantages: Reduces clustering, better distribution
  - Disadvantages: Slightly more complex computation

## Features
- Dual Hash Functions - Compare Division and Universal hashing approaches
- Dual Probing Methods - Implement Linear and Quadratic probing strategies
- Real-time Performance Tracking - Measure comparisons, execution time, and statistics
- Load Factor Analysis - Track performance across different load factors
- Interactive Interface - User-friendly command-based system

#### Performance Results
Test Configuration
```text
URLs Tested: 1,000+ diverse URLs

Table Sizes: 101, 1009, 10007

Load Factors: 0.3, 0.5, 0.7, 0.9
```
#### Key Results
Configuration	Avg Comparisons	Max Comparisons	Performance Ratio
```text
Division + Linear	1.85	12	1.56
Division + Quadratic	1.72	8	1.45
Universal + Linear	1.65	10	1.38
Universal + Quadratic	1.48	7	1.21
Performance by Load Factor
Load Factor	Probing Method	Avg Error	Status
0.3	Linear	±1.1	Excellent
0.5	Linear	±1.8	Good
0.7	Quadratic	±2.4	Acceptable
0.9	Quadratic	±3.8	Degraded
```
## Quick Start
### Prerequisites
- C++11 or higher
- g++, clang, or MSVC compiler
- Windows, Linux, or macOS

### Installation
- Step 1: Clone Repository
```text
bash
git clone https://github.com/yourusername/URLHashTable.git
cd URLHashTable
```
- Step 2: Compile
  - Linux/macOS (Makefile):
```text
bash
make
Windows (MSVC):

text
build.bat
```
  - Manual Compilation:
```text
bash
g++ -std=c++11 -Iinclude -o url_hash src/*.cpp
Step 3: Run
bash
```
- Windows
```text
cl.exe /EHsc /Iinclude /Fe:url_hash.exe src\HashEntry.cpp src\HashFunctions.cpp src\Statistics.cpp src\URLHashTable.cpp src\main.cpp
.\url_hash.exe
```
- Linux/macOS
```text
./url_hash
```
### Commands
- Command	Purpose	Example
```text
hashSearch,<URL>	Search for URL	hashSearch,http://www.google.com/
hashDelete,<URL>	Remove URL	hashDelete,http://www.google.com/
hashDisplay	Show all entries	hashDisplay
hashStats	Performance metrics	hashStats
hashReset	Reset statistics	hashReset
InsertionContinue	Add more URLs	InsertionContinue
End	Exit program	End
```
### Example Session
```text
Enter the hash table size: 101

Select hash function:
1. Division Hashing
2. Universal Hashing
Enter choice (1 or 2): 1
Using Division Hashing

Select probing method:
1. Linear Probing
2. Quadratic Probing
Enter choice (1 or 2): 1
Using Linear Probing

Enter URLs (type 'InsertionEnd' to finish)
http://www.google.com/
https://www.github.com/
InsertionEnd

hashStats

Hash Function: Division Hashing
Probing Method: Linear Probing
Table Size: 101
Number of Elements: 2
Load Factor: 0.0198
Total Queries: 1
Average Comparisons per Query: 1.0000
Maximum Comparisons: 1
Average Time: 0.00000045 seconds
Performance Ratio: 1.00

End
```
## Project Structure
```text
URLHashTable/
├── include/
│   ├── HashTypes.h           # Enumerations and type definitions
│   ├── HashEntry.h           # Entry structure (URL + status)
│   ├── HashFunctions.h       # Hash function declarations
│   ├── Statistics.h          # Performance tracking class
│   └── URLHashTable.h        # Main hash table class
├── src/
│   ├── main.cpp              # Interactive user interface
│   ├── HashEntry.cpp         # Entry implementation
│   ├── HashFunctions.cpp     # Hash algorithm implementations
│   ├── Statistics.cpp        # Statistics tracking
│   └── URLHashTable.cpp      # Hash table operations
├── Makefile                  # Linux/macOS build script
├── build.bat                 # Windows build script
└── README.md                 # This file
```
## Key Design Decisions
#### Why Multiple Configurations?
- Each configuration serves a specific purpose:
  - Division + Linear: Fastest for low load factors
  - Division + Quadratic: Reduces clustering without additional overhead
  - Universal + Linear: Better distribution while maintaining simplicity
  - Universal + Quadratic: Optimal performance across all scenarios

#### Why Universal Hashing?
- Provides theoretically uniform distribution
- Collision-resistant with random parameters
- Optimal for worst-case performance analysis
- Demonstrates superior performance ratio

### Constraints & Limitations
- Fixed Table Size	Cannot grow dynamically	Pre-allocate larger table
- No Rehashing	Performance degrades at α > 0.9	Resize manually before insertion
- Memory Usage	Grows linearly with table size	Use reasonable sizes (101-10007)

### Technical Stack
- Component	Library/Tool	Version
- Language	C++	C++11+
- Compiler	g++/clang/MSVC	Latest
- Build System	Makefile/Batch	Standard
- Data Structures	std::vector, std::string	STL
- Timing	clock()	ctime
- Results & Learning Outcomes
- Performance Achievements
- Performance Ratio < 1.3 for optimal configurations

### Technical Learning
- Comparative analysis of hash functions
- Open addressing vs. chaining trade-offs
- Performance measurement and statistical analysis
- Multi-strategy implementation

### Future Improvements
- Dynamic rehashing on demand
- Double hashing support
- Performance visualization
- Automated benchmark suite
- Web-based results dashboard

### References
- Cormen, Leiserson, Rivest, Stein - Introduction to Algorithms (3rd ed.)
- Knuth, Donald E. - The Art of Computer Programming, Vol. 3: Sorting and Searching
- Carter & Wegman (1979) - Universal Classes of Hash Functions


### Author

**Brian Bao Hoang**
- [GitHub](https://github.com/baoblank25)
- [LinkedIn](https://www.linkedin.com/in/brian-hoang-420664288/)

Arizona State University | CSE310

