#pragma once

#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include <vector>
#include <initializer_list>
#include <memory>

#include "xcctensor.hpp"
#include "node.hpp"
#include "edge.hpp"
// Explicitly instan

template <typename T>
class xcctensor;

template <typename T>
class Function;

template <typename T>
class GraphNode;

template <typename T>
class GraphEdge;

template <typename T>
class Function
{
public:
    virtual std::string name() = 0;
    virtual std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) = 0;

    virtual void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr)
    {
        if (arr != nullptr)
        {

            for (auto &node : nodes)
            {
                node->arr_->arr_back_ *= arr->arr_back_;
            }
        }
    }
};

template <typename T>
class Relu : public Function<T>
{
public:
    static Relu<T> relu;
    virtual std::string name() override
    {
        return "relu";
    }
    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {
        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&relu, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(
            xt::maximum(arrs[0]->arr_, 0.0f), node);
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {
        nodes[0]->arr_->arr_back_ = xt::where(nodes[0]->arr_->arr_ >= 0.0f, 1.0f, 0.0f);
        Function<T>::backward(nodes, arr);
    }
};
template <typename T>

Relu<T> Relu<T>::relu;

template <typename T>
inline std::shared_ptr<xcctensor<T>> relu(const std::shared_ptr<xcctensor<T>> &arr)
{
    return Relu<T>::relu.forward({arr});
}

template <typename T>
class Add : public Function<T>
{
public:
    static Add<T> add;
    virtual std::string name() override
    {
        return "add";
    }
    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {

        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&add, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(xt::zeros<T>(arrs[0]->arr_.shape()), node);
        for (auto &arr : arrs)
        {
            ret->arr_ += arr->arr_;
        }
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {
        for (auto &node : nodes)
        {
            node->arr_->arr_back_ = xt::ones<T>(node->arr_->arr_.shape());
        }
        Function<T>::backward(nodes, arr);
    }
};

template <typename T>

Add<T> Add<T>::add;

template <typename T>
inline std::shared_ptr<xcctensor<T>> add(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return Add<T>::add.forward({arr1, arr2});
}

// Define the + operator as a member function
template <typename T>
inline std::shared_ptr<xcctensor<T>> operator+(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return add(arr1, arr2);
}

template <typename T>
class Subtract : public Function<T>
{
public:
    static Subtract<T> subtract;
    virtual std::string name() override
    {
        return "subtract";
    }
    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {

        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&subtract, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(arrs[0]->arr_, node);
        for (size_t i = 1; i < arrs.size(); i++)
        {
            ret->arr_ -= arrs[i]->arr_;
        }
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {

        nodes[0]->arr_->arr_back_ = xt::ones<T>(nodes[0]->arr_->arr_.shape());
        for (size_t i = 1; i < nodes.size(); i++)
        {
            nodes[i]->arr_->arr_back_ = -(xt::ones<T>(nodes[i]->arr_->arr_.shape()));
        }
        Function<T>::backward(nodes, arr);
    }
};

template <typename T>

Subtract<T> Subtract<T>::subtract;

template <typename T>
inline std::shared_ptr<xcctensor<T>> subtract(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return Subtract<T>::subtract.forward({arr1, arr2});
}

// Define the + operator as a member function
template <typename T>
inline std::shared_ptr<xcctensor<T>> operator-(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return subtract(arr1, arr2);
}

template <typename T>
class Multiply : public Function<T>
{
public:
    static Multiply<T> multiply;
    virtual std::string name() override
    {
        return "multiply";
    }
    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {
        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&multiply, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(xt::ones<T>(arrs[0]->arr_.shape()), node);
        for (auto &arr : arrs)
        {
            ret->arr_ *= arr->arr_;
        }
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {
        const size_t size = nodes.size();
        for (size_t i = 0; i < size; i++)
        {
            nodes[i]->arr_->arr_back_ = xt::ones<T>(nodes[i]->arr_->arr_.shape());

            for (size_t j = 0; j < size; j++)
            {
                if (i != j)
                {
                    nodes[i]->arr_->arr_back_ *= nodes[j]->arr_->arr_;
                }
            }
        }
        Function<T>::backward(nodes, arr);
    }
};

template <typename T>
Multiply<T> Multiply<T>::multiply;

template <typename T>
inline std::shared_ptr<xcctensor<T>> multiply(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return Multiply<T>::multiply.forward({arr1, arr2});
}

// Define the + operator as a member function
template <typename T>
inline std::shared_ptr<xcctensor<T>> operator*(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return multiply(arr1, arr2);
}

template <typename T>
class Dot : public Function<T>
{
public:
    static Dot<T> dot;

    virtual std::string name() override
    {
        return "dot";
    }

    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {

        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&dot, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(xt::ones<T>(arrs[0]->arr_.shape()), node);

        for (auto &arr : arrs)
        {
            ret->arr_ *= arr->arr_;
        }
        ret->arr_ = xt::sum(ret->arr_);

        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {
        const size_t size = nodes.size();
        for (size_t i = 0; i < size; i++)
        {
            nodes[i]->arr_->arr_back_ = xt::ones<T>(nodes[i]->arr_->arr_.shape());

            for (size_t j = 0; j < size; j++)
            {
                if (i != j)
                {
                    nodes[i]->arr_->arr_back_ *= nodes[j]->arr_->arr_;
                }
            }
        }
        Function<T>::backward(nodes, arr);
    }
};
template <typename T>
Dot<T> Dot<T>::dot;

template <typename T>
inline std::shared_ptr<xcctensor<T>> dot(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return Dot<T>::dot.forward({arr1, arr2});
}

template <typename T>
class MSE : public Function<T>
{
public:
    static MSE<T> mse;
    virtual std::string name() override
    {
        return "mse";
    }

    std::shared_ptr<xcctensor<T>> forward(const std::vector<std::shared_ptr<xcctensor<T>>> &arrs) override
    {
        std::vector<std::shared_ptr<GraphNode<T>>> nodes = make_nodes_from_xccarrry<T>(arrs);
        std::shared_ptr<GraphEdge<T>> edge = std::make_shared<GraphEdge<T>>(&mse, nodes);
        std::shared_ptr<GraphNode<T>> node = make_shared<GraphNode<T>>(edge);

        std::shared_ptr<xcctensor<T>> ret = std::make_shared<xcctensor<T>>(xt::mean(xt::pow<2>(arrs[0]->arr_ - arrs[1]->arr_)), node);

        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<std::shared_ptr<GraphNode<T>>> nodes, const std::shared_ptr<xcctensor<T>> arr) override
    {
        nodes[0]->arr_->arr_back_ = ((nodes[0]->arr_->arr_ - nodes[1]->arr_->arr_) * 2 / nodes[0]->arr_->arr_.size());
        nodes[1]->arr_->arr_back_ = -(nodes[0]->arr_->arr_back_);
        Function<T>::backward(nodes, arr);
    }
};

template <typename T>
MSE<T> MSE<T>::mse;


template <typename T>
inline std::shared_ptr<xcctensor<T>> mse(const std::shared_ptr<xcctensor<T>> &arr1, const std::shared_ptr<xcctensor<T>> &arr2)
{
    return MSE<T>::mse.forward({arr1, arr2});
}
