

#include <iostream>
#include "xtensor/containers/xarray.hpp"
#include "xtensor/containers/xadapt.hpp"
#include "xtensor/io/xio.hpp"
#include <xtensor-blas/xlinalg.hpp>

#include <sstream>
#include <string>

#include <initializer_list>
#include <memory>

#include "xcctensor.hpp"
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
class xcctensor;

template <typename T>
class Function;

template <typename T>
class GraphNode;

using namespace std;

int main()
{
    Tensor<float> a = make_tensor<float>({1, -2, 3, -4, 5, -6, 7, -8, 9});
    Tensor<float> b = make_tensor<float>({1, 2, 3, 4, 5, 6, 7, 8, 9});
    Tensor<float> c = make_tensor<float>({-10, -8, -6, -4, -2, 0, 2, 4, 6});
    Tensor<float> d = make_tensor<float>({-1, -2, -3, -4, -5, -6, -7, -8, -9});
    Tensor<float> e = a + c;
    Tensor<float> f = b - d;
    Tensor<float> g = dot(e, f);
    Tensor<float> h = relu(g);
    Tensor<float> r = make_tensor<float>({151.5});
    Tensor<float> i = mse(h, r);

    std::cout << "The Computational graph constructed\n";
    std::cout << i->node_->print() << "\n";
    
    i->backward();
    std::cout << "a" << " " << a->arr_ << a->arr_back_ << "\n";
    std::cout << "b" << " " << b->arr_ << b->arr_back_ << "\n";
    std::cout << "c" << " " << c->arr_ << c->arr_back_ << "\n";
    std::cout << "d" << " " << d->arr_ << d->arr_back_ << "\n";
    std::cout << "e" << " " << e->arr_ << e->arr_back_ << "\n";
    std::cout << "f" << " " << f->arr_ << f->arr_back_ << "\n";
    std::cout << "g" << " " << g->arr_ << g->arr_back_ << "\n";
    std::cout << "h" << " " << h->arr_ << h->arr_back_ << "\n";
    std::cout << "i" << " " << i->arr_ << i->arr_back_ << "\n";
    return 0;
}
// int main()
// {
//     xt::xarray<int> arr{1, -2, 3, -4, 5, -6, 7, -8, 9};
//     xt::xarray<int> arr2{1, 2, 3, 4, 5, 6, 7, 8, 9};
//     Tensor<int> xcca = make_tensor<int>(arr);

//     Tensor<int> a = relu(xcca);
//     Tensor<int> b = relu(a);
//     std::cout << b->node_->print() << "\n";

//     b->backward();

//     std::cout << "xcca" << xcca->arr_ << xcca->arr_back_ << "\n";
//     std::cout << "a" << a->arr_ << a->arr_back_ << "\n";
//     std::cout << "b" << b->arr_ << b->arr_back_ << "\n";

//     Tensor<int> ap = make_tensor<int>(arr);
//     Tensor<int> bp = make_tensor<int>(arr2);
//     Tensor<int> cp = ap + bp;
//     Tensor<int> cpr = relu(cp);
//     std::cout << cpr->node_->print() << "\n";

//     cpr->backward();
//     std::cout << "ap" << ap->arr_ << ap->arr_back_ << "\n";
//     std::cout << "bp" << bp->arr_ << bp->arr_back_ << "\n";
//     std::cout << "cp" << cp->arr_ << cp->arr_back_ << "\n";
//     std::cout << "cpr" << cpr->arr_ << cpr->arr_back_ << "\n";

//     Tensor<float> am = make_tensor<float>(arr);
//     Tensor<float> bm = make_tensor<float>(arr2);
//     Tensor<float> cm = multiply(am, bm);
//     std::cout << cm->node_->print() << "\n";

//     cm->backward();
//     std::cout << "am" << am->arr_ << am->arr_back_ << "\n";
//     std::cout << "bm" << bm->arr_ << bm->arr_back_ << "\n";
//     std::cout << "cm" << cm->arr_ << cm->arr_back_ << "\n";

//     Tensor<float> ad = make_tensor<float>(arr);
//     Tensor<float> bd = make_tensor<float>(arr2);
//     auto t = bd + cm;
//     auto cd = dot(cm - ad, bd + cm);
//     std::cout << cd->node_->print() << "\n";

//     cd->backward();
//     std::cout << "am" << am->arr_ << am->arr_back_ << "\n";
//     std::cout << "bm" << bm->arr_ << bm->arr_back_ << "\n";
//     std::cout << "ad" << ad->arr_ << ad->arr_back_ << "\n";
//     std::cout << "bd" << bd->arr_ << bd->arr_back_ << "\n";
//     std::cout << "cd" << cd->arr_ << cd->arr_back_ << "\n";

//     Tensor<float> ar = make_tensor<float>(arr);
//     Tensor<float> br = make_tensor<float>(arr2);
//     auto cr = dot(ar, br);
//     auto cru = relu(cr);
//     Tensor<float> rr = make_tensor<float>(arr);

//     Tensor<float> rms;
//     if (1)
//     {
//         rms = mse(cru, rr);
//     }
//     else
//     {
//         rms = mse(cru, rr);
//     }
//     std::cout << rms->node_->print() << "\n";

//     rms->backward();
//     std::cout << "ar" << ar->arr_ << ar->arr_back_ << "\n";
//     std::cout << "br" << br->arr_ << br->arr_back_ << "\n";
//     std::cout << "cr" << cr->arr_ << cr->arr_back_ << "\n";
//     std::cout << "cru" << cru->arr_ << cru->arr_back_ << "\n";
//     std::cout << "rr" << rr->arr_ << rr->arr_back_ << "\n";
//     std::cout << "rms" << rms->arr_ << rms->arr_back_ << "\n";

//     return 0;
// }