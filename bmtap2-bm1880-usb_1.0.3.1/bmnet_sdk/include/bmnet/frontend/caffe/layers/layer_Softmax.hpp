/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_SOFTMAX_H_
#define _CAFFE_LAYER_SOFTMAX_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class SoftmaxLayer : public CaffeLayer {
 public:
  explicit SoftmaxLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~SoftmaxLayer() override = default;

  std::string layer_name() override { return std::string("Softmax"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
