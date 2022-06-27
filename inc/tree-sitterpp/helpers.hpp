#ifndef __TREE_SITTERPP_DELETER_HPP__
#define __TREE_SITTERPP_DELETER_HPP__

#include <tree_sitter/api.h>
#include <memory>
#include <span>

namespace TreeSitter {
	namespace detail {
		// Struct that includes functions specifying how to delete managed types
		struct Deleter {
			void operator()(TSParser* del) { if(del) ts_parser_delete(del); }
			void operator()(TSTree* del) { if(del) ts_tree_delete(del); }
			void operator()(TSTreeCursor* del) { if(del) ts_tree_cursor_delete(del); }
		};

		// A UniqueHandle is a unique_ptr that uses the ts_ deleters
		template<typename T>
		using UniqueHandle = std::unique_ptr<T, Deleter>;
	}

	// ByteRange indicates the start and end bytes of a node
	using ByteRange = std::pair<uint32_t, uint32_t>;
	// PointRange indicates the start and end points of a node
	using PointRange = std::pair<TSPoint, TSPoint>;
}

namespace ts = TreeSitter;

#endif // __TREE_SITTERPP_DELETER_HPP__