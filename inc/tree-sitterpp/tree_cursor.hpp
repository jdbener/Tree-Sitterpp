#ifndef __TREE_SITTERPP_TREE_TreeCursor_HPP__
#define __TREE_SITTERPP_TREE_TreeCursor_HPP__

#include "helpers.hpp"
#include "node.hpp"

namespace TreeSitter {

	struct TreeCursor : TSTreeCursor {
		TreeCursor(Node n) : TSTreeCursor(ts_tree_cursor_new(n)) { }
		TreeCursor(TSTreeCursor* move) : TSTreeCursor(*move) { }
		TreeCursor(const TreeCursor& copy) : TSTreeCursor(ts_tree_cursor_copy(copy)) { }
		TreeCursor(TreeCursor&&) = default;
		~TreeCursor() { ts_tree_cursor_delete(*this); }
		inline TreeCursor& operator=(const TreeCursor& copy) { return *this = TreeCursor(copy); } // TODO: Works?
		TreeCursor& operator=(TreeCursor&&) = default;

		inline operator TSTreeCursor*() { return this; }
		inline operator const TSTreeCursor*() const { return this; }


		/**
		 * Re-initialize a tree cursor to start at a different node.
		 */
		void reset(const Node& node) { ts_tree_cursor_reset(*this, node); }

		/**
		 * Get the tree cursor's current node.
		 */
		Node current_node() { return ts_tree_cursor_current_node(*this); }

		/**
		 * Get the field name of the tree cursor's current node.
		 *
		 * This returns `NULL` if the current node doesn't have a field.
		 * See also `ts_node_child_by_field_name`.
		 */
		const std::string_view current_field_name() { return ts_tree_cursor_current_field_name(*this); }

		/**
		 * Get the field id of the tree cursor's current node.
		 *
		 * This returns zero if the current node doesn't have a field.
		 * See also `ts_node_child_by_field_id`, `ts_language_field_id_for_name`.
		 */
		TSFieldId current_field_id() { return ts_tree_cursor_current_field_id(*this); }

		/**
		 * Move the cursor to the parent of its current node.
		 *
		 * This returns `true` if the cursor successfully moved, and returns `false`
		 * if there was no parent node (the cursor was already on the root node).
		 */
		bool goto_parent() { return ts_tree_cursor_goto_parent(*this); }

		/**
		 * Move the cursor to the next sibling of its current node.
		 *
		 * This returns `true` if the cursor successfully moved, and returns `false`
		 * if there was no next sibling node.
		 */
		bool goto_next_sibling() { return ts_tree_cursor_goto_next_sibling(*this); }

		/**
		 * Move the cursor to the first child of its current node.
		 *
		 * This returns `true` if the cursor successfully moved, and returns `false`
		 * if there were no children.
		 */
		bool goto_first_child() { return ts_tree_cursor_goto_first_child(*this); }

		/**
		 * Move the cursor to the first child of its current node that extends beyond
		 * the given byte offset or point.
		 *
		 * This returns the index of the child node if one was found, and returns -1
		 * if no such child was found.
		 */
		int64_t goto_first_child_for_byte(uint32_t byte) { return ts_tree_cursor_goto_first_child_for_byte(*this, byte); }
		int64_t goto_first_child_for_point(TSPoint point) { return ts_tree_cursor_goto_first_child_for_point(*this, point); }

	};

}

#endif // __TREE_SITTERPP_TREE_TreeCursor_HPP__