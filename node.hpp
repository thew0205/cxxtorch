#pragma once

#include "xcctensor.hpp"
#include "edge.hpp"
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>
#include <vector>

#include <initializer_list>
#include <memory>

template <typename T>
class xcctensor;

template <typename T>
class Function;

template <typename T>
class GraphNode;

template <typename T>
class GraphEdge;

template <typename T>
class GraphNode
{
public:
    std::shared_ptr<xcctensor<T>> arr_;
    std::shared_ptr<GraphEdge<T>> edge_;

    GraphNode(const std::shared_ptr<GraphEdge<T>> &edge) : arr_{}, edge_{edge} {}

    GraphNode(const std::shared_ptr<xcctensor<T>> &arr) : arr_{arr}, edge_{} {}

    std::string print(size_t indent = 0)
    {
        std::ostringstream oss;
        std::string tab;
        for (size_t i = 0; i < indent; i++)
        {
            tab += "  ";
        }
        oss << tab << "|--" << "xarr: " << arr_->arr_ << " @ " << arr_ << "\n";
        if (edge_ != nullptr)
        {
            oss << edge_->print(indent);
        }

        // Retrieving the string
        // std::cout << oss.str() << "\n";

        return oss.str();
    }

    void backward(const std::shared_ptr<xcctensor<T>> arr)
    {
        if (edge_ != nullptr)
        {
            edge_->backward(arr);
        }
    }
};

template <typename T>
inline std::vector<std::shared_ptr<GraphNode<T>>> make_nodes_from_xccarrry(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs)
{
    std::vector<std::shared_ptr<GraphNode<T>>> nodes;
    for (auto &arr : arrs)
    {
        if (arr->node_ != nullptr)
        {
            nodes.push_back(arr->node_);
        }
        else
        {
            auto a = std::make_shared<GraphNode<T>>(arr);
            nodes.push_back(a);
        }
    }
    return nodes;
}