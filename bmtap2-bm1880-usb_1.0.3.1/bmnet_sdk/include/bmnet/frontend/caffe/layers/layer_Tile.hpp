/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _CAFFE_LAYER_TILE_H_
#define _CAFFE_LAYER_TILE_H_

#include <bmnet/frontend/caffe/CaffeFrontendContext.hpp>
#include <bmnet/frontend/caffe/CaffeLayer.hpp>

namespace bmnet {

class TileLayer : public CaffeLayer {
 public:
  explicit TileLayer(FrontendContext *ctx) : CaffeLayer(ctx) {}
  ~TileLayer() override = default;

  std::string layer_name() override { return std::string("Tile"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;

 private:
};

}  // namespace bmnet
#endif
