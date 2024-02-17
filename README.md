# Custom Regex Engine

This project is a custom implementation of a regex (regular expression) engine in C++. It is designed to replicate some of the functionality of standard regex libraries, with a focus on pattern matching and searching within text. This implementation includes a tokenizer, parser, and a matching engine, following the basic principles and structure of regex processing.

## Overview

The regex engine supports basic regex functionalities including:

- Literal character matching
- Quantifiers (`*` for zero or more, `+` for one or more)
- Character classes (a-z, A-Z)
- Grouping and alternation (`(`, `)`, `+`)
- Dot (`.`) for any single character
- Escaped characters (e.g., `\\`, `{n}` for exact number of repetitions)
- Space character recognition

## Syntax

The engine uses a simplified regex syntax as follows:

- `<regex>` ::= `<term>` [`<escaped_char>`] [`<regex>`]
- `<term>` ::= `<string>` [`*` | `{` `<digit>` `}`]
              | `(` `<term>` `+` `<term>` `)`
              | `.` [`{` `<digit>` `}` | `*`]
- `<string>` ::= `<char>` { `<char>` }
- `<char>` ::= a-z | A-Z | space
- `<escaped_char>` ::= `\\` ( "I" | "O" `{` `<digit>` `}` )
- `<digit>` ::= [0-9]+


## Usage

To use this custom regex engine, compile the source code with a C++ compiler and run the executable with a regex pattern and a text string as arguments. For example:

g++ main.cpp -o regexEngine
./regexEngine "<your_regex_pattern>" "<your_text>"

Replace `<your_regex_pattern>` with the regex pattern you want to match and `<your_text>` with the text you want to search.

