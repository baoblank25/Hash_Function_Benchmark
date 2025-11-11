# URL Hash Table with Open Addressing

> [!NOTE]
> A high-performance C++ hash table implementation for storing and searching URLs using open addressing collision resolution with advanced hash functions.

## Table of Contents
- [Overview](#overview)
- [Hash Functions](#hash-functions)
- [Features](#features)
- [Quick Start](#quick-start)
- [Performance Results](#performance-results)
- [Project Structure](#project-structure)
- [Assignment Requirements](#assignment-requirements-fulfilled)
- [References](#references)

---

## Overview

This project implements a configurable hash table system that benchmarks **Bitwise Mixing**, **Polynomial Rolling**, and **Universal hashing** combined with **Linear** vs. **Quadratic** probing to determine optimal configurations for URL storage and retrieval across multiple table sizes and load factors.

### Problem Statement

Efficiently storing and retrieving URL strings presents several key challenges:

- Non-linear collision patterns with different hash functions
- Clustering behavior varies significantly between probing methods
- Performance degradation at high load factors (α > 0.7)
- Trade-offs between memory usage and lookup speed
- Need for consistent performance across different table sizes

> [!IMPORTANT]
> This project addresses these challenges through automated batch testing across at least 10 different table sizes with the same dataset.

### Architecture

#### Hash Table Design: Six Configurations

The system provides **six distinct configurations** combining three hash functions and two probing methods:

| Configuration | Hash Function | Probing Method | Best For |
|--------------|---------------|----------------|----------|
| 1 | Bitwise Mixing | Linear | α < 0.5, High performance |
| 2 | Bitwise Mixing | Quadratic | α < 0.8, Production use |
| 3 | Polynomial Rolling | Linear | α < 0.6, String optimization |
| 4 | Polynomial Rolling | Quadratic | α < 0.8, Balanced performance |
| 5 | Universal | Linear | α < 0.5, Theoretical guarantees |
| 6 | Universal | Quadratic | α < 0.9, Worst-case optimized |

---

## Hash Functions

### 1. Bitwise Mixing Hash (MurmurHash-style)

**Method**: Bit-level operations with XOR and multiplication
```
hash ^= hash >> 16;
hash *= 0x7feb352d;
hash ^= hash >> 15;
hash *= 0x846ca68b;
hash ^= hash >> 16;
```

- **Advantages**: Extremely fast, excellent distribution, works with any table size
- **Use Case**: High-performance applications, real-time systems

### 2. Polynomial Rolling Hash (DJB2-style)

**Method**: Polynomial rolling hash with prime base 31

**Formula**: `h(s) = (s₀×31^(n-1) + s₁×31^(n-2) + ... + s_(n-1)) mod m`

- **Advantages**: String-optimized, simple, proven track record
- **Use Case**: String-heavy applications, similar to Java's `String.hashCode()`

### 3. Universal Hashing

**Method**: Horner's rule with base-256 encoding

**Formula**: `h_{a,b}(x) = ((a * #(x) + b) mod k*Hsize) / k`

**Parameters**: `a=31415`, `b=27183`, `k=1000003`

- **Advantages**: Provable uniform distribution, collision reduction
- **Use Case**: Security-sensitive applications, worst-case performance requirements

### Probing Methods

#### Linear Probing

**Formula**: `h(k,i) = (h(k) + i) mod m`

- **Best for**: Low to medium load factors (α < 0.6)
- Cache-friendly, simple implementation
- Primary clustering at high loads

#### Quadratic Probing

**Formula**: `h(k,i) = (h(k) + i²) mod m`

- **Best for**: Medium-high load factors (0.5 < α < 0.9)
- Reduces clustering significantly
- Slightly more complex computation

---

## Features

- **Three Advanced Hash Functions** - Bitwise Mixing, Polynomial Rolling, Universal
- **Two Probing Strategies** - Linear and Quadratic probing
- **CSV File Input** - Batch load URLs from file with configurable table size
- **Batch Testing Mode** - Automatically test 10+ different table sizes with same data
- **Real-time Performance Tracking** - Measure comparisons, execution time, and statistics
- **Load Factor Analysis** - Compare performance across multiple load factors (0.33 to 0.95)
- **Interactive Interface** - User-friendly command-based system
- **"HIT" Detection** - Reports when URLs already exist in table

---

## Quick Start

### Prerequisites

- C++11 or higher
- g++, clang, or MSVC compiler
- Windows, Linux, or macOS

### Installation

**Step 1: Clone Repository**
```
git clone https://github.com/baoblank25/URLHashTable.git
cd URLHashTable
```

**Step 2: Compile**

<details>
<summary>Linux/macOS (Makefile)</summary>
```
make
```
</details>

<details>
<summary>Windows (MSVC)</summary>
```
cl.exe /EHsc /Iinclude /Fe:url_hash.exe src\HashEntry.cpp src\HashFunctions.cpp src\Statistics.cpp src\URLHashTable.cpp src\main.cpp
```
</details>

<details>
<summary>Manual Compilation</summary>
```
g++ -std=c++11 -Iinclude -o url_hash src/*.cpp
```
</details>

**Step 3: Prepare CSV Input File**

Create `urls.csv` with format:
```
1016
http://www.google.com
https://www.github.com
http://stackoverflow.com
https://www.youtube.com
```

> [!TIP]
> Line 1 must be the suggested table size

**Step 4: Run**
```
./url_hash # Linux/macOS
url_hash.exe # Windows
```

### Available Commands

| Command | Purpose | Example |
|---------|---------|---------|
| `hashSearch,<URL>` | Search for URL | `hashSearch,http://www.google.com` |
| `hashDelete,<URL>` | Remove URL | `hashDelete,http://www.google.com` |
| `hashDisplay` | Show all entries | `hashDisplay` |
| `hashStats` | Performance metrics | `hashStats` |
| `hashReset` | Reset statistics | `hashReset` |
| `End` | Exit program | `End` |

### Example Session

**Single Table Size Mode:**
```
Enter CSV filename: urls.csv
Loaded 1013 URLs from file.

Select mode:

Single table size test (interactive)

Multiple table size test (batch mode - at least 10 sizes)
Enter choice (1 or 2): 1

Select hash function:

Bitwise Mixing Hash (MurmurHash-style)

Polynomial Rolling Hash (DJB2-style)

Universal Hashing
Enter choice (1, 2, or 3): 1
Using Bitwise Mixing Hash

Select probing method:

Linear Probing

Quadratic Probing
Enter choice (1 or 2): 2
Using Quadratic Probing
```

---

## Performance Results

### Test Configuration

```
URLs Tested: 1,013 diverse URLs
Table Sizes: 10+ sizes from 1,023 to 3,039
Load Factors: 0.33, 0.50, 0.67, 0.75, 0.80, 0.90, 0.95
```

### Key Findings

| Hash Function | Probing | Load Factor | Avg Comparisons | Status |
|---------------|---------|-------------|-----------------|--------|
| Bitwise Mixing | Quadratic | 0.33 | 1.02 | Excellent |
| Polynomial Rolling | Quadratic | 0.50 | 1.18 | Excellent |
| Universal | Quadratic | 0.67 | 1.54 | Good |
| Bitwise Mixing | Linear | 0.75 | 2.31 | Acceptable |
| Universal | Quadratic | 0.90 | 8.42 | Degraded |
| Any | Linear | 0.95 | 35+ | Critical |

### Performance by Configuration

> [!TIP]
> **Best Overall**: Bitwise Mixing + Quadratic Probing
> - Fastest computation
> - Excellent distribution
> - Best performance ratio across all load factors

**Best Theoretical**: Universal + Quadratic Probing
- Provable guarantees
- Worst-case optimized
- Security-focused applications

**Best for Strings**: Polynomial Rolling + Quadratic Probing
- String-optimized algorithm
- Proven track record (Java, Python)
- Simple and reliable

---

## Project Structure
```
URLHashTable/
├── include/
│ ├── HashTypes.h # Enumerations (BITWISE_HASH, POLYNOMIAL_HASH, UNIVERSAL_HASH)
│ ├── HashEntry.h # Entry structure (URL + SlotStatus)
│ ├── HashFunctions.h # Three hash function declarations
│ ├── Statistics.h # Performance tracking class
│ └── URLHashTable.h # Main hash table class
├── src/
│ ├── main.cpp # CSV loader + batch testing + interactive UI
│ ├── HashEntry.cpp # Entry implementation
│ ├── HashFunctions.cpp # Bitwise, Polynomial, Universal implementations
│ ├── Statistics.cpp # Average/max comparisons, timing
│ └── URLHashTable.cpp # Open addressing operations
├── Makefile # Linux/macOS build script
├── build.bat # Windows build script
└── README.md # This file
```

---

## Key Design Decisions

### Why Three Hash Functions?

Each serves a specific purpose:

1. **Bitwise Mixing**: Production performance (fastest)
2. **Polynomial Rolling**: String optimization (proven)
3. **Universal**: Theoretical guarantees (secure)

### Why CSV Input?

- **Reproducibility**: Same dataset across tests
- **Batch Testing**: Load once, test multiple configurations
- **Real-world Simulation**: Mirrors production data ingestion

### Why Multiple Table Sizes?

- **Load Factor Analysis**: Compare performance across α from 0.33 to 0.95
- **Assignment Requirement**: Test at least 10 different sizes
- **Performance Profiling**: Identify optimal size for given dataset

---

## Constraints & Limitations

| Constraint | Impact | Mitigation |
|------------|--------|------------|
| Fixed Table Size | Cannot grow dynamically | Pre-allocate based on expected data |
| No Rehashing | Performance degrades α > 0.9 | Use batch mode to find optimal size |
| Open Addressing Only | Memory grows linearly | Choose appropriate initial size |
| High Load Factor Issues | Clustering increases dramatically | Keep α < 0.75 for production |

> [!WARNING]
> Performance degrades dramatically when load factor exceeds 0.9. Always maintain α < 0.75 for production environments.

---

## Assignment Requirements Fulfilled

- **Open addressing only** (no chaining)  
- **At least two hash functions** (implemented three)  
- **Universal hashing included** (as specified)  
- **Linear vs. Quadratic probing** (both implemented)  
- **At least ten table sizes** (batch mode with 10+ sizes)  
- **Same data, different sizes** (load once, test multiple)  
- **Three required metrics**:
   - Average comparisons per query
   - Maximum comparisons per query
   - Average running time per query

---

## Technical Stack

| Component | Technology | Version |
|-----------|-----------|---------|
| Language | C++ | C++11+ |
| Compiler | g++/clang/MSVC | Latest |
| Build System | Makefile/Batch | Standard |
| Data Structures | `std::vector`, `std::string` | STL |
| Timing | `clock()` | `<ctime>` |
| File I/O | `ifstream` | `<fstream>` |

---

## Learning Outcomes

### Technical Skills Developed

- Advanced hash function implementation (bitwise operations)
- Open addressing collision resolution strategies
- Performance measurement and statistical analysis
- Batch testing and data analysis automation
- CSV parsing and file I/O handling

### Key Insights

1. **Load factor matters more than hash function** at extreme values (α > 0.9)
2. **Bitwise mixing outperforms** traditional methods in practice
3. **Quadratic probing essential** for load factors above 0.6
4. **Batch testing reveals** performance cliffs not visible in single tests

---

## Future Improvements

- Dynamic rehashing when load factor exceeds threshold
- Double hashing as third probing option
- Performance visualization (graphs/charts)
- Automated benchmark report generation
- Multi-threaded batch testing
- Additional hash functions (FNV-1a, CityHash, xxHash)
- Web-based results dashboard

---

## References

1. **Cormen, Leiserson, Rivest, Stein** - *Introduction to Algorithms* (4th ed.) - Universal hashing theory
2. **Knuth, Donald E.** - *The Art of Computer Programming, Vol. 3* - Hash table analysis
3. **Carter & Wegman (1979)** - *Universal Classes of Hash Functions* - Theoretical foundation
4. **Austin Appleby** - *MurmurHash* - Bitwise mixing techniques
5. **Bernstein, Daniel J.** - *DJB2 Hash* - Polynomial rolling hash

---

## Author

**Brian Bao Hoang**  

[![GitHub](https://img.shields.io/badge/GitHub-baoblank25-181717?logo=github)](https://github.com/baoblank25)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Brian%20Hoang-0A66C2?logo=linkedin)](https://www.linkedin.com/in/brian-hoang-420664288/)

---

<sub>*Last Updated: November 2025*</sub>