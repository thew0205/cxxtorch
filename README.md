# CXXTorch

Lightweight C++ framework for edge training through computational graph construction and backpropagation.

## Overview

CXXTorch enables on-device machine learning training by building dynamic computational graphs and executing backpropagation efficiently on resource-constrained environments.

## Current Features

### Computational Graph
- **Graph Construction**: Automatic tracking of operations and tensor dependencies
- **Supported Operations**:
    - Arithmetic: Multiply, Dot product
    - Activation: ReLU
    - Loss: Mean Squared Error (MSE)

### Backpropagation
- Graph traversal for gradient computation
- Automatic differentiation through operation chains
- Memory-efficient gradient accumulation

## Architecture

```
Input Tensors
        ↓
[Operation Nodes]
        ↓
Output Node
        ↓
Backpropagation Traversal
        ↓
Gradient Computation
```

## Use Cases

- Edge device training and fine-tuning
- On-device model adaptation
- Low-latency inference with learning capabilities

## Getting Started

*(Documentation in progress)*

---

**Status**: Early development - Computational graph and backpropagation core implementation
## Sample Execution

The following is a sample execution demonstrating the computational graph and operations:

```
|--xarr:  2.25 @ 0x6069ecf76a30
  |
  mse
  |
  |--xarr:  45. @ 0x6069ecf76750
    |
    relu
    |
    |--xarr:  45. @ 0x6069ecf76470
      |
      dot
      |
      |--xarr: { 1., -2.,  3., -4.,  5., -6.,  7., -8.,  9.} @ 0x7ffef698d150
      |--xarr: { 1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9.} @ 0x7ffef698d340
  |--xarr:  46.5 @ 0x7ffef698d530

ar{ 1., -2.,  3., -4.,  5., -6.,  7., -8.,  9.}{ -3.,  -6.,  -9., -12., -15., -18., -21., -24., -27.}
br{ 1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9.}{ -3.,   6.,  -9.,  12., -15.,  18., -21.,  24., -27.}
cr 45.-3.
cru 45.-3.
rr 46.5 3.
rms 2.25 0.
```