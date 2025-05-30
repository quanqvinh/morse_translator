# Morse Code Translator

A command-line utility for translating between text and Morse code, with support for file input/output and detailed conversion statistics.

## Features

- Convert text to Morse code and vice versa
- Support for all standard Morse code characters:
  - Alphabet (a-z, A-Z)
  - Numbers (0-9)
  - Special characters (., , ? ' " ! / ( ) & : ; = + - \_ $ @)
  - Common briefs (understood, error, invitation to transmit, wait, end of work, starting signal)
- File-based translation with input/output file support
- Detailed conversion statistics
- Error handling and reporting
- Colored console output for better readability

## Usage

```bash
morse <inputfile> <outputfile> [-t | -m] [-c]
morse [-t | -m] [-c] <inputfile> <outputfile>
morse -h
```

### Parameters

- `<inputfile>`: Path to an existing input file
- `<outputfile>`: Path to the output file (will be created if it doesn't exist)
- `-h`: Display help message and save to readme.txt
- `-t`: Force input file to be treated as text and output as Morse code
- `-m`: Force input file to be treated as Morse code and output as text
- `-c`: Enable statistics mode (shows conversion details)

### Notes

- If a file path contains spaces, enclose it in double quotes
- The program automatically detects if the input file is Morse code or text
- When using `-c` option, statistics include:
  - Input and output file names
  - Conversion completion time (YYYY-MM-DD HH:MM:SS)
  - Conversion duration
  - Word count in input file
  - Number of successfully converted words
  - Number of words with errors
  - Total character count
  - Number of successfully converted characters
  - Number of characters that couldn't be converted
  - Detailed error messages

### Error Handling

The program handles various error cases:

- Missing arguments
- Unrecognized commands
- Invalid argument order
- File access issues
- Invalid Morse code format
- Unrecognized characters

Error messages are displayed in red text for better visibility.

## Examples

1. Basic translation (auto-detect):

```bash
morse input.txt output.txt
```

2. Force text to Morse code:

```bash
morse -t input.txt output.txt
```

3. Force Morse code to text with statistics:

```bash
morse -m -c input.txt output.txt
```

4. Get help:

```bash
morse -h
```

## Technical Details

- Written in C++
- Uses standard C++ libraries (iostream, fstream, map, string)
- Supports Windows console color output
- Handles file I/O with proper error checking
- Uses maps for efficient Morse code lookups
- Supports both Windows and Unix-style line endings

## Error Codes

- ERROR 07: Invalid Morse code format
- ERROR 08: Unrecognized character in text

## License

This project is open source and available for personal and educational use.
