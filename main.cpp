

#include <iostream>
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <initializer_list>
#include <memory>
// Explicitly instantiate MyClass for int and std::string
// template class xt::xarray<int>;
// template class xt::xarray<<float>;
template class xt::xarray_container<
    xt::uvector<int, std::allocator<int>>,
    xt::layout_type::row_major,
    xt::svector<std::size_t, 4, std::allocator<std::size_t>, true>>;

template <typename T>
class xccarray;

template <typename T>
class Function;

template<typename T>
class GraphNode;

template<typename T>
class GraphEdge{
    public:

    Function<T>* fun_;
    std::vector<GraphNode<T>*> nodes_;
    
    GraphEdge(Function<T>* fun, const std::vector<GraphNode<T>*>& nodes): fun_{fun}, nodes_{nodes}{

    }
};

template<typename T>
class GraphNode{
    public:
    xccarray<T>* arr_;
    std::vector<GraphEdge<T>*> edges_;

    GraphNode(xccarray<T>* arr, const std::vector<GraphEdge<T>*> edges): arr_{arr}, edges_{edges}{}
};

template <typename T>
class Function
{
public:
    virtual xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) = 0;
    virtual void backward(const std::vector<xccarray<T> *> &arrs)
    {
        for (auto &arr : arrs)
        {
            arr->backward();
        }
    };
};

template <typename T>
class Relu : Function<T>
{
public:
    static Relu<T> relu;

    xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) override
    {
        return xccarray<T>{
            xt::maximum(arrs[0]->arr_, 0.0f), this, arrs};
    }

    void backward(const std::vector<xccarray<T> *> &arrs) override
    {
        arrs[0]->arr_back_ = xt::where(arrs[0]->arr_ >= 0.0f, 1.0f, 0.0f);
        Function<T>::backward(arrs);
    }
};
template <typename T>

Relu<T> Relu<T>::relu;

template <typename T>
class Add : Function<T>
{
public:
    static Add<T> add;

    xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) override
    {
        xccarray<T> ret{xt::zeros<T>(arrs[0]->arr_.shape()), this, arrs};
        for (auto &arr : arrs)
        {
            ret.arr_ += arr->arr_;
        }
        return ret;
    }

    void backward(const std::vector<xccarray<T> *> &arrs) override
    {
        for (auto &arr : arrs)
        {
            arr->arr_back_ = xt::xarray<T>(1);
        }
    }
};

template <typename T>

Add<T> Add<T>::add;
template <typename T>
class Multiply : Function<T>
{
public:
    static Multiply<T> multiply;

    xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) override
    {
        xccarray<T> ret{xt::ones<T>(arrs[0]->arr_.shape()), this, arrs};
        for (auto &arr : arrs)
        {
            ret.arr_ *= arr->arr_;
        }
        return ret;
    }

    void backward(const std::vector<xccarray<T> *> &arrs) override
    {

        for (size_t i = 0; i < arrs.size(); i++)
        {
            arrs[i]->arr_back_ = xt::ones<T>(arrs[0]->arr_.shape());

            for (size_t j = 0; j < arrs.size(); j++)
            {
                if (i != j)
                {
                    arrs[i]->arr_back_ *= arrs[j]->arr_;
                }
            }
        }
    }
};

template <typename T>
Multiply<T> Multiply<T>::multiply;

template <typename T>
class Dot : public Function<T>
{
public:
    static Dot<T> dot;
    xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) override
    {
        xccarray<T> ret{xt::ones<T>(arrs[0]->arr_.shape())};
        for (auto &arr : arrs)
        {
            ret.arr_ *= arr->arr_;
        }
        return xccarray<T>{xt::sum(ret.arr_), this, arrs};
    }

    void backward(const std::vector<xccarray<T> *> &arrs) override
    {
        for (size_t i = 0; i < arrs.size(); i++)
        {
            arrs[i]->arr_back_ = xt::ones<T>(arrs[0]->arr_.shape());

            for (size_t j = 0; j < arrs.size(); j++)
            {
                if (i != j)
                {
                    arrs[i]->arr_back_ *= arrs[j]->arr_;
                }
            }
        }
        Function<T>::backward(arrs);
    }
};
template <typename T>
Dot<T> Dot<T>::dot;

template <typename T>
class MSE : public Function<T>
{
public:
    static MSE<T> mse;
    xccarray<T> forward(const std::vector<xccarray<T> *> &arrs) override
    {
        return xccarray<T>{xt::mean(xt::pow<2>(arrs[0]->arr_ - arrs[1]->arr_)), this, arrs};
    }

    void backward(const std::vector<xccarray<T> *> &arrs) override
    {
       arrs[0]->arr_back_ = ((arrs[0]->arr_ - arrs[1]->arr_) * 2 / arrs[0]->arr_.size());
       arrs[1]->arr_back_= -(arrs[0]->arr_back_);
        Function<T>::backward(arrs);
    }
};

template <typename T>
MSE<T> MSE<T>::mse;

template <typename T>
class xccarray
{
public:
    xt::xarray<T> arr_;
    bool required_grad_;
    Function<T> *fun_;
    xt::xarray<T> arr_back_;
    std::vector<xccarray<T> *> arrs_src_;

    xccarray(const xt::xarray<T> &t, bool required_grad = false) : arr_{t}, required_grad_{required_grad}, fun_{nullptr}
    {
    }

    xccarray(const xt::xarray<T> &t, Function<T> *fun, const std::vector<xccarray<T> *> &arrs_src) : arr_{t}, required_grad_{true}, fun_{fun}, arrs_src_{arrs_src}
    {
    }

    void backward()
    {

        if (fun_ != nullptr)
            fun_->backward(arrs_src_);
    }
};



int main()
{
    xt::xarray<int> arr{1, -2, 3, -4, 5, -6, 7, -8, 9};
    xt::xarray<int> arr2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    xccarray<int> xcca{arr, true};
    auto a = Relu<int>::relu.forward({&xcca});
    auto b = Relu<int>::relu.forward({&a});
    b.backward();
    // // auto a = arr.reshape({3, 3});
    // // ;

    // // auto b = a.shape();

    // // auto result = xt::linalg::dot(arr, arr2);
    std::cout << "xcca" << xcca.arr_ << xcca.arr_back_ << "\n";
    std::cout << "a" << a.arr_ << a.arr_back_ << "\n";
    std::cout << "b" << b.arr_ << b.arr_back_ << "\n"; // << xt::adapt(b);

    xccarray<int> ap{arr};
    xccarray<int> bp{arr2};
    auto cp = Add<int>::add.forward({&ap, &bp});
    cp.backward();
    std::cout << "ap" << ap.arr_ << ap.arr_back_ << "\n";
    std::cout << "bp" << bp.arr_ << bp.arr_back_ << "\n";
    std::cout << "cp" << cp.arr_ << cp.arr_back_ << "\n";

    xccarray<int> am{arr};
    xccarray<int> bm{arr2};
    auto cm = Multiply<int>::multiply.forward({&am, &bm});
    cm.backward();
    std::cout << "am" << am.arr_ << am.arr_back_ << "\n";
    std::cout << "bm" << bm.arr_ << bm.arr_back_ << "\n";
    std::cout << "cm" << cm.arr_ << cm.arr_back_ << "\n";

    xccarray<int> ad{arr};
    xccarray<int> bd{arr2};
    auto cd = Dot<int>::dot.forward({&ad, &bd});
    cd.backward();
    std::cout << "ad" << ad.arr_ << ad.arr_back_ << "\n";
    std::cout << "bd" << bd.arr_ << bd.arr_back_ << "\n";
    std::cout << "cd" << cd.arr_ << cd.arr_back_ << "\n";

    xccarray<int> ar{arr};
    xccarray<int> br{arr2};
    auto cr = Dot<int>::dot.forward({&ar, &br});
    xccarray<int> rr{xt::xarray<int>(46.5)};
    
    auto rms = MSE<int>::mse.forward({&cr, &rr});
    rms.backward();
    std::cout << "ar" << ar.arr_ << ar.arr_back_ << "\n";
    std::cout << "br" << br.arr_ << br.arr_back_ << "\n";
    std::cout << "cr" << cr.arr_ << cr.arr_back_ << "\n";
    std::cout << "rr" << rr.arr_ << rr.arr_back_ << "\n";
    std::cout << "rms" << rms.arr_ << rms.arr_back_ << "\n";

    return 0;
}