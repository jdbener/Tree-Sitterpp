#ifndef __TREE_SITTERPP_TREE_HPP__
#define __TREE_SITTERPP_TREE_HPP__

#include "helpers.hpp"
#include "node.hpp"

namespace TreeSitter {

	struct Tree : detail::UniqueHandle<TSTree> {
		using detail::UniqueHandle<TSTree>::UniqueHandle;
		using detail::UniqueHandle<TSTree>::operator=;

		Tree(TSTree* tree) : detail::UniqueHandle<TSTree>(tree) { }
		Tree(const Tree& copy) : detail::UniqueHandle<TSTree>(ts_tree_copy(copy)) { }
		Tree(Tree&&) = default;
		inline Tree& operator=(const Tree& copy) { return *this = Tree(copy); } // TODO: Works?
		Tree& operator=(Tree&&) = default;

		inline operator TSTree*() { return get(); }
		inline operator const TSTree*() const { return get(); }


		/**
		 * Get the root node of the syntax tree.
		 */
		inline Node root_node() const { return ts_tree_root_node(*this); }

		/**
		 * Get the language that was used to parse the syntax tree.
		 */
		inline const TSLanguage* language() const { return ts_tree_language(*this); }
		inline const TSLanguage* get_language() const { return language(); }

		/**
		 * Edit the syntax tree to keep it in sync with source code that has been
		 * edited.
		 *
		 * You must describe the edit both in terms of byte offsets and in terms of
		 * (row, column) coordinates.
		 */
		inline void edit(const TSInputEdit* edit) { ts_tree_edit(*this, edit); }
		inline void edit(const TSInputEdit& edit_) { edit(&edit_); }

		/**
		 * Compare an old edited syntax tree to a new syntax tree representing the same
		 * document, returning an array of ranges whose syntactic structure has changed.
		 *
		 * For this to work correctly, the old syntax tree must have been edited such
		 * that its ranges match up to the new tree. Generally, you'll want to call
		 * this function right after calling one of the `ts_parser_parse` functions.
		 * You need to pass the old tree that was passed to parse, as well as the new
		 * tree that was returned from that function.
		 *
		 * The returned array is allocated using `malloc` and the caller is responsible
		 * for freeing it using `free`. The length of the array will be written to the
		 * given `length` pointer.
		 */
		inline const TSRange* get_changed_ranges(const Tree new_tree, uint32_t* length) const { return ts_tree_get_changed_ranges(*this, new_tree, length); }
		std::span<const TSRange> get_changed_ranges(const Tree new_tree) const {
			uint32_t len;
			auto range = get_changed_ranges(new_tree, &len);
			return std::span{range, len};
		}

	};

	void ts_tree_delete(Tree p) = delete;
}

#endif // __TREE_SITTERPP_TREE_HPP__