#pragma once

#include "xcctensor.hpp"
#include "edge.hpp"
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include "node.hpp"

template <typename T>
class xcctensor
{
public:
    xt::xarray<T> arr_;
    bool required_grad_;
    std::shared_ptr<GraphNode<T>> node_;
    xt::xarray<T> arr_back_;

    xcctensor(const xt::xarray<T> &t) : arr_{t}, required_grad_{false}, node_{}
    {
    }

    xcctensor(const xt::xarray<T> &t, std::shared_ptr<GraphNode<T>> &node) : arr_{t}, required_grad_{true}, node_{node}
    {
    }

    void backward()
    {

        if (node_ != nullptr)
            node_->backward({});
    }
};

template <typename T>
using Tensor = std::shared_ptr<xcctensor<T>>;

template <typename T>
Tensor<T> make_tensor(const xt::xarray<T> &arr)
{
    return std::make_shared<xcctensor<T>>(arr);
}