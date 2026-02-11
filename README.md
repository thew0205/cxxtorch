# CXXTorch

A lightweight C++ framework for **on-device training** using dynamic computational graph construction and automatic differentiation.

CXXTorch is designed for resource-constrained environments where models must **learn, adapt, and run locally**.

---

## Overview

CXXTorch builds a dynamic computation graph as tensor operations are executed.  
During the backward pass, the graph is traversed in reverse to compute gradients using automatic differentiation.

The goal is to provide PyTorch-like learning capability while remaining suitable for embedded and edge systems.

---

## Current Features

### Computational Graph
- Automatic tracking of tensor dependencies
- Node-based representation of operations
- Graph introspection and printable structure

### Operations
- **Arithmetic**: addition, subtraction, multiply, dot
- **Activation**: ReLU
- **Loss**: Mean Squared Error (MSE)

### Backpropagation
- Reverse graph traversal
- Gradient propagation across operation chains
- Accumulation of gradients at tensors

---

## Architecture
Each tensor owns:
- its data
- its gradient
- its gradient buffer
- the node that produced it

---

## Use Cases

- Edge training and personalization  
- On-device fine-tuning  
- Adaptive systems with low latency  
- Research / education on autograd internals  

---

## Project Status

⚠️ Early development.  
Core computational graph and backpropagation engine are functional, and the operator set is expanding.

---

## Sample Execution

Example demonstrating graph construction, printing, and gradient computation.

```cpp
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

    std::cout << "a " << a->arr_ << a->arr_back_ << "\n";
    std::cout << "b " << b->arr_ << b->arr_back_ << "\n";
    std::cout << "c " << c->arr_ << c->arr_back_ << "\n";
    std::cout << "d " << d->arr_ << d->arr_back_ << "\n";
    std::cout << "e " << e->arr_ << e->arr_back_ << "\n";
    std::cout << "f " << f->arr_ << f->arr_back_ << "\n";
    std::cout << "g " << g->arr_ << g->arr_back_ << "\n";
    std::cout << "h " << h->arr_ << h->arr_back_ << "\n";
    std::cout << "i " << i->arr_ << i->arr_back_ << "\n";

    return 0;
}
```

Output generated with the generated computational graph.
```
The Computational graph constructed
|--xarr:  2.25 @ 0x59b616f01d40
  |
  mse
  |
  |--xarr:  150. @ 0x59b616f01800
    |
    relu
    |
    |--xarr:  150. @ 0x59b616f01490
      |
      dot
      |
      |--xarr: { -9., -10.,  -3.,  -8.,   3.,  -6.,   9.,  -4.,  15.} @ 0x59b616f00df0
        |
        add
        |
        |--xarr: { 1., -2.,  3., -4.,  5., -6.,  7., -8.,  9.} @ 0x59b616f002f0
        |--xarr: {-10.,  -8.,  -6.,  -4.,  -2.,   0.,   2.,   4.,   6.} @ 0x59b616f007b0
      |--xarr: {  2.,   4.,   6.,   8.,  10.,  12.,  14.,  16.,  18.} @ 0x59b616f01180
        |
        subtract
        |
        |--xarr: { 1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9.} @ 0x59b616f00550
        |--xarr: {-1., -2., -3., -4., -5., -6., -7., -8., -9.} @ 0x59b616f00a10
  |--xarr: { 151.5} @ 0x59b616f01a70

a { 1., -2.,  3., -4.,  5., -6.,  7., -8.,  9.}{ -6., -12., -18., -24., -30., -36., -42., -48., -54.}
b { 1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9.}{ 27.,  30.,   9.,  24.,  -9.,  18., -27.,  12., -45.}
c {-10.,  -8.,  -6.,  -4.,  -2.,   0.,   2.,   4.,   6.}{ -6., -12., -18., -24., -30., -36., -42., -48., -54.}
d {-1., -2., -3., -4., -5., -6., -7., -8., -9.}{-27., -30.,  -9., -24.,   9., -18.,  27., -12.,  45.}
e { -9., -10.,  -3.,  -8.,   3.,  -6.,   9.,  -4.,  15.}{ -6., -12., -18., -24., -30., -36., -42., -48., -54.}
f {  2.,   4.,   6.,   8.,  10.,  12.,  14.,  16.,  18.}{ 27.,  30.,   9.,  24.,  -9.,  18., -27.,  12., -45.}
g  150.{-3.}
h  150.{-3.}
i  2.25 0.
```

## Roadmap
- Planned improvements include:
- More tensor operations
- Broadcasting support
- Memory optimization / arena allocators
- Optimizers (SGD, Adam)
- Static graph / compile-time execution options
- Better device abstraction