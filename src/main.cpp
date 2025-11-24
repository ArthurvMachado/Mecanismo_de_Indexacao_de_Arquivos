#include "commandLineInterface/commandLineInterface.hpp"

int main(int argc, char* argv[]) {
    CommandLineInterface cli;
    return cli.run(argc, argv);
}