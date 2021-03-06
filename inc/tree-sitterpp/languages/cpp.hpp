#ifndef __TREE_SITTERPP_LANGUAGES_CPP_HPP__
#define __TREE_SITTERPP_LANGUAGES_CPP_HPP__

#include "../language.hpp"

namespace TreeSitter::cpp {
	namespace detail { extern "C" {
		// Declare the `tree_sitter_cpp` function, which is
		// implemented by the `tree-sitter-cpp` library.
		extern TSLanguage* tree_sitter_cpp();
	} }

	// Returns a static reference to the C++ language
	inline Language& language() {
		static Language cpp;
		static bool first = true;

		if(first){
			first = false;
			cpp = detail::tree_sitter_cpp();
		}

		return cpp;
	}

	// Enum with all of the symbols in the language
	enum Symbols : TSSymbol {
		identifier = 1,
		aux_preproc_include_token1 = 2,
		anon_LF = 3,
		aux_preproc_def_token1 = 4,
		anon_LPAREN = 5,
		anon_DOT_DOT_DOT = 6,
		anon_COMMA = 7,
		anon_RPAREN = 8,
		aux_preproc_if_token1 = 9,
		aux_preproc_if_token2 = 10,
		aux_preproc_ifdef_token1 = 11,
		aux_preproc_ifdef_token2 = 12,
		aux_preproc_else_token1 = 13,
		aux_preproc_elif_token1 = 14,
		preproc_directive = 15,
		preproc_arg = 16,
		anon_LPAREN2 = 17,
		anon_defined = 18,
		anon_BANG = 19,
		anon_TILDE = 20,
		anon_DASH = 21,
		anon_PLUS = 22,
		anon_STAR = 23,
		anon_SLASH = 24,
		anon_PERCENT = 25,
		anon_PIPE_PIPE = 26,
		anon_AMP_AMP = 27,
		anon_PIPE = 28,
		anon_CARET = 29,
		anon_AMP = 30,
		anon_EQ_EQ = 31,
		anon_BANG_EQ = 32,
		anon_GT = 33,
		anon_GT_EQ = 34,
		anon_LT_EQ = 35,
		anon_LT = 36,
		anon_LT_LT = 37,
		anon_GT_GT = 38,
		anon_SEMI = 39,
		anon_typedef = 40,
		anon_extern = 41,
		anon___attribute__ = 42,
		anon_COLON_COLON = 43,
		anon_LBRACK_LBRACK = 44,
		anon_RBRACK_RBRACK = 45,
		anon___declspec = 46,
		anon___based = 47,
		anon___cdecl = 48,
		anon___clrcall = 49,
		anon___stdcall = 50,
		anon___fastcall = 51,
		anon___thiscall = 52,
		anon___vectorcall = 53,
		ms_restrict_modifier = 54,
		ms_unsigned_ptr_modifier = 55,
		ms_signed_ptr_modifier = 56,
		anon__unaligned = 57,
		anon___unaligned = 58,
		anon_LBRACE = 59,
		anon_RBRACE = 60,
		anon_LBRACK = 61,
		anon_RBRACK = 62,
		anon_EQ = 63,
		anon_static = 64,
		anon_register = 65,
		anon_inline = 66,
		anon_thread_local = 67,
		anon_const = 68,
		anon_volatile = 69,
		anon_restrict = 70,
		anon__Atomic = 71,
		anon_mutable = 72,
		anon_constexpr = 73,
		anon_constinit = 74,
		anon_consteval = 75,
		anon_signed = 76,
		anon_unsigned = 77,
		anon_long = 78,
		anon_short = 79,
		primitive_type = 80,
		anon_enum = 81,
		anon_class = 82,
		anon_struct = 83,
		anon_union = 84,
		anon_COLON = 85,
		anon_if = 86,
		anon_else = 87,
		anon_switch = 88,
		anon_case = 89,
		anon_default = 90,
		anon_while = 91,
		anon_do = 92,
		anon_for = 93,
		anon_return = 94,
		anon_break = 95,
		anon_continue = 96,
		anon_goto = 97,
		anon_QMARK = 98,
		anon_STAR_EQ = 99,
		anon_SLASH_EQ = 100,
		anon_PERCENT_EQ = 101,
		anon_PLUS_EQ = 102,
		anon_DASH_EQ = 103,
		anon_LT_LT_EQ = 104,
		anon_GT_GT_EQ = 105,
		anon_AMP_EQ = 106,
		anon_CARET_EQ = 107,
		anon_PIPE_EQ = 108,
		anon_LT_EQ_GT = 109,
		anon_DASH_DASH = 110,
		anon_PLUS_PLUS = 111,
		anon_sizeof = 112,
		anon_DOT = 113,
		anon_DASH_GT = 114,
		number_literal = 115,
		anon_L_SQUOTE = 116,
		anon_u_SQUOTE = 117,
		anon_U_SQUOTE = 118,
		anon_u8_SQUOTE = 119,
		anon_SQUOTE = 120,
		aux_char_literal_token1 = 121,
		anon_L_DQUOTE = 122,
		anon_u_DQUOTE = 123,
		anon_U_DQUOTE = 124,
		anon_u8_DQUOTE = 125,
		anon_DQUOTE = 126,
		aux_string_literal_token1 = 127,
		escape_sequence = 128,
		system_lib_string = 129,
		true_ = 130,
		false_ = 131,
		null = 132,
		comment = 133,
		auto_ = 134,
		anon_decltype = 135,
		anon_final = 136,
		anon_override = 137,
		anon_virtual = 138,
		anon_explicit = 139,
		anon_public = 140,
		anon_private = 141,
		anon_protected = 142,
		anon_typename = 143,
		anon_template = 144,
		anon_GT2 = 145,
		anon_operator = 146,
		anon_delete = 147,
		anon_friend = 148,
		anon_noexcept = 149,
		anon_throw = 150,
		anon_namespace = 151,
		anon_using = 152,
		anon_static_assert = 153,
		anon_concept = 154,
		anon_co_return = 155,
		anon_co_yield = 156,
		anon_try = 157,
		anon_catch = 158,
		anon_co_await = 159,
		anon_new = 160,
		anon_requires = 161,
		anon_DOT_STAR = 162,
		anon_DASH_GT_STAR = 163,
		anon_LPAREN_RPAREN = 164,
		anon_LBRACK_RBRACK = 165,
		anon_DQUOTE_DQUOTE = 166,
		this_ = 167,
		nullptr_ = 168,
		literal_suffix = 169,
		raw_string_literal = 170,
		translation_unit = 171,
		preproc_include = 172,
		preproc_def = 173,
		preproc_function_def = 174,
		preproc_params = 175,
		preproc_call = 176,
		preproc_if = 177,
		preproc_ifdef = 178,
		preproc_else = 179,
		preproc_elif = 180,
		preproc_if_in_field_declaration_list = 181,
		preproc_ifdef_in_field_declaration_list = 182,
		preproc_else_in_field_declaration_list = 183,
		preproc_elif_in_field_declaration_list = 184,
		_preproc_expression = 185,
		preproc_parenthesized_expression = 186,
		preproc_defined = 187,
		preproc_unary_expression = 188,
		preproc_call_expression = 189,
		preproc_argument_list = 190,
		preproc_binary_expression = 191,
		function_definition = 192,
		declaration = 193,
		type_definition = 194,
		_declaration_modifiers = 195,
		_declaration_specifiers = 196,
		linkage_specification = 197,
		attribute_specifier = 198,
		attribute = 199,
		attribute_declaration = 200,
		ms_declspec_modifier = 201,
		ms_based_modifier = 202,
		ms_call_modifier = 203,
		ms_unaligned_ptr_modifier = 204,
		ms_pointer_modifier = 205,
		declaration_list = 206,
		_declarator = 207,
		_field_declarator = 208,
		_type_declarator = 209,
		_abstract_declarator = 210,
		parenthesized_declarator = 211,
		parenthesized_field_declarator = 212,
		parenthesized_type_declarator = 213,
		abstract_parenthesized_declarator = 214,
		attributed_declarator = 215,
		attributed_field_declarator = 216,
		attributed_type_declarator = 217,
		pointer_declarator = 218,
		pointer_field_declarator = 219,
		pointer_type_declarator = 220,
		abstract_pointer_declarator = 221,
		function_declarator = 222,
		function_field_declarator = 223,
		function_type_declarator = 224,
		abstract_function_declarator = 225,
		array_declarator = 226,
		array_field_declarator = 227,
		array_type_declarator = 228,
		abstract_array_declarator = 229,
		init_declarator = 230,
		compound_statement = 231,
		storage_class_specifier = 232,
		type_qualifier = 233,
		_type_specifier = 234,
		sized_type_specifier = 235,
		enum_specifier = 236,
		enumerator_list = 237,
		struct_specifier = 238,
		union_specifier = 239,
		field_declaration_list = 240,
		_field_declaration_list_item = 241,
		field_declaration = 242,
		bitfield_clause = 243,
		enumerator = 244,
		parameter_list = 245,
		parameter_declaration = 246,
		attributed_statement = 247,
		attributed_non_case_statement = 248,
		labeled_statement = 249,
		expression_statement = 250,
		if_statement = 251,
		switch_statement = 252,
		case_statement = 253,
		while_statement = 254,
		do_statement = 255,
		for_statement = 256,
		return_statement = 257,
		break_statement = 258,
		continue_statement = 259,
		goto_statement = 260,
		_expression = 261,
		comma_expression = 262,
		conditional_expression = 263,
		assignment_expression = 264,
		pointer_expression = 265,
		unary_expression = 266,
		binary_expression = 267,
		update_expression = 268,
		cast_expression = 269,
		type_descriptor = 270,
		sizeof_expression = 271,
		subscript_expression = 272,
		call_expression = 273,
		argument_list = 274,
		field_expression = 275,
		compound_literal_expression = 276,
		parenthesized_expression = 277,
		initializer_list = 278,
		initializer_pair = 279,
		subscript_designator = 280,
		field_designator = 281,
		char_literal = 282,
		concatenated_string = 283,
		string_literal = 284,
		_empty_declaration = 285,
		placeholder_type_specifier = 286,
		decltype_auto = 287,
		decltype_ = 288,
		class_specifier = 289,
		_class_name = 290,
		virtual_specifier = 291,
		virtual_function_specifier = 292,
		explicit_function_specifier = 293,
		base_class_clause = 294,
		_enum_base_clause = 295,
		dependent_type = 296,
		template_declaration = 297,
		template_instantiation = 298,
		template_parameter_list = 299,
		type_parameter_declaration = 300,
		variadic_type_parameter_declaration = 301,
		optional_type_parameter_declaration = 302,
		template_template_parameter_declaration = 303,
		optional_parameter_declaration = 304,
		variadic_parameter_declaration = 305,
		variadic_declarator = 306,
		variadic_reference_declarator = 307,
		operator_cast = 308,
		field_initializer_list = 309,
		field_initializer = 310,
		inline_method_definition = 311,
		_constructor_specifiers = 312,
		operator_cast_definition = 313,
		operator_cast_declaration = 314,
		constructor_or_destructor_definition = 315,
		constructor_or_destructor_declaration = 316,
		default_method_clause = 317,
		delete_method_clause = 318,
		friend_declaration = 319,
		access_specifier = 320,
		reference_declarator = 321,
		reference_field_declarator = 322,
		abstract_reference_declarator = 323,
		structured_binding_declarator = 324,
		ref_qualifier = 325,
		trailing_return_type = 326,
		noexcept_ = 327,
		throw_specifier = 328,
		template_type = 329,
		template_method = 330,
		template_function = 331,
		template_argument_list = 332,
		namespace_definition = 333,
		namespace_alias_definition = 334,
		namespace_definition_name = 335,
		using_declaration = 336,
		alias_declaration = 337,
		static_assert_declaration = 338,
		concept_definition = 339,
		condition_clause = 340,
		condition_declaration = 341,
		for_range_loop = 342,
		co_return_statement = 343,
		co_yield_statement = 344,
		throw_statement = 345,
		try_statement = 346,
		catch_clause = 347,
		co_await_expression = 348,
		new_expression = 349,
		new_declarator = 350,
		delete_expression = 351,
		type_requirement = 352,
		compound_requirement = 353,
		_requirement = 354,
		requirement_seq = 355,
		constraint_conjunction = 356,
		constraint_disjunction = 357,
		_requirement_clause_constraint = 358,
		requires_clause = 359,
		requires_parameter_list = 360,
		requires_expression = 361,
		lambda_expression = 362,
		lambda_capture_specifier = 363,
		lambda_default_capture = 364,
		_fold_operator = 365,
		_binary_fold_operator = 366,
		_unary_left_fold = 367,
		_unary_right_fold = 368,
		_binary_fold = 369,
		fold_expression = 370,
		parameter_pack_expansion = 371,
		type_parameter_pack_expansion = 372,
		destructor_name = 373,
		dependent_identifier = 374,
		dependent_field_identifier = 375,
		dependent_type_identifier = 376,
		_scope_resolution = 377,
		qualified_field_identifier = 378,
		qualified_identifier = 379,
		qualified_type_identifier = 380,
		qualified_operator_cast_identifier = 381,
		operator_name = 382,
		user_defined_literal = 383,
		aux_translation_unit_repeat1 = 384,
		aux_preproc_params_repeat1 = 385,
		aux_preproc_if_in_field_declaration_list_repeat1 = 386,
		aux_preproc_argument_list_repeat1 = 387,
		aux_declaration_repeat1 = 388,
		aux_type_definition_repeat1 = 389,
		aux_type_definition_repeat2 = 390,
		aux__declaration_specifiers_repeat1 = 391,
		aux_attribute_declaration_repeat1 = 392,
		aux_attributed_declarator_repeat1 = 393,
		aux_pointer_declarator_repeat1 = 394,
		aux_function_declarator_repeat1 = 395,
		aux_function_declarator_repeat2 = 396,
		aux_abstract_function_declarator_repeat1 = 397,
		aux_sized_type_specifier_repeat1 = 398,
		aux_enumerator_list_repeat1 = 399,
		aux_field_declaration_repeat1 = 400,
		aux_parameter_list_repeat1 = 401,
		aux_case_statement_repeat1 = 402,
		aux_argument_list_repeat1 = 403,
		aux_initializer_list_repeat1 = 404,
		aux_initializer_pair_repeat1 = 405,
		aux_concatenated_string_repeat1 = 406,
		aux_string_literal_repeat1 = 407,
		aux_base_class_clause_repeat1 = 408,
		aux_template_parameter_list_repeat1 = 409,
		aux_field_initializer_list_repeat1 = 410,
		aux_operator_cast_definition_repeat1 = 411,
		aux_structured_binding_declarator_repeat1 = 412,
		aux_throw_specifier_repeat1 = 413,
		aux_template_argument_list_repeat1 = 414,
		aux_try_statement_repeat1 = 415,
		aux_requirement_seq_repeat1 = 416,
		aux_requires_parameter_list_repeat1 = 417,
		aux_lambda_capture_specifier_repeat1 = 418,
		alias_field_identifier = 419,
		alias_namespace_identifier = 420,
		alias_simple_requirement = 421,
		alias_statement_identifier = 422,
		alias_type_identifier = 423,
	};
}

#endif // __TREE_SITTERPP_LANGUAGES_CPP_HPP__