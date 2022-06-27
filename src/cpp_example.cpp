#include <iostream>

#include <cassert>
#include "tspp/parser.hpp"
#include "tspp/languages/cpp.hpp"

using namespace std::literals;

int main() {
	// Create a parser and set its language.
	auto cpp = ts::cpp::language();
	ts::Parser parser(cpp);

	// Create the parser explicitly then set the parser's language (C++ in this case).
	// parser.reset(ts_parser_new());
	// parser.set_language(ts::language_cpp(););

	// Build a syntax tree based on source code stored in a string.
	std::string source_code = "#include <iostream>\n[[depreciated]] int main() { auto print = []{std::cout << \"Hello World\" << std::endl;}; print(); }";
	auto tree = parser.parse_string(source_code);

	// Get the root node of the syntax tree.
	auto root_node = tree.root_node();

	// Get some child nodes.
	auto preprocessorNode = root_node.named_child(0);
	auto stringNode = preprocessorNode.named_child(0);

	// Check that the nodes have the expected types.
	assert(root_node.type() == "translation_unit"sv);
	assert(root_node.symbol() == ts::cpp::Symbols::translation_unit);
	assert(preprocessorNode.type() == "preproc_include"sv);
	assert(preprocessorNode.symbol() == ts::cpp::Symbols::preproc_include);
	assert(stringNode.type() == "system_lib_string"sv);
	assert(stringNode.symbol() == ts::cpp::Symbols::system_lib_string);

	// Check that the nodes have the expected child counts.
	assert(root_node.child_count() == 2);
	assert(preprocessorNode.child_count() == 3);
	assert(preprocessorNode.named_child_count() == 1);
	assert(stringNode.child_count() == 0);

	assert(*stringNode.field_name() == "path"sv);

	auto [start, end] = stringNode.byte_range();
	for(size_t i = start; i < end; i++)
		std::cout << source_code[i];
	std::cout << " - " << stringNode.symbol() << std::endl;

	// Print the syntax tree as an S-expression.
	std::cout << root_node.string() << std::endl;

	return 0;
}