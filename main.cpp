

#include <iostream>
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include <initializer_list>
#include <memory>

#include "xccarray.hpp"
#include "node.hpp"
#include "edge.hpp"
#include "function.hpp"
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

template <typename T>
class GraphNode;

int main()
{
    xt::xarray<float> arr{1, -2, 3, -4, 5, -6, 7, -8, 9};
    xt::xarray<float> arr2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    // xccarray<int> xcca{arr};
    // auto a = Relu<int>::relu.forward({&xcca});    
    // auto b = Relu<int>::relu.forward({a});
    // std::cout << b->node_->print() << "\n";

    // b->backward();
    // // auto a = arr.reshape({3, 3});
    // // ;

    // // auto b = a.shape();

    // // auto result = xt::linalg::dot(arr, arr2);
    // std::cout << "xcca" << xcca.arr_ << xcca.arr_back_ << "\n";
    // std::cout << "a" << a->arr_ << a->arr_back_ << "\n";
    // std::cout << "b" << b->arr_ << b->arr_back_ << "\n"; // << xt::adapt(b);

    // xccarray<int> ap{arr};
    // xccarray<int> bp{arr2};
    // auto cp = Add<int>::add.forward({&ap, &bp});
    // auto cpr = Relu<int>::relu.forward({cp});
    // std::cout << cpr->node_->print() << "\n";

    // cpr->backward();
    // std::cout << "ap" << ap.arr_ << ap.arr_back_ << "\n";
    // std::cout << "bp" << bp.arr_ << bp.arr_back_ << "\n";
    // std::cout << "cp" << cp->arr_ << cp->arr_back_ << "\n";
    // std::cout << "cpr" << cpr->arr_ << cpr->arr_back_ << "\n";

    xccarray<int> am{arr};
    xccarray<int> bm{arr2};
    auto cm = Multiply<int>::multiply.forward({&am, &bm});
    std::cout << cm->node_->print() << "\n";
    
    cm->backward();
    std::cout << "am" << am.arr_ << am.arr_back_ << "\n";
    std::cout << "bm" << bm.arr_ << bm.arr_back_ << "\n";
    std::cout << "cm" << cm->arr_ << cm->arr_back_ << "\n";

    // xccarray<int> ad{arr};
    // xccarray<int> bd{arr2};
    // auto cd = Dot<int>::dot.forward({&ad, &bd});
    // cd->backward();
    // std::cout << "ad" << ad.arr_ << ad.arr_back_ << "\n";
    // std::cout << "bd" << bd.arr_ << bd.arr_back_ << "\n";
    // std::cout << "cd" << cd->arr_ << cd->arr_back_ << "\n";

    xccarray<float> ar{arr};
    xccarray<float> br{arr2};
    auto cr = Dot<float>::dot.forward({&ar, &br});
    auto cru = Relu<float>::relu.forward({cr});
    xccarray<float> rr{xt::xarray<float>(46.5)};

     xccarray<float>* rms;
     if(1){
     rms=  MSE<float>::mse.forward({cru, &rr});

     }else{
     rms=  MSE<float>::mse.forward({cru, &rr});

     }
    std::cout << rms->node_->print() << "\n";

    rms->backward();
    std::cout << "ar" << ar.arr_ << ar.arr_back_ << "\n";
    std::cout << "br" << br.arr_ << br.arr_back_ << "\n";
    std::cout << "cr" << cr->arr_ << cr->arr_back_ << "\n";
    std::cout << "cru" << cru->arr_ << cru->arr_back_ << "\n";
    std::cout << "rr" << rr.arr_ << rr.arr_back_ << "\n";
    std::cout << "rms" << rms->arr_ << rms->arr_back_ << "\n";

    return 0;
}