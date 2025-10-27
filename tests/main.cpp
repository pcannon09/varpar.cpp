#include <iostream>

#include "../inc/varparse.cpp/VP_Parse.hpp"

int main(int argc, char **argv)
{
	vp::Parser parse("main-parse",
			(argc >= 2 ? argv[1] : "./tests/zone/file.varpar"), ".varpar"
			);

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
