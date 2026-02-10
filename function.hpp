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

#include "xccarray.hpp"
#include "node.hpp"
#include "edge.hpp"
// Explicitly instan

template <typename T>
class xccarray;

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
    virtual xccarray<T> *forward(const std::vector<xccarray<T> *> &arrs) = 0;
    virtual void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr)
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
    xccarray<T> *forward(const std::vector<xccarray<T> *> &arrs) override
    {
        auto nodes = make_nodes_from_xccarrry<T>(arrs);
        auto edge = new GraphEdge<T>{this, nodes};
        GraphNode<T> *node = new GraphNode<T>{nullptr, edge};

        auto ret = new xccarray<T>{
            xt::maximum(arrs[0]->arr_, 0.0f), node};
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr) override
    {
        nodes[0]->arr_->arr_back_ = xt::where(nodes[0]->arr_->arr_ >= 0.0f, 1.0f, 0.0f);
        Function<T>::backward(nodes, arr);
    }
};
template <typename T>

Relu<T> Relu<T>::relu;

template <typename T>
class Add : Function<T>
{
public:
    static Add<T> add;
    virtual std::string name() override
    {
        return "add";
    }
    xccarray<T> *forward(const std::vector<xccarray<T> *> &arrs) override
    {

        auto nodes = make_nodes_from_xccarrry<T>(arrs);
        auto edge = new GraphEdge<T>{this, nodes};
        GraphNode<T> *node = new GraphNode<T>{nullptr, edge};

        xccarray<T> *ret = new xccarray<T>{xt::zeros<T>(arrs[0]->arr_.shape()), node};
        for (auto &arr : arrs)
        {
            ret->arr_ += arr->arr_;
        }
        node->arr_ = ret;

        return ret;
    }
    void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr) override
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
class Multiply : Function<T>
{
public:
    static Multiply<T> multiply;
 virtual std::string name() override
    {
        return "multiply";
    }
    xccarray<T>* forward(const std::vector<xccarray<T> *> &arrs) override
    {
      auto nodes = make_nodes_from_xccarrry<T>(arrs);
        auto edge = new GraphEdge<T>{this, nodes};
        GraphNode<T> *node = new GraphNode<T>{nullptr, edge};
        xccarray<T> *ret = new xccarray<T>{xt::ones<T>(arrs[0]->arr_.shape()), node};
        for (auto &arr : arrs)
        {
            ret->arr_ *= arr->arr_;
        }
        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr) override
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
class Dot : public Function<T>
{
public:
    static Dot<T> dot;

    virtual std::string name() override
    {
        return "dot";
    }

    xccarray<T> *forward(const std::vector<xccarray<T> *> &arrs) override
    {

        auto nodes = make_nodes_from_xccarrry<T>(arrs);
        auto edge = new GraphEdge<T>{this, nodes};
        GraphNode<T> *node = new GraphNode<T>{nullptr, edge};
        xccarray<T> *ret = new xccarray<T>{xt::ones<T>(arrs[0]->arr_.shape()), node};
        for (auto &arr : arrs)
        {
            ret->arr_ *= arr->arr_;
        }
        ret->arr_ = xt::sum(ret->arr_);

        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr) override
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
class MSE : public Function<T>
{
public:
    static MSE<T> mse;
    virtual std::string name() override
    {
        return "mse";
    }

    xccarray<T> *forward(const std::vector<xccarray<T> *> &arrs) override
    {
        auto nodes = make_nodes_from_xccarrry<T>(arrs);
        auto edge = new GraphEdge<T>{this, nodes};
        GraphNode<T> *node = new GraphNode<T>{nullptr, edge};
        xccarray<T> *ret = new xccarray<T>{xt::mean(xt::pow<2>(arrs[0]->arr_ - arrs[1]->arr_)), node};

        node->arr_ = ret;

        return ret;
    }

    void backward(std::vector<GraphNode<T> *> nodes, const xccarray<T> *arr) override
    {
        nodes[0]->arr_->arr_back_ = ((nodes[0]->arr_->arr_ - nodes[1]->arr_->arr_) * 2 / nodes[0]->arr_->arr_.size());
        nodes[1]->arr_->arr_back_ = -(nodes[0]->arr_->arr_back_);
        Function<T>::backward(nodes, arr);
    }
};

template <typename T>
MSE<T> MSE<T>::mse;