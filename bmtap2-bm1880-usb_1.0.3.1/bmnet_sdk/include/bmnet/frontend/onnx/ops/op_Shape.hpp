/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _ONNX_LAYER_SHAPE_H_
#define _ONNX_LAYER_SHAPE_H_

#include <bmnet/frontend/onnx/OnnxFrontendContext.hpp>
#include <bmnet/frontend/onnx/OnnxOperator.hpp>

namespace bmnet {

class ShapeOp : public OnnxOperator {
 public:
  explicit ShapeOp(FrontendContext *ctx) : OnnxOperator(ctx) {}
  ShapeOp(FrontendContext *ctx, const ONNX_NAMESPACE::Node *pOnnxNode)
      : OnnxOperator(ctx, pOnnxNode) {}
  ~ShapeOp() override = default;

  std::string layer_name() override { return std::string("Shape"); }

  void dump() override;
  void setup(TensorOp *op) override;
  void codegen(TensorOp *op) override;
  OnnxOperator *makeOp(const ONNX_NAMESPACE::Node *node) override;
};

}  // namespace bmnet

#endif /* _ONNX_LAYER_SHAPE_H_ */
