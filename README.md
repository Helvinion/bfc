# bfc
This is a useless, stupid, absurd, probably ineficiant, Brainfuck compiler. It can output :
- C
- NASM code for x86_64
- BF, without the comments
- BF, without the comments but with indentation.

Usage: `bfc [--output | -o <output_file>] [--mode | -m <mode>] [--datasize | -d <size>] [input_file]`
- `output_file` : the file to write the output of bfc. Default is standard output
- `mode`        : the mode of the compiler : print, prettyprint, c, amd64. Default is amd64
- `size`        : the size of the memory to allocate. Default is 30000 bytes
- `input_file`  : the file to read from. Default is standard input
