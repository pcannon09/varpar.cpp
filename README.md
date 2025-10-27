# VarPar - Variable Parser

`VarPar` (Variable Parser) is a extremely lightweight **C++17+ configuration file parser** that provides simple, strict key value parsing for flat text configuration files

---

## Features

* **Strict Parsing:** Ensures each key is uniquely defined and every line contains a valid `key = value` pair

* **Automatic Validation:** Checks file existence and verifies the correct file extension before parsing

* **Informative Error Handling:** Reports precise error messages and line numbers for duplicate or malformed entries

* **Minimal Dependencies:** Uses only standard C++17 libraries

* **Lightweight Runtime Status:** Parser state (constructed / error) is tracked through `ParserStatus` for safe checks

---

## Core Components

### `vp::Parser`

Main parsing class responsible for reading and interpreting configuration files.

#### Constructor

```cpp
vp::Parser(const std::string& _id, const std::string& _file, const std::string& _extension = ".varpar");
```

**Parameters**

* `_id` — Unique identifier string for this parser instance.
* `_file` — File path to the config file.
* `_extension` — Required file extension (default as: `.varpar`).

**Behavior**

* Validates that `_file` exists.
* Confirms that `_file` has the required `_extension`.
* If any checks fail, the parser sets its internal error status and logs the issue to `std::cerr`.

---

### `ParserReturn`

Struct returned by the parser after execution.

```cpp
struct ParserReturn {
    std::map<std::string, std::string> config;  // Parsed key value pairs
    std::vector<std::string> output;            // Raw messages and errors
    bool success;                               // Parsing result flag
};
```

---

### `ParserStatus`

Represents the parser’s internal construction status.

```cpp
struct ParserStatus {
    bool constructed;       // Whether parser was constructed successfully
    std::string error;      // Any error message generated during setup
};
```

---

### Public Methods

#### `ParserReturn parse()`

Executes parsing and returns a structured result.
If successful, `ParserReturn::success` is `true` and `config` contains parsed pairs.

#### `std::string getVal(const std::string& _key) const`

Retrieves a parsed value by key.
Returns an empty string if the key is missing.

#### `ParserStatus checkStatus() const`

Returns the internal construction status for validation before parsing.

#### `std::string getID() const`

Returns the parser’s unique identifier.

---

## Parsing Rules

* Lines starting with `;` or empty lines are ignored.
* Lines must follow the format:
```
key = value
```
* Whitespace around keys and values is trimmed automatically.
* Duplicate keys produce an immediate error, halting parsing.

---

## Example File (`config.varpar`)

```ini
; Example config file
hello_world = "Bye..."
random = "aa"
randomText = "aab"
```

---

## Example Usage

```cpp
#include <iostream>
#include <varparse/VP_Parse.hpp>

int main()
{
	vp::Parser parse("main-parse", "/path/to/file.varpar");

	if (auto status = parse.checkStatus() ; !status.constructed)
	{
		std::cerr << "Failed to construct: " << parse.getID() << "\n";
		std::cerr << status.error << "\n";

		std::exit(1);
	}

	std::cout << "Output:\n";

	vp::ParserReturn parsed = parse.parse();

	for (const auto &x : parsed.output)
	{ std::cout << x << "\n"; }

	if (!parsed.success)
	{
		std::cerr << "[ ! ] Exiting due to an error\n";

		std::exit(1);
	}

	for (const auto &[k, v] : parsed.config)
	{ std::cout << k << " = " << v << "\n"; }

	std::cout << "Value of `hello_world`: " << parse.getVal("hello_world") << "\n";

	return 0;
}
```

---

## Error Example

Given this invalid input:

```ini
hello_world = "Bye..."
hello_world = "Bye...a"
```

Output:

```
ERR: LINE: 2
Duplicate member : hello_world = "Bye...a"
```

Due to the fact that there are two keys with the same name

---

## Supported Compilers

* GCC >= 7.0
* Clang >= 6.0
* MSVC >= 19.14 (Visual Studio 2017 15.7+)

Requires **C++17** or newer

