#pragma once

#include "xccarray.hpp"
#include "node.hpp"

#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include <initializer_list>
#include <memory>
#include "function.hpp"
template <typename T>
class GraphNode;

template <typename T>
class GraphEdge
{
public:
    Function<T> *fun_;
    std::vector<GraphNode<T> *> nodes_;

    GraphEdge(Function<T> *fun, const std::vector<GraphNode<T> *> &nodes) : fun_{fun}, nodes_{nodes}
    {
    }

    std::string print(size_t indent = 0)
    {
        std::ostringstream oss;
        std::string tab;
        for(size_t i = 0; i < indent +1; i++){
            tab += "  ";
        }
        if (fun_ != nullptr)
        {
            oss << tab << "|" << "\n";
            oss << tab << fun_->name() << "\n";
            oss << tab << "|" << "\n";
            ++indent;
            for (auto &node : nodes_)
            {
                oss << node->print(indent);
            }
        }

        // Retrieving the string
        // std::cout << oss.str() << "\n";
        return oss.str();
    }

    void backward(const xccarray<T> *arr)
    {
        if (fun_ != nullptr)
        {
            fun_->backward(nodes_, arr);
            for (auto node : nodes_)
            {

                node->backward(node->arr_);
            }
        }
    }
};
