# 🔑 HashTables – C++ Implementations of Hash Table Data Structures

This project offers a deep dive into various **hash table** implementations in C++, providing an interactive platform to understand, test, and compare their functionalities and performance.

---

## 🧩 Project Highlights

- 🗄️ **Implemented Hash Table Variants**:
  - **Separate Chaining**: Handles collisions using linked lists.
  - **Open Addressing**: Resolves collisions through probing techniques.
- 🛠️ **Core Operations**:
  - `insert(key, value)`: Adds a key-value pair to the hash table.
  - `remove(key)`: Deletes the key-value pair associated with the specified key.
  - `search(key)`: Retrieves the value associated with the given key.
- ⏱️ **Performance Analysis**: Measures execution time for each operation to evaluate efficiency.
- 📊 **Theoretical Validation**: Ensures that observed time complexities align with theoretical expectations.
- 🧰 **Object-Oriented Design Principles**:
  - **Encapsulation**: Bundles data with methods operating on that data.
  - **Inheritance**: Promotes code reusability by deriving new classes from existing ones.
  - **Polymorphism**: Allows entities to be represented in multiple forms.
  - **Abstraction**: Simplifies complex systems by modeling classes appropriate to the problem.

---

## 📂 Directory Structure

- **`include/`**: Contains header files defining interfaces and data structures.
- **`src/`**: Houses the main source code implementing hash table variants.
- **`tests/`** *(optional)*: Comprises test cases to validate the correctness of implementations.
- **`benchmarks/`** *(optional)*: Contains scripts or programs to measure performance metrics.
- **`main.cpp`**: Serves as the entry point, integrating all components and facilitating user interaction.

---

## 🧪 How It Works

Upon executing the application, users are presented with an interactive console interface that allows them to:

- Select a specific hash table implementation.
- Perform fundamental operations such as insertion, deletion, and search.
- Observe real-time feedback and results directly in the terminal.
- Analyze performance metrics to compare different implementations.

---

## 📈 Performance Benchmarking

The project conducts thorough measurements of execution times for each operation across different hash table variants. This empirical data aids in understanding the practical efficiency of each implementation and determining the most suitable one for various scenarios.

---

## ▶️ Getting Started

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/wiktoriamiich/HashTables.git
   cd HashTables

2. **Compile the Program**:

   ```bash
   g++ src/main.cpp -o hashtables

3. **Run the Application**:

   ```bash
   ./hashtables

