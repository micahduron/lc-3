#pragma once

#include <any>
#include <vector>
#include "Token.h"
#include "NodeType.h"

namespace LC3::Language {

class SyntaxTreeBuilder;

struct SyntaxTreeNode {
    NodeType type = NodeType::Blank;
    Token token;
    std::vector<SyntaxTreeNode> children;

    SyntaxTreeNode() {}
    SyntaxTreeNode(NodeType nodeType) :
      type{ nodeType }
    {}
    SyntaxTreeNode(NodeType nodeType, const Token& nodeToken) :
      type{ nodeType },
      token{ nodeToken }
    {}

    SyntaxTreeNode& child(size_t index) {
        return children[index];
    }

    const SyntaxTreeNode& child(size_t index) const {
        return children[index];
    }

    const SourceLocation& location() const {
        return token.location;
    }

    template <typename VisitorT>
    void walk(VisitorT&& visitor) const {
        visitor(*this);

        for (const auto& child : this->children) {
            visitor(child);
        }
    }

    template <typename NodeT>
    auto& data() {
        return std::any_cast<typename NodeT::DataContainer&>(m_data);
    }

    template <typename NodeT>
    const auto& data() const {
        return std::any_cast<const typename NodeT::DataContainer&>(m_data);
    }

    bool operator == (const SyntaxTreeNode& other) const {
        return this == &other;
    }
    bool operator != (const SyntaxTreeNode& other) const {
        return this != &other;
    }

protected:
    std::any m_data;
};

} // namespace LC3::Language
