#include <iostream>
#include <fstream>
#include <cassert>

#include "Lexer.hpp"
#include "Program.hpp"
#include "ParseError.hpp"

void parse_cmd(int argc, char** argv, std::string& input, std::string& output, std::string& memory_size, std::string& mode)
{
    std::string* current_arg = &input;
    bool         error_cmdline = false;
    
    for (int i = 1; i < argc && !error_cmdline; i++)
    {
        std::string arg = argv[i];

        if (arg[0] == '-')
        {
            // It is expected to be in "normal" mode. Otherwise, it's an error.
            error_cmdline = (current_arg != &input);
            if (!error_cmdline)
            {
                if (arg == "-o" || arg == "--output")
                    current_arg = &output;
                else if (arg == "-m" || arg == "--mode")
                    current_arg = &mode;
                else if (arg == "-d" || arg == "--datasize")
                    current_arg = &memory_size;
                else
                    error_cmdline = true;
            }
        }
        else
        {
            // It is expected that the current destination is empty.
            // Otherwise the same parameter were given twice
            error_cmdline = (!current_arg->empty());
            if (!error_cmdline)
            {
                current_arg->assign(arg);
                current_arg = &input;
            }
        }
    }

    if (error_cmdline)
    {
        std::cerr << "Usage: bfc [--output | -o <output_file>] [--mode | -m <mode>] [--datasize | -d <size>] [input_file]" << std::endl;
        std::cerr << "output_file : the file to write the output of bfc. Default is standard output" << std::endl;
        std::cerr << "mode        : the mode of the compiler : print, prettyprint, c, amd64. Default is amd64" << std::endl;
        std::cerr << "size        : the size of the memory to allocate. Default is 30000 bytes" << std::endl;
        std::cerr << "input_file  : the file to read from. Default is standard input" << std::endl;
        exit(1);
    }
}

std::ofstream output_stream;

std::istream& get_input(const std::string& path)
{
    static std::ifstream input_stream;

    assert(!input_stream.is_open());

    if (path.empty())
        return std::cin;

    input_stream.open(path);

    if (!input_stream.is_open())
    {
        std::cerr << "Cannot open " << path << " for reading" << std::endl;
        exit(2);
    }

    return input_stream;
}

std::ostream& get_output(const std::string& path)
{
    static std::ofstream output_stream;

    assert(!output_stream.is_open());

    if (path.empty())
        return std::cout;

    output_stream.open(path);

    if (!output_stream.is_open())
    {
        std::cerr << "Cannot open " << path << " for writing" << std::endl;
        exit(2);
    }

    return output_stream;
}

int main(int argc, char** argv)
{
    std::string  input = "";
    std::string  output = "";
    std::string  memory_size = "";
    std::string  mode = "";

    parse_cmd(argc, argv, input, output, memory_size, mode);

    BF::Lexer lexer(get_input(input));

    BF::AST::Program program(memory_size);
    try
    {
        program.parse(lexer);
    }
    catch (BF::ParseError& error)
    {
        std::cerr << "Parse error: " << error.what() << std::endl;
        exit(2);
    }

    if (mode == "print")
        program.print(get_output(output));
    else if (mode == "prettyprint")
        program.prettyprint(get_output(output));
    else if (mode == "c")
        program.print_c(get_output(output));
    else if (mode == "amd64" || mode.empty())
        program.print_amd64(get_output(output));
    else
    {
        std::cerr << "Unknown mode: " << mode << ". Please use print, prettyprint, c, ou amd64." << std::endl;
        exit(3);
    }
}
