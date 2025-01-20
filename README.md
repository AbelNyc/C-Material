### **📌 Custom Memory Allocator - README.md**  

## **1️⃣ What You Learned in This Project**
Building a **Custom Memory Allocator** helped reinforce **core memory management concepts** in C++. You gained hands-on experience in:

### **📌 Understanding Memory Layout**
✅ **Stack vs. Heap Allocation**  
- **Stack**: Fast, managed automatically, stores local variables and pointers.  
- **Heap**: Manually allocated, stores dynamically allocated memory.  

✅ **How Pointers Work**  
- `x` (pointer) is stored **on the stack**.  
- `*x` (value) is stored **on the heap**.  
- `&x` gives the **stack address** where `x` is stored.  

✅ **Pointer Arithmetic**  
- `memoryPool + (i * blockSize)` → Moves the pointer by `blockSize` bytes to find the correct memory block.  
- `ptr - memoryPool` → Computes the byte offset to identify which block a pointer belongs to.

---

### **📌 Implementing a Custom Allocator**
✅ **Creating a Fixed-Size Memory Pool**  
- Instead of allocating/deallocating memory on-demand, we **preallocate a large block** (`memoryPool`).  
- **Divided into fixed-size blocks** for fast allocation.  

✅ **Efficient Allocation (`allocate()`)**  
- Scans for the first **free block**, marks it as used, and returns its pointer.  
- Uses `std::vector<bool>` to track allocated blocks.  

✅ **Efficient Deallocation (`deallocate()`)**  
- Computes the **block index** of a pointer using pointer arithmetic.  
- Marks the block as free.  
- Prevents **double-free errors** and **out-of-bounds access**.  

✅ **RAII (Resource Acquisition Is Initialization)**  
- Memory is allocated **in the constructor** and freed **in the destructor** to prevent leaks.

✅ **Error Handling**  
- Throws `std::bad_alloc()` if no free blocks are available.  
- Prevents **invalid deallocation** (e.g., deallocating memory outside the pool).  

---

### **📌 Advanced Memory Management Concepts**
✅ **Custom Memory Management**  
- Instead of relying on `new/delete`, we **manually manage memory**, just like in low-level systems programming.  

✅ **Memory Safety**  
- Prevents **use-after-free**, **double free**, and **invalid access**.  
- Ensures correct **boundary checks** during allocation and deallocation.  

✅ **Smart Pointer Integration**  
- `std::unique_ptr<void, Deleter>` can be used to manage allocated memory safely.

---

### **📌 Code Walkthrough**
#### **1️⃣ CustomAllocator.h**
```cpp
class CustomAllocator {
private:
    std::size_t blockSize;
    std::size_t numBlocks;
    std::vector<bool> used;
    char* memoryPool;

public:
    CustomAllocator(std::size_t numBlocks, std::size_t blockSize);
    void* allocate();
    void deallocate(void* ptr);
    ~CustomAllocator();
};
```

#### **2️⃣ Allocation**
```cpp
void* allocate() {
    for (std::size_t i = 0; i < numBlocks; ++i) {
        if (!used[i]) {  
            used[i] = true;
            return memoryPool + (i * blockSize);
        }
    }
    throw std::bad_alloc();
}
```

#### **3️⃣ Deallocation**
```cpp
void deallocate(void* ptr) {
    std::ptrdiff_t index = (static_cast<char*>(ptr) - memoryPool) / blockSize;
    if (index >= 0 && index < static_cast<std::ptrdiff_t>(numBlocks) && used[index]) {
        used[index] = false;
    } else {
        std::cerr << "Invalid deallocation!" << std::endl;
    }
}
```

#### **4️⃣ Destructor to Free Memory**
```cpp
~CustomAllocator() {
    delete[] memoryPool;
}
```

---

## **2️⃣ Why Is This Important?**
🔹 **You now understand how memory allocators work at a low level.**  
🔹 **This is the foundation for writing custom memory managers in real-world applications.**  
🔹 **Critical for performance-sensitive applications like databases, game engines, and financial systems.**  

---

## **3️⃣ Next Steps (Advanced Features)**
🚀 Want to extend the project? Here are **some advanced features you can add**:

1️⃣ **Thread Safety**  
   - Use `std::mutex` to make the allocator safe in multi-threaded environments.  

2️⃣ **Custom Object Placement**  
   - Implement **placement new** to construct objects inside allocated memory.  

3️⃣ **Support for Variable-Sized Allocations**  
   - Instead of fixed-size blocks, allow **variable-sized allocations** like `malloc()`.  

4️⃣ **Benchmark Performance**  
   - Compare your allocator against `malloc()` and `std::allocator<>`.  

---

## **🎯 Summary of What You Learned**
✔ **Memory layout: stack vs. heap**  
✔ **Pointers, dereferencing, pointer arithmetic**  
✔ **Manual memory management (allocators)**  
✔ **Efficient allocation & deallocation strategies**  
✔ **RAII, smart pointers, and memory safety**  
✔ **Advanced memory management (placement new, multi-threading, benchmarking)**  

---

## **📌 Final Thoughts**
💡 **This project gives you a deep understanding of memory management in C++!**  
💡 **Essential for low-level systems, high-performance applications, and game engines.**  
💡 **Next step: Build a more advanced memory pool with multi-threading!**  

---
