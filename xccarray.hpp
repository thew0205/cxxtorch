#pragma once

#include "xccarray.hpp"
#include "edge.hpp"
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include "node.hpp"

template <typename T>
class xccarray
{
public:
    xt::xarray<T> arr_;
    bool required_grad_;
    GraphNode<T> *node_;
    xt::xarray<T> arr_back_;

    xccarray(const xt::xarray<T> &t) : arr_{t}, required_grad_{false}, node_{nullptr}
    {
    }

    xccarray(const xt::xarray<T> &t, GraphNode<T> *node) : arr_{t}, required_grad_{true}, node_{node}
    {
    }

    void backward()
    {

        if (node_ != nullptr)
            node_->backward(nullptr);
    }
};
