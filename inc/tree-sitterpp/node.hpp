#ifndef __TREE_SITTERPP_NODE_HPP__
#define __TREE_SITTERPP_NODE_HPP__

#include "helpers.hpp"
#include <optional>

namespace TreeSitter {
	struct Node : TSNode {
		Node() { id = nullptr; tree = nullptr; }
		inline Node(const TSNode& copy) { *this = copy; };
		inline Node(TSNode&& move) { *this = std::move(move); };
		Node(const Node&) = default;
		Node(Node&&) = default;

		Node& operator=(const TSNode& copy) { for(uint8_t i = 0; i < 4; i++) context[i] = copy.context[i]; id = copy.id; tree = copy.tree; return *this; };
		Node& operator=(TSNode&& move) { for(uint8_t i = 0; i < 4; i++) context[i] = move.context[i]; id = move.id; tree = move.tree; return *this; };
		Node& operator=(const Node& copy) = default;
		Node& operator=(Node&& move) = default;

		/**
		 * Get the node's type as a null-terminated string.
		 */
		inline const std::string_view type() const { return ts_node_type(*this); }
		inline const std::string_view get_type() const { return type(); }

		/**
		 * Get the node's type as a numerical id.
		 */
		inline TSSymbol symbol() const { return ts_node_symbol(*this); }
		inline TSSymbol get_symbol() const { return symbol(); }

		/**
		 * Get the node's start byte.
		 */
		inline uint32_t start_byte() const { return ts_node_start_byte(*this); }
		inline uint32_t get_start_byte() const { return start_byte(); }

		/**
		 * Get the node's start position in terms of rows and columns.
		 */
		inline TSPoint start_point() const { return ts_node_start_point(*this); }
		inline TSPoint get_start_point() const { return start_point(); }

		/**
		 * Get the node's end byte.
		 */
		inline uint32_t end_byte() const { return ts_node_end_byte(*this); }
		inline uint32_t get_end_byte() const { return end_byte(); }

		/**
		 * Get the node's end position in terms of rows and columns.
		 */
		inline TSPoint end_point() const { return ts_node_end_point(*this); }
		inline TSPoint get_end_point() const { return end_point(); }

		/**
		 * Get the node's start and end point and byte.
		 */
		inline TSRange range() const { return { start_point(), end_point(), start_byte(), end_byte() }; }
		inline TSRange get_range() const { return range(); }

		/**
		 * Get the node's start and end byte.
		 */
		inline ByteRange byte_range() const { return { start_byte(), end_byte() }; }
		inline ByteRange get_byte_range() const { return byte_range(); }

		/**
		 * Get the node's start and end point.
		 */
		inline std::pair<TSPoint, TSPoint> point_range() const { return { start_point(), end_point() }; }
		inline std::pair<TSPoint, TSPoint> get_point_range() const { return point_range(); }

		/**
		 * Get an S-expression representing the node as a string.
		 *
		 * This string is allocated with `malloc` and the caller is responsible for
		 * freeing it using `free`.
		 */
		std::string string() const {
			char* raw = ts_node_string(*this);
			std::string out = raw;
			free(raw);
			return out;
		}
		inline std::string get_string() const { return string(); }

		/**
		 * Gets the index of this child in its parent
		 */
		uint32_t child_index() const {
			uint32_t i = 0;

			Node prev = *this;
			while(prev.has_prev_sibling()){
				i++;
				prev = prev_sibling();
			}

			return i;
		}
		inline uint32_t get_child_index() const { return child_index(); }

		/**
		 * Gets the field name of this node
		 */
		std::optional<std::string_view> field_name() { return get_parent().get_field_name_for_child(child_index()); }
		inline std::optional<std::string_view> get_field_name() { return field_name(); }

		/**
		 * Check if the node is null. Functions like `child` and
		 * `next_sibling` will return a null node to indicate that no such node
		 * was found.
		 */
		inline bool is_null() const { return ts_node_is_null(*this); }

		/**
		 * Check if the node is *named*. Named nodes correspond to named rules in the
		 * grammar, whereas *anonymous* nodes correspond to string literals in the
		 * grammar.
		 */
		inline bool is_named() const { return ts_node_is_named(*this); }

		/**
		 * Check if the node is *missing*. Missing nodes are inserted by the parser in
		 * order to recover from certain kinds of syntax errors.
		 */
		inline bool is_missing() const { return ts_node_is_missing(*this); }

		/**
		 * Check if the node is *extra*. Extra nodes represent things like comments,
		 * which are not required the grammar, but can appear anywhere.
		 */
		inline bool is_extra() const { return ts_node_is_extra(*this); }

		/**
		 * Check if a syntax node has been edited.
		 */
		inline bool has_changes() const { return ts_node_has_changes(*this); }

		/**
		 * Check if the node is a syntax error or contains any syntax errors.
		 */
		inline bool has_error() const { return ts_node_has_error(*this); }

		/**
		 * Get the node's immediate parent.
		 */
		inline Node parent() const { return ts_node_parent(*this); }
		inline Node get_parent() const { return parent(); }

		/**
		 * Get the node's child at the given index, where zero represents the first
		 * child.
		 */
		inline Node child(uint32_t i) const { return ts_node_child(*this, i); }
		inline Node get_child(uint32_t i) const { return child(i); }
		inline Node operator[](uint32_t i) const { return child(i); }

		/**
		 * Get the field name for node's child at the given index, where zero represents
		 * the first child. Returns NULL, if no field is found.
		 */
		std::optional<std::string_view> field_name_for_child(uint32_t i) const {
			auto name = ts_node_field_name_for_child(*this, i);
			if(name == nullptr) return {};
			return name;
		}
		inline std::optional<std::string_view> get_field_name_for_child(uint32_t i) const { return field_name_for_child(i); }

		/**
		 * Get the node's number of children.
		 */
		inline uint32_t child_count() const { return ts_node_child_count(*this); }
		inline uint32_t get_child_count() const { return child_count(); }

		/**
		 * Get the node's *named* child at the given index.
		 *
		 * See also `is_named`.
		 */
		inline Node named_child(uint32_t i) const { return ts_node_named_child(*this, i); }
		inline Node get_named_child(uint32_t i) const { return named_child(i); }

		/**
		 * Get the node's number of *named* children.
		 *
		 * See also `is_named`.
		 */
		inline uint32_t named_child_count() const { return ts_node_named_child_count(*this); }
		inline uint32_t get_named_child_count() const { return named_child_count(); }

		/**
		 * Get the node's child with the given field name.
		 */
		inline Node child_by_field_name(const std::string_view name) const { return ts_node_child_by_field_name(*this, name.data(), name.size()); }
		inline Node get_child_by_field_name(const std::string_view name) const { return child_by_field_name(name); }

		/**
		 * Get the node's child with the given numerical field id.
		 *
		 * You can convert a field name to an id using the
		 * `ts_language_field_id_for_name` function.
		 */
		inline Node child_by_field_id(TSFieldId id) const { return ts_node_child_by_field_id(*this, id); }
		inline Node get_child_by_field_id(TSFieldId id) const { return child_by_field_id(id); }

		/**
		 * Get the node's next / previous sibling.
		 */
		inline Node next_sibling() const { return ts_node_next_sibling(*this); }
		inline Node get_next_sibling() const { return next_sibling(); }
		inline Node prev_sibling() const { return ts_node_prev_sibling(*this); }
		inline Node get_prev_sibling() const { return prev_sibling(); }

		/**
		 * Check if the node has a next / previous sibling.
		 */
		bool has_next_sibling() const { return !next_sibling().is_null(); }
		bool has_prev_sibling() const { return !prev_sibling().is_null(); }

		/**
		 * Get the node's next / previous *named* sibling.
		 */
		inline Node next_named_sibling() const { return ts_node_next_named_sibling(*this); }
		inline Node get_next_named_sibling() const { return next_named_sibling(); }
		inline Node prev_named_sibling() const { return ts_node_prev_named_sibling(*this); }
		inline Node get_prev_named_sibling() const { return next_named_sibling(); }

		/**
		 * Check if the node has a next / previous sibling.
		 */
		bool has_next_named_sibling() const { return !next_named_sibling().is_null(); }
		bool has_prev_named_sibling() const { return !prev_named_sibling().is_null(); }

		/**
		 * Get the node's first child that extends beyond the given byte offset.
		 */
		inline Node first_child_for_byte(uint32_t byte) const { return ts_node_first_child_for_byte(*this, byte); }

		/**
		 * Get the node's first named child that extends beyond the given byte offset.
		 */
		inline Node first_named_child_for_byte(uint32_t byte) const { return ts_node_first_named_child_for_byte(*this, byte); }

		/**
		 * Get the smallest node within this node that spans the given range of bytes
		 * or (row, column) positions.
		 */
		inline Node descendant_for_byte_range(uint32_t start, uint32_t end) const { return ts_node_descendant_for_byte_range(*this, start, end); }
		inline Node descendant_for_byte_range(ByteRange range) const { return descendant_for_byte_range(range.first, range.second); };
		inline Node descendant_for_point_range(TSPoint start, TSPoint end) const { return ts_node_descendant_for_point_range(*this, start, end); }
		inline Node descendant_for_point_range(PointRange range) const { return descendant_for_point_range(range.first, range.second); }

		/**
		 * Get the smallest named node within this node that spans the given range of
		 * bytes or (row, column) positions.
		 */
		inline Node named_descendant_for_byte_range(uint32_t start, uint32_t end) const { return ts_node_named_descendant_for_byte_range(*this, start, end); }
		inline Node named_descendant_for_byte_range(ByteRange range) const { return named_descendant_for_byte_range(range.first, range.second); }
		inline Node named_descendant_for_point_range(TSPoint start, TSPoint end) const { return ts_node_named_descendant_for_point_range(*this, start, end); }
		inline Node named_descendant_for_point_range(PointRange range) const { return named_descendant_for_point_range(range.first, range.second); }

		/**
		 * Edit the node to keep it in-sync with source code that has been edited.
		 *
		 * This function is only rarely needed. When you edit a syntax tree with the
		 * `ts_tree_edit` function, all of the nodes that you retrieve from the tree
		 * afterward will already reflect the edit. You only need to use `edit`
		 * when you have a `Node` instance that you want to keep and continue to use
		 * after an edit.
		 */
		inline void edit(const TSInputEdit* edit) { return ts_node_edit(this, edit); }
		inline void edit(const TSInputEdit& edit_) { return edit(&edit_); }

		/**
		 * Check if two nodes are identical.
		 */
		inline bool eq(TSNode other) const { return ts_node_eq(*this, other); }
		inline bool operator==(TSNode other) const { return eq(other); }
	};
}

#endif // __TREE_SITTERPP_NODE_HPP__