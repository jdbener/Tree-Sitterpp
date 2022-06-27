#ifndef __TREE_SITTERPP_PARSER_HPP__
#define __TREE_SITTERPP_PARSER_HPP__

#include "helpers.hpp"
#include "tree.hpp"
#include <cstdio>

namespace TreeSitter {

	struct Parser : detail::UniqueHandle<TSParser> {
		Parser() : detail::UniqueHandle<TSParser>(ts_parser_new()) {}
		Parser(TSParser* parser) : detail::UniqueHandle<TSParser>(parser) { }
		explicit inline Parser(const TSLanguage* lang) : Parser() { set_language(lang); }
		using detail::UniqueHandle<TSParser>::UniqueHandle;
		using detail::UniqueHandle<TSParser>::operator=;

		operator TSParser*() { return get(); }
		operator const TSParser*() const { return get(); }

		/**
		 * Set the language that the parser should use for parsing.
		 *
		 * Returns a boolean indicating whether or not the language was successfully
		 * assigned. True means assignment succeeded. False means there was a version
		 * mismatch: the language was generated with an incompatible version of the
		 * Tree-sitter CLI. Check the language's version using `ts_language_version`
		 * and compare it to this library's `TREE_SITTER_LANGUAGE_VERSION` and
		 * `TREE_SITTER_MIN_COMPATIBLE_LANGUAGE_VERSION` constants.
		 */
		bool set_language(const TSLanguage* language) { return ts_parser_set_language(*this, language); }

		/**
		 * Get the parser's current language.
		 */
		const TSLanguage* language() const { return ts_parser_language(*this); }
		const TSLanguage* get_language() const { return language(); }

		/**
		 * Set the ranges of text that the parser should include when parsing.
		 *
		 * By default, the parser will always include entire documents. This function
		 * allows you to parse only a* portion* of a document but still return a syntax
		 * tree whose ranges match up with the document as a whole. You can also pass
		 * multiple disjoint ranges.
		 *
		 * The second and third parameters specify the location and length of an array
		 * of ranges. The parser does* not* take ownership of these ranges; it copies
		 * the data, so it doesn't matter how these ranges are allocated.
		 *
		 * If `length` is zero, then the entire document will be parsed. Otherwise,
		 * the given ranges must be ordered from earliest to latest in the document,
		 * and they must not overlap. That is, the following must hold for all
		 * `i` < `length - 1`: ranges[i].end_byte <= ranges[i + 1].start_byte
		 *
		 * If this requirement is not satisfied, the operation will fail, the ranges
		 * will not be assigned, and this function will return `false`. On success,
		 * this function returns `true`
		 */
		bool set_included_ranges(const TSRange* ranges, uint32_t length) { return ts_parser_set_included_ranges(*this, ranges, length); }
		bool set_included_ranges(const std::span<TSRange> ranges) { return set_included_ranges(ranges.data(), ranges.size()); }
		bool set_included_ranges(const TSRange& range) { return set_included_ranges(&range, 1); }

		/**
		 * Get the ranges of text that the parser will include when parsing.
		 *
		 * The returned pointer is owned by the parser. The caller should not free it
		 * or write to it. The length of the array will be written to the given
		 * `length` pointer.
		 */
		const TSRange* included_ranges(uint32_t* length) const { return ts_parser_included_ranges(*this, length); }
		std::span<const TSRange> included_ranges() const {
			uint32_t len;
			auto* ranges = included_ranges(&len);
			return std::span{ranges, (size_t)len};
		}

		/**
		 * Use the parser to parse some source code and create a syntax tree.
		 *
		 * If you are parsing this document for the first time, pass `NULL` for the
		 * `old_tree` parameter. Otherwise, if you have already parsed an earlier
		 * version of this document and the document has since been edited, pass the
		 * previous syntax tree so that the unchanged parts of it can be reused.
		 * This will save time and memory. For this to work correctly, you must have
		 * already edited the old syntax tree using the `ts_tree_edit` function in a
		 * way that exactly matches the source code changes.
		 *
		 * The `TSInput` parameter lets you specify how to read the text. It has the
		 * following three fields:
		 * 1. `read`: A function to retrieve a chunk of text at a given byte offset
		 *    and (row, column) position. The function should return a pointer to the
		 *    text and write its length to the `bytes_read` pointer. The parser does
		 *    not take ownership of this buffer; it just borrows it until it has
		 *    finished reading it. The function should write a zero value to the
		 *    `bytes_read` pointer to indicate the end of the document.
		 * 2. `payload`: An arbitrary pointer that will be passed to each invocation
		 *    of the `read` function.
		 * 3. `encoding`: An indication of how the text is encoded. Either
		 *    `TSInputEncodingUTF8` or `TSInputEncodingUTF16`.
		 *
		 * This function returns a syntax tree on success, and `NULL` on failure. There
		 * are three possible reasons for failure:
		 * 1. The parser does not have a language assigned. Check for this using the
			 `language` function.
		* 2. Parsing was cancelled due to a timeout that was set by an earlier call to
		*    the `set_timeout_micros` function. You can resume parsing from
		*    where the parser left out by calling `parse` again with the
		*    same arguments. Or you can start parsing from scratch by first calling
		*    `reset`.
		* 3. Parsing was cancelled using a cancellation flag that was set by an
		*    earlier call to `set_cancellation_flag`. You can resume parsing
		*    from where the parser left out by calling `parse` again with
		*    the same arguments.
		*/
		inline Tree parse(const TSTree* old_tree, TSInput input) { return ts_parser_parse(*this, old_tree, input); }
		inline Tree parse(const Tree old_tree, TSInput input) { return ts_parser_parse(*this, old_tree, input); }
		inline Tree parse(TSInput input) { return parse(nullptr, input); }

		/**
		 * Use the parser to parse some source code stored in one contiguous buffer.
		 * The first two parameters are the same as in the `parse` function
		 * above. The second two parameters indicate the location of the buffer and its
		 * length in bytes.
		 */
		inline Tree parse_string(const TSTree* old_tree, const std::string_view string) { return ts_parser_parse_string(*this, old_tree, string.data(), string.size()); }
		inline Tree parse_string(const Tree old_tree, const std::string_view string) { return ts_parser_parse_string(*this, old_tree, string.data(), string.size()); }
		inline Tree parse_string(const std::string_view string) { return parse_string(nullptr, string); }

		/**
		 * Use the parser to parse some source code stored in one contiguous buffer with
		 * a given encoding. The first four parameters work the same as in the
		 * `parse_string` method above. The final parameter indicates whether
		 * the text is encoded as UTF8 or UTF16.
		 */
		inline Tree parse_string_encoding(const TSTree* old_tree, const std::string_view string, const TSInputEncoding encoding) { return ts_parser_parse_string_encoding(*this, old_tree, string.data(), string.size(), encoding); }
		inline Tree parse_string_encoding(const Tree old_tree, const std::string_view string, const TSInputEncoding encoding) { return ts_parser_parse_string_encoding(*this, old_tree, string.data(), string.size(), encoding); }
		inline Tree parse_string_encoding(const std::string_view string, const TSInputEncoding encoding) { return parse_string_encoding(nullptr, string, encoding); }

		/**
		 * Instruct the parser to start the next parse from the beginning.
		 *
		 * If the parser previously failed because of a timeout or a cancellation, then
		 * by default, it will resume where it left off on the next call to
		 * `parse` or other parsing functions. If you don't want to resume,
		 * and instead intend to use this parser to parse some other document, you must
		 * call `reset` first.
		 */
		inline void reset() { return ts_parser_reset(*this); }

		/**
		 * Set the maximum duration in microseconds that parsing should be allowed to
		 * take before halting.
		 *
		 * If parsing takes longer than this, it will halt early, returning NULL.
		 * See `parse` for more information.
		 */
		inline void set_timeout_micros(const uint64_t timeout) { return ts_parser_set_timeout_micros(*this, timeout); }

		/**
		 * Get the duration in microseconds that parsing is allowed to take.
		 */
		inline uint64_t timeout_micros() const { return ts_parser_timeout_micros(*this); }
		inline uint64_t get_timeout_micros() const { return timeout_micros(); }

		/**
		 * Set the parser's current cancellation flag pointer.
		 *
		 * If a non-null pointer is assigned, then the parser will periodically read
		 * from this pointer during parsing. If it reads a non-zero value, it will
		 * halt early, returning NULL. See `parse` for more information.
		 */
		inline void set_cancellation_flag(const size_t* flag) { ts_parser_set_cancellation_flag(*this, flag); }

		/**
		 * Get the parser's current cancellation flag pointer.
		 */
		inline const size_t* cancellation_flag() const { return ts_parser_cancellation_flag(*this); }
		inline const size_t* get_cancellation_flag() const { return cancellation_flag(); }

		/**
		 * Set the logger that a parser should use during parsing.
		 *
		 * The parser does not take ownership over the logger payload. If a logger was
		 * previously assigned, the caller is responsible for releasing any memory
		 * owned by the previous logger.
		 */
		inline void set_logger(const TSLogger logger) { ts_parser_set_logger(*this, logger); }

		/**
		 * Get the parser's current logger.
		 */
		inline TSLogger logger() const { return ts_parser_logger(*this); }
		inline TSLogger get_logger() const { return logger(); }
	};

	void ts_parser_delete(Parser p) = delete;
}

#endif // __TREE_SITTERPP_PARSER_HPP__