# Effective Modern C++ Notes

## Item 1: Understand Template Type Deduction
Template type deduction forms the foundation of modern C++. When the compiler sees `template<typename T> void f(ParamType param); f(expr);`, it deduces two types: one for `T` and one for `ParamType`.

There are three main cases depending on `ParamType`:

### Case 1: `ParamType` is a Reference or Pointer (but not a Universal Reference)
* Example: `template<typename T> void f(T& param);` or `void f(const T& param);`
* **Rule:** The reference-ness of `expr` is ignored. `const`-ness is preserved.
* **Systems Implication:** If you pass a `const int`, `T` becomes `const int` to ensure you can't mutate it inside the function.

### Case 2: `ParamType` is a Universal Reference (`T&&`)
* Example: `template<typename T> void f(T&& param);`
* **Rule:** If `expr` is an lvalue (a named variable), both `T` and `ParamType` are deduced as lvalue references (`T&`). This is the *only* time `T` is deduced as a reference.
* If `expr` is an rvalue (a temporary, like `27`), normal Case 1 rules apply.

### Case 3: `ParamType` is Pass-By-Value (`T`)
* Example: `template<typename T> void f(T param);`
* **Rule:** `param` will be a brand new copy. Therefore, the reference-ness of `expr` is ignored, AND the `const`/`volatile` qualifiers are ignored.
* **Systems Implication:** Even if you pass a `const int&`, `T` is deduced as just `int`, because mutating the new copy doesn't affect the original `const` variable.

### Array and Function Decay
* If you pass an array by value to a template `T`, it decays into a pointer (e.g., `int*`).
* **The Trick:** If you pass an array by reference to `T&`, it is deduced as the actual array type with its size preserved! (e.g., `int (&)[13]`).

---

## Item 2: Understand `auto` Type Deduction
`auto` type deduction is identical to template type deduction. `auto` essentially plays the role of `T`.

* `auto x = 27;` (Case 3: pass-by-value)
* `const auto& cx = x;` (Case 1: reference)
* `auto&& uref = x;` (Case 2: universal reference)

### The Only Exception: Braced Initializers
There is exactly one rule where `auto` deduction differs from template deduction: **Braced Initialization**.

* `auto x = { 11, 23, 9 };` 
  * `auto` successfully deduces `x` as a `std::initializer_list<int>`.
* `template<typename T> void f(T param); f({11, 23, 9});`
  * Template deduction **fails**. It cannot deduce `std::initializer_list` from a braced initializer. You would have to explicitly declare `T` as `std::initializer_list<T>`.

---

## Retention Drills

### Question 1: Const and Auto
```cpp
const int max_connections = 100;
auto my_connections = max_connections;
my_connections = 50; 
```
**Does this code compile? Why or why not?**
* **Answer:** It perfectly compiles. `my_connections` is deduced using Case 3 (Pass-By-Value). In pass-by-value deduction, reference and `const` qualifiers are completely stripped. `my_connections` becomes a brand new, independent, mutable `int`.

### Question 2: The Systems Performance Trap
```cpp
const std::vector<int>& getSystemsTelemetry();
auto data = getSystemsTelemetry();
```
**What is the exact type deduced for `data`? Did we make a performance mistake?**
* **Answer:** Because plain `auto` uses pass-by-value deduction rules, the `const` and `&` are stripped. `data` is deduced as a plain `std::vector<int>`. We just triggered a massive, unintentional deep copy of the entire vector onto the heap. 
* **The Fix:** Change the code to `const auto& data = getSystemsTelemetry();` to force Reference Deduction (Case 1), which preserves the reference and constness, completely avoiding the memory allocation.
* **The Template Equivalent:**
  To see exactly why `auto` caused the copy, map it to its template equivalent:
  ```cpp
  // Plain auto (The Bug):
  template<typename T> void f(T param); // Case 3: Pass-By-Value
  
  // const auto& (The Fix):
  template<typename T> void f(const T& param); // Case 1: Reference
  ```
  Remember that `auto` matches `T`, NOT `ParamType`. By typing `const auto&`, you explicitly change `ParamType` to `const T&`, forcing the compiler to use Case 1 rules and perfectly preserving your memory constraints.
