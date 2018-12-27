#pragma once

// @generated by aten/src/ATen/gen.py

#include "ATen/Device.h"
#include "ATen/core/Layout.h"
#include "ATen/Scalar.h"
#include "ATen/ScalarType.h"
#include "ATen/SparseTensorRef.h"
#include "ATen/Storage.h"
#include "ATen/TensorAccessor.h"
#include "ATen/TensorBase.h"
#include "ATen/TensorImpl.h"
#include "ATen/core/optional.h"

namespace at {
struct Generator;
struct Type;
struct Tensor;
struct TensorOptions;
namespace detail {
void set_data(Tensor& tensor, Tensor new_data);
} // namespace detail
} // namespace at

namespace at {
// Tensor is a "generic" object holding a pointer to the underlying TensorImpl object, which
// has an embedded reference count. In this way, Tensor is similar to boost::intrusive_ptr.
//
// For example:
//
// void func(Tensor a) {
//   Tensor b = a;
//   ...
// }
//
// In this example, when we say Tensor b = a, we are creating a new object that points to the
// same underlying TensorImpl, and bumps its reference count. When b goes out of scope, the
// destructor decrements the reference count by calling release() on the TensorImpl it points to.
// The existing constructors, operator overloads, etc. take care to implement the correct semantics.
//
// Note that Tensor can also be NULL, i.e. it is not associated with any underlying TensorImpl, and
// special care must be taken to handle this.
struct AT_API Tensor : public detail::TensorBase {
  using TensorBase = detail::TensorBase;
  Tensor() : TensorBase() {}
  Tensor(TensorImpl * self, bool retain) : TensorBase(self, retain) {}
  Tensor(const TensorBase & rhs) : TensorBase(rhs) {}
  Tensor(const Tensor & rhs) = default;
  Tensor(Tensor && rhs) noexcept = default;

  // reimplemented from TensorBase so the return type is Tensor rather than TensorBase
  Tensor & operator=(Tensor && rhs) & {
    rhs.swap(*this);
    return *this;
  }
  Tensor & operator=(Tensor const & rhs) & {
      //Tensor ctor retains original rhs.pImpl
      //then rhs.pImpl is swapped with this->pImpl
      //finally Tensor dtor releases rhs.pImpl, which was originally this->pImpl
      Tensor(rhs).swap(*this);
      return *this;
  }

  inline Tensor & operator=(Tensor const & rhs) &&;
  Tensor & operator=(Scalar v) &&;
  const char * toString() const {
    return pImpl->toString();
  }
  IntList sizes() const {
    return pImpl->sizes();
  }
  IntList strides() const {
    return pImpl->strides();
  }
  int64_t ndimension() const {
    return dim();
  }
  Type & type() const {
    return pImpl->type();
  }
  const Storage& storage() const {
    return pImpl->storage();
  }
  inline Tensor toType(const Type & t, bool non_blocking=false) const;
  inline Tensor & copy_(const Tensor & src, bool non_blocking=false);
  inline Tensor toType(ScalarType t) const;
  inline Tensor toBackend(Backend b) const;

  /// New-style `to()` methods.
  /// NB: These methods are defined in TensorOptions.h.
  Tensor to(Device device, ScalarType dtype, bool non_blocking = false) const;
  Tensor to(ScalarType dtype, bool non_blocking = false) const;
  Tensor to(Device device, bool non_blocking = false) const;

  /// Returns true if the `Tensor` is actually a `torch::autograd::Variable`.
  /// Defined in Type.h because of include order issues.
  bool is_variable() const noexcept;

  /// Returns a `Tensor`'s layout. Defined in Type.h
  Layout layout() const noexcept;

  /// Returns a `Tensor`'s dtype (`ScalarType`). Defined in Type.h
  ScalarType dtype() const noexcept;

  /// Returns a `Tensor`'s device.
  Device device() const;

  /// Returns the `TensorOptions` corresponding to this `Tensor`. Defined in
  /// TensorOptions.h.
  TensorOptions options() const;

  template<typename T>
  T * data() const;

  // non-retaining
  TensorImpl * unsafeGetTensorImpl() const {
    return pImpl;
  }

  // Purposely not defined here to avoid inlining
  void print() const;

  //toLongData(), toFloatData() etc.
  #define TO_TYPE_DATA(T,name,_) \
  T * to##name##Data() const;
  AT_FORALL_SCALAR_TYPES(TO_TYPE_DATA)
  #undef TO_TYPE_DATA

  #define TO_C_TYPE(T,name,_) \
  T toC##name () const;
  AT_FORALL_SCALAR_TYPES(TO_C_TYPE)
  #undef TO_C_TYPE

  template<typename T, size_t N>
  TensorAccessor<T,N> accessor() const& {
    static_assert(N > 0, "accessor is used for indexing tensor, for scalars use *data<T>()");
    AT_CHECK(dim() == N, "expected ", N, " dims but tensor has ", dim());
    return TensorAccessor<T,N>(data<T>(),sizes().data(),strides().data());
  }
  template<typename T, size_t N>
  TensorAccessor<T,N> accessor() && = delete;

  Tensor operator-() const;
  Tensor& operator+=(const Tensor & other);
  Tensor& operator+=(Scalar other);
  Tensor& operator-=(const Tensor & other);
  Tensor& operator-=(Scalar other);
  Tensor& operator*=(const Tensor & other);
  Tensor& operator*=(Scalar other);
  Tensor& operator/=(const Tensor & other);
  Tensor& operator/=(Scalar other);
  Tensor operator[](Scalar index) const;
  Tensor operator[](Tensor index) const;
  Tensor operator[](int64_t index) const;

  Tensor cpu() const;
  Tensor cuda() const;

  // ~~~~~ Autograd API ~~~~~

  Tensor& set_requires_grad(bool requires_grad) {
    pImpl->set_requires_grad(requires_grad);
    return *this;
  }
  bool requires_grad() const {
    return pImpl->requires_grad();
  }

  Tensor& grad() {
    return pImpl->grad();
  }
  const Tensor& grad() const {
    return pImpl->grad();
  }

  Tensor detach() const {
    return pImpl->detach();
  }
  void detach_() {
    pImpl->detach_();
  }

  /// Computes the gradient of current tensor w.r.t. graph leaves.
  void backward(
      at::optional<Tensor> gradient = at::nullopt,
      bool keep_graph = false,
      bool create_graph = false);

  friend void detail::set_data(Tensor& tensor, Tensor new_data);

  // STOP.  Thinking of adding a method here, which only makes use
  // of other ATen methods?  Define it in native_functions.yaml.

  //example
  //Tensor * add(Tensor & b);
  int64_t storage_offset() const;
  Tensor & resize_(IntList size);
  Tensor & set_(Storage source);
  Tensor & set_(Storage source, int64_t storage_offset, IntList size, IntList stride={});
  Tensor & set_(const Tensor & source);
  Tensor & set_();
  Tensor & _fill_(Scalar value);
  Tensor & _fill_(const Tensor & value);
  bool is_contiguous() const;
  bool is_set_to(const Tensor & tensor) const;
  Tensor & masked_fill_(const Tensor & mask, Scalar value);
  Tensor & masked_fill_(const Tensor & mask, const Tensor & value);
  Tensor & masked_scatter_(const Tensor & mask, const Tensor & source);
  Tensor masked_select(const Tensor & mask) const;
  Tensor nonzero() const;
  Tensor contiguous() const;
  Tensor view(IntList size) const;
  Tensor index_select(int64_t dim, const Tensor & index) const;
  Tensor & _indexCopy_(int64_t dim, const Tensor & index, const Tensor & source);
  Tensor take(const Tensor & index) const;
  Tensor & put_(const Tensor & index, const Tensor & source, bool accumulate=false);
  Tensor & index_add_(int64_t dim, const Tensor & index, const Tensor & source);
  Tensor & index_fill_(int64_t dim, const Tensor & index, Scalar value);
  Tensor & index_fill_(int64_t dim, const Tensor & index, const Tensor & value);
  Tensor unfold(int64_t dimension, int64_t size, int64_t step) const;
  Tensor & scatter_(int64_t dim, const Tensor & index, const Tensor & src);
  Tensor & scatter_(int64_t dim, const Tensor & index, Scalar value);
  Tensor & scatter_add_(int64_t dim, const Tensor & index, const Tensor & src);
  Tensor gather(int64_t dim, const Tensor & index) const;
  void* data_ptr() const;
  bool equal(const Tensor & other) const;
  Tensor __and__(Scalar other) const;
  Tensor __and__(const Tensor & other) const;
  Tensor & __iand__(Scalar other);
  Tensor & __iand__(const Tensor & other);
  Tensor __or__(Scalar other) const;
  Tensor __or__(const Tensor & other) const;
  Tensor & __ior__(Scalar other);
  Tensor & __ior__(const Tensor & other);
  Tensor __xor__(Scalar other) const;
  Tensor __xor__(const Tensor & other) const;
  Tensor & __ixor__(Scalar other);
  Tensor & __ixor__(const Tensor & other);
  Tensor __lshift__(Scalar other) const;
  Tensor __lshift__(const Tensor & other) const;
  Tensor & __ilshift__(Scalar other);
  Tensor & __ilshift__(const Tensor & other);
  Tensor __rshift__(Scalar other) const;
  Tensor __rshift__(const Tensor & other) const;
  Tensor & __irshift__(Scalar other);
  Tensor & __irshift__(const Tensor & other);
  Tensor lt(Scalar other) const;
  Tensor lt(const Tensor & other) const;
  Tensor & lt_(Scalar other);
  Tensor & lt_(const Tensor & other);
  Tensor gt(Scalar other) const;
  Tensor gt(const Tensor & other) const;
  Tensor & gt_(Scalar other);
  Tensor & gt_(const Tensor & other);
  Tensor le(Scalar other) const;
  Tensor le(const Tensor & other) const;
  Tensor & le_(Scalar other);
  Tensor & le_(const Tensor & other);
  Tensor ge(Scalar other) const;
  Tensor ge(const Tensor & other) const;
  Tensor & ge_(Scalar other);
  Tensor & ge_(const Tensor & other);
  Tensor eq(Scalar other) const;
  Tensor eq(const Tensor & other) const;
  Tensor & eq_(Scalar other);
  Tensor & eq_(const Tensor & other);
  Tensor ne(Scalar other) const;
  Tensor ne(const Tensor & other) const;
  Tensor & ne_(Scalar other);
  Tensor & ne_(const Tensor & other);
  Tensor min(const Tensor & other) const;
  Tensor min() const;
  std::tuple<Tensor,Tensor> _th_min(int64_t dim, bool keepdim=false) const;
  Tensor max(const Tensor & other) const;
  Tensor max() const;
  std::tuple<Tensor,Tensor> _th_max(int64_t dim, bool keepdim=false) const;
  std::tuple<Tensor,Tensor> _th_kthvalue(int64_t k, int64_t dim=-1, bool keepdim=false) const;
  std::tuple<Tensor,Tensor> _th_mode(int64_t dim=-1, bool keepdim=false) const;
  Tensor median() const;
  std::tuple<Tensor,Tensor> _th_median(int64_t dim, bool keepdim=false) const;
  std::tuple<Tensor,Tensor> sort(int64_t dim=-1, bool descending=false) const;
  std::tuple<Tensor,Tensor> topk(int64_t k, int64_t dim=-1, bool largest=true, bool sorted=true) const;
  Tensor all() const;
  Tensor _th_all(int64_t dim, bool keepdim=false) const;
  Tensor any() const;
  Tensor _th_any(int64_t dim, bool keepdim=false) const;
  Tensor _abs() const;
  Tensor _th_sigmoid() const;
  Tensor _log() const;
  Tensor _log10() const;
  Tensor _log1p() const;
  Tensor _log2() const;
  Tensor lgamma() const;
  Tensor & lgamma_();
  Tensor digamma() const;
  Tensor & digamma_();
  Tensor polygamma(int64_t n) const;
  Tensor & polygamma_(int64_t n);
  Tensor _exp() const;
  Tensor _expm1() const;
  Tensor _cos() const;
  Tensor _acos() const;
  Tensor _cosh() const;
  Tensor _sin() const;
  Tensor _asin() const;
  Tensor _sinh() const;
  Tensor _tan() const;
  Tensor _atan() const;
  Tensor _th_tanh() const;
  Tensor _erf() const;
  Tensor _erfc() const;
  Tensor & erfinv_();
  Tensor erfinv() const;
  Tensor _sqrt() const;
  Tensor _rsqrt() const;
  Tensor _ceil() const;
  Tensor _floor() const;
  Tensor _round() const;
  Tensor _trunc() const;
  Tensor & frac_();
  Tensor frac() const;
  Tensor _th_var(int64_t dim, bool unbiased=true, bool keepdim=false) const;
  Tensor _th_var(bool unbiased=true) const;
  Tensor _th_std(int64_t dim, bool unbiased=true, bool keepdim=false) const;
  Tensor _th_std(bool unbiased=true) const;
  Tensor _th_norm(Scalar p, int64_t dim, bool keepdim=false) const;
  Tensor renorm(Scalar p, int64_t dim, Scalar maxnorm) const;
  Tensor & renorm_(Scalar p, int64_t dim, Scalar maxnorm);
  Tensor dist(const Tensor & other, Scalar p=2) const;
  Tensor reciprocal() const;
  Tensor & reciprocal_();
  Tensor neg() const;
  Tensor & neg_();
  Tensor atan2(const Tensor & other) const;
  Tensor & atan2_(const Tensor & other);
  Tensor pow(const Tensor & exponent) const;
  Tensor & pow_(Scalar exponent);
  Tensor & pow_(const Tensor & exponent);
  Tensor lerp(const Tensor & end, Scalar weight) const;
  Tensor & lerp_(const Tensor & end, Scalar weight);
  Tensor histc(int64_t bins=100, Scalar min=0, Scalar max=0) const;
  Tensor _sumall() const;
  Tensor _th_sum(int64_t dim, bool keepdim=false) const;
  Tensor _prodall() const;
  Tensor _th_prod(int64_t dim, bool keepdim=false) const;
  Tensor _cumsum(int64_t dim) const;
  Tensor _cumprod(int64_t dim) const;
  Tensor sign() const;
  Tensor & sign_();
  Tensor trace() const;
  Tensor fmod(Scalar other) const;
  Tensor fmod(const Tensor & other) const;
  Tensor & fmod_(Scalar other);
  Tensor & fmod_(const Tensor & other);
  Tensor remainder(Scalar other) const;
  Tensor remainder(const Tensor & other) const;
  Tensor & remainder_(Scalar other);
  Tensor & remainder_(const Tensor & other);
  Tensor _th_clamp(Scalar min, Scalar max) const;
  Tensor _th_clamp_min(Scalar min) const;
  Tensor _th_clamp_max(Scalar max) const;
  Tensor _dot(const Tensor & tensor) const;
  Tensor tril(int64_t diagonal=0) const;
  Tensor & tril_(int64_t diagonal=0);
  Tensor triu(int64_t diagonal=0) const;
  Tensor & triu_(int64_t diagonal=0);
  Tensor cross(const Tensor & other, int64_t dim=-1) const;
  Tensor diag(int64_t diagonal=0) const;
  Tensor _addmv(const Tensor & mat, const Tensor & vec, Scalar beta=1, Scalar alpha=1) const;
  Tensor & _addmv_(const Tensor & mat, const Tensor & vec, Scalar beta=1, Scalar alpha=1);
  Tensor _addr(const Tensor & vec1, const Tensor & vec2, Scalar beta=1, Scalar alpha=1) const;
  Tensor & _addr_(const Tensor & vec1, const Tensor & vec2, Scalar beta=1, Scalar alpha=1);
  Tensor _ger(const Tensor & vec2) const;
  Tensor _mv(const Tensor & vec) const;
  Tensor _mm(const Tensor & mat2) const;
  Tensor bmm(const Tensor & mat2) const;
  Tensor addbmm(const Tensor & batch1, const Tensor & batch2, Scalar beta=1, Scalar alpha=1) const;
  Tensor & addbmm_(const Tensor & batch1, const Tensor & batch2, Scalar beta=1, Scalar alpha=1);
  Tensor baddbmm(const Tensor & batch1, const Tensor & batch2, Scalar beta=1, Scalar alpha=1) const;
  Tensor & baddbmm_(const Tensor & batch1, const Tensor & batch2, Scalar beta=1, Scalar alpha=1);
  Tensor addcmul(const Tensor & tensor1, const Tensor & tensor2, Scalar value=1) const;
  Tensor & addcmul_(const Tensor & tensor1, const Tensor & tensor2, Scalar value=1);
  Tensor addcdiv(const Tensor & tensor1, const Tensor & tensor2, Scalar value=1) const;
  Tensor & addcdiv_(const Tensor & tensor1, const Tensor & tensor2, Scalar value=1);
  std::tuple<Tensor,Tensor> _gesv_single(const Tensor & A) const;
  std::tuple<Tensor,Tensor> gels(const Tensor & A) const;
  std::tuple<Tensor,Tensor> trtrs(const Tensor & A, bool upper=true, bool transpose=false, bool unitriangular=false) const;
  std::tuple<Tensor,Tensor> symeig(bool eigenvectors=false, bool upper=true) const;
  std::tuple<Tensor,Tensor> eig(bool eigenvectors=false) const;
  std::tuple<Tensor,Tensor,Tensor> svd(bool some=true) const;
  Tensor _getri() const;
  Tensor potrf(bool upper=true) const;
  Tensor potrs(const Tensor & input2, bool upper=true) const;
  Tensor potri(bool upper=true) const;
  std::tuple<Tensor,Tensor> pstrf(bool upper=true, Scalar tol=-1) const;
  std::tuple<Tensor,Tensor> qr() const;
  std::tuple<Tensor,Tensor> geqrf() const;
  Tensor orgqr(const Tensor & input2) const;
  Tensor ormqr(const Tensor & input2, const Tensor & input3, bool left=true, bool transpose=false) const;
  std::tuple<Tensor,Tensor> btrifact(bool pivot=true) const;
  std::tuple<Tensor,Tensor,Tensor> btrifact_with_info(bool pivot=true) const;
  Tensor btrisolve(const Tensor & LU_data, const Tensor & LU_pivots) const;
  Tensor & random_(int64_t from, int64_t to, Generator * generator=nullptr);
  Tensor & random_(int64_t to, Generator * generator=nullptr);
  Tensor & random_(Generator * generator=nullptr);
  Tensor multinomial(int64_t num_samples, bool replacement=false, Generator * generator=nullptr) const;
  Tensor & uniform_(double from=0, double to=1, Generator * generator=nullptr);
  Tensor & normal_(double mean=0, double std=1, Generator * generator=nullptr);
  Tensor & cauchy_(double median=0, double sigma=1, Generator * generator=nullptr);
  Tensor & log_normal_(double mean=1, double std=2, Generator * generator=nullptr);
  Tensor & exponential_(double lambd=1, Generator * generator=nullptr);
  Tensor & geometric_(double p, Generator * generator=nullptr);
  Tensor & _bernoulli_(double p, Generator * generator=nullptr);
  Tensor _th_bernoulli(Generator * generator=nullptr) const;
  Tensor & _copy_ignoring_overlaps_(const Tensor & src);
  Tensor _cast_Byte(bool non_blocking=false) const;
  Tensor _cast_Char(bool non_blocking=false) const;
  Tensor _cast_Double(bool non_blocking=false) const;
  Tensor _cast_Float(bool non_blocking=false) const;
  Tensor _cast_Int(bool non_blocking=false) const;
  Tensor _cast_Long(bool non_blocking=false) const;
  Tensor _cast_Short(bool non_blocking=false) const;
  Tensor _cast_Half(bool non_blocking=false) const;
  std::tuple<Tensor,Tensor> _fused_dropout(double p, Generator * generator=nullptr) const;
  Tensor _masked_scale(const Tensor & mask, double scale) const;
  Tensor abs() const;
  Tensor & abs_();
  Tensor acos() const;
  Tensor & acos_();
  Tensor add(const Tensor & other, Scalar alpha=1) const;
  Tensor & add_(const Tensor & other, Scalar alpha=1);
  Tensor add(Scalar other, Scalar alpha=1) const;
  Tensor & add_(Scalar other, Scalar alpha=1);
  Tensor addmv(const Tensor & mat, const Tensor & vec, Scalar beta=1, Scalar alpha=1) const;
  Tensor & addmv_(const Tensor & mat, const Tensor & vec, Scalar beta=1, Scalar alpha=1);
  Tensor addr(const Tensor & vec1, const Tensor & vec2, Scalar beta=1, Scalar alpha=1) const;
  Tensor & addr_(const Tensor & vec1, const Tensor & vec2, Scalar beta=1, Scalar alpha=1);
  Tensor all(int64_t dim, bool keepdim=false) const;
  bool allclose(const Tensor & other, double rtol=1e-05, double atol=1e-08, bool equal_nan=false) const;
  Tensor any(int64_t dim, bool keepdim=false) const;
  Tensor argmax(int64_t dim, bool keepdim=false) const;
  Tensor argmax() const;
  Tensor _argmax(int64_t dim, bool keepdim=false) const;
  Tensor argmin(int64_t dim, bool keepdim=false) const;
  Tensor argmin() const;
  Tensor _argmin(int64_t dim, bool keepdim=false) const;
  Tensor as_strided(IntList size, IntList stride) const;
  Tensor & as_strided_(IntList size, IntList stride);
  Tensor as_strided(IntList size, IntList stride, int64_t storage_offset) const;
  Tensor & as_strided_(IntList size, IntList stride, int64_t storage_offset);
  Tensor asin() const;
  Tensor & asin_();
  Tensor atan() const;
  Tensor & atan_();
  Tensor bernoulli(const Tensor & p, Generator * generator=nullptr) const;
  Tensor bernoulli(double p, Generator * generator=nullptr) const;
  Tensor bernoulli() const;
  Tensor & bernoulli_(const Tensor & p, Generator * generator=nullptr);
  Tensor & bernoulli_(double p, Generator * generator=nullptr);
  Tensor & bernoulli_();
  Tensor bincount(const Tensor & weights={}, int64_t minlength=0) const;
  Tensor ceil() const;
  Tensor & ceil_();
  std::vector<Tensor> chunk(int64_t chunks, int64_t dim=0) const;
  Tensor clamp(Scalar min, Scalar max) const;
  Tensor & clamp_(Scalar min, Scalar max);
  Tensor clamp_max(Scalar max) const;
  Tensor & clamp_max_(Scalar max);
  Tensor clamp_min(Scalar min) const;
  Tensor & clamp_min_(Scalar min);
  Tensor cos() const;
  Tensor & cos_();
  Tensor cosh() const;
  Tensor & cosh_();
  Tensor cumsum(int64_t dim, ScalarType dtype) const;
  Tensor cumsum(int64_t dim) const;
  Tensor cumprod(int64_t dim, ScalarType dtype) const;
  Tensor cumprod(int64_t dim) const;
  Tensor det() const;
  Tensor diagflat(int64_t offset=0) const;
  Tensor diagonal(int64_t offset=0, int64_t dim1=0, int64_t dim2=1) const;
  Tensor div(const Tensor & other) const;
  Tensor & div_(const Tensor & other);
  Tensor div(Scalar other) const;
  Tensor & div_(Scalar other);
  Tensor dot(const Tensor & tensor) const;
  Tensor erf() const;
  Tensor & erf_();
  Tensor erfc() const;
  Tensor & erfc_();
  Tensor exp() const;
  Tensor & exp_();
  Tensor expm1() const;
  Tensor & expm1_();
  Tensor expand(IntList size, bool implicit=false) const;
  Tensor expand_as(const Tensor & other) const;
  Tensor flatten(int64_t start_dim=0, int64_t end_dim=-1) const;
  Tensor & fill_(Scalar value);
  Tensor & fill_(const Tensor & value);
  Tensor floor() const;
  Tensor & floor_();
  Tensor ger(const Tensor & vec2) const;
  std::tuple<Tensor,Tensor> gesv(const Tensor & A) const;
  std::tuple<Tensor,Tensor> _gesv_helper(const Tensor & A) const;
  Tensor fft(int64_t signal_ndim, bool normalized=false) const;
  Tensor ifft(int64_t signal_ndim, bool normalized=false) const;
  Tensor rfft(int64_t signal_ndim, bool normalized=false, bool onesided=true) const;
  Tensor irfft(int64_t signal_ndim, bool normalized=false, bool onesided=true, IntList signal_sizes={}) const;
  Tensor _fft_with_size(int64_t signal_ndim, bool complex_input, bool complex_output, bool inverse, IntList checked_signal_sizes, bool normalized, bool onesided, IntList output_sizes) const;
  Tensor index(TensorList indices) const;
  Tensor & index_copy_(int64_t dim, const Tensor & index, const Tensor & source);
  Tensor index_put(TensorList indices, const Tensor & values) const;
  Tensor & index_put_(TensorList indices, const Tensor & values);
  Tensor inverse() const;
  Tensor isclose(const Tensor & other, double rtol=1e-05, double atol=1e-08, bool equal_nan=false) const;
  bool is_cuda() const;
  bool is_distributed() const;
  bool is_floating_point() const;
  bool is_nonzero() const;
  bool is_same_size(const Tensor & other) const;
  bool is_signed() const;
  bool is_sparse() const;
  std::tuple<Tensor,Tensor> kthvalue(int64_t k, int64_t dim=-1, bool keepdim=false) const;
  Tensor log() const;
  Tensor & log_();
  Tensor log10() const;
  Tensor & log10_();
  Tensor log1p() const;
  Tensor & log1p_();
  Tensor log2() const;
  Tensor & log2_();
  Tensor logdet() const;
  Tensor log_softmax(int64_t dim) const;
  Tensor logsumexp(int64_t dim, bool keepdim=false) const;
  Tensor matmul(const Tensor & other) const;
  std::tuple<Tensor,Tensor> max(int64_t dim, bool keepdim=false) const;
  Tensor max_values(int64_t dim, bool keepdim=false) const;
  Tensor mean(ScalarType dtype) const;
  Tensor mean() const;
  Tensor mean(int64_t dim, bool keepdim, ScalarType dtype) const;
  Tensor mean(int64_t dim, bool keepdim=false) const;
  Tensor mean(int64_t dim, ScalarType dtype) const;
  std::tuple<Tensor,Tensor> median(int64_t dim, bool keepdim=false) const;
  std::tuple<Tensor,Tensor> min(int64_t dim, bool keepdim=false) const;
  Tensor min_values(int64_t dim, bool keepdim=false) const;
  Tensor mm(const Tensor & mat2) const;
  std::tuple<Tensor,Tensor> mode(int64_t dim=-1, bool keepdim=false) const;
  Tensor mul(const Tensor & other) const;
  Tensor & mul_(const Tensor & other);
  Tensor mul(Scalar other) const;
  Tensor & mul_(Scalar other);
  Tensor mv(const Tensor & vec) const;
  Tensor mvlgamma(int64_t p) const;
  Tensor & mvlgamma_(int64_t p);
  Tensor narrow(int64_t dim, int64_t start, int64_t length) const;
  Tensor permute(IntList dims) const;
  Tensor pin_memory() const;
  Tensor pinverse(double rcond=1e-15) const;
  Tensor repeat(IntList repeats) const;
  Tensor reshape(IntList shape) const;
  Tensor reshape_as(const Tensor & other) const;
  Tensor round() const;
  Tensor & round_();
  Tensor relu() const;
  Tensor & relu_();
  Tensor hardshrink(Scalar lambd=0.5) const;
  Tensor hardshrink_backward(const Tensor & grad_out, Scalar lambd) const;
  Tensor rsqrt() const;
  Tensor & rsqrt_();
  Tensor select(int64_t dim, int64_t index) const;
  Tensor sigmoid() const;
  Tensor & sigmoid_();
  Tensor sin() const;
  Tensor & sin_();
  Tensor sinh() const;
  Tensor & sinh_();
  int64_t size(int64_t dim) const;
  Tensor slice(int64_t dim=0, int64_t start=0, int64_t end=9223372036854775807, int64_t step=1) const;
  std::tuple<Tensor,Tensor> slogdet() const;
  Tensor smm(const Tensor & mat2) const;
  Tensor softmax(int64_t dim) const;
  std::vector<Tensor> split(int64_t split_size, int64_t dim=0) const;
  std::vector<Tensor> split_with_sizes(IntList split_sizes, int64_t dim=0) const;
  Tensor squeeze() const;
  Tensor squeeze(int64_t dim) const;
  Tensor & squeeze_();
  Tensor & squeeze_(int64_t dim);
  Tensor sspaddmm(const Tensor & mat1, const Tensor & mat2, Scalar beta=1, Scalar alpha=1) const;
  Tensor stft(int64_t n_fft, int64_t hop_length, int64_t win_length, const Tensor & window={}, bool normalized=false, bool onesided=true) const;
  int64_t stride(int64_t dim) const;
  Tensor sum(ScalarType dtype) const;
  Tensor sum() const;
  Tensor _sum() const;
  Tensor sum(IntList dim, bool keepdim, ScalarType dtype) const;
  Tensor sum(IntList dim, bool keepdim=false) const;
  Tensor sum(IntList dim, ScalarType dtype) const;
  Tensor _sum(IntList dim, bool keepdim=false) const;
  Tensor sqrt() const;
  Tensor & sqrt_();
  Tensor std(bool unbiased=true) const;
  Tensor std(int64_t dim, bool unbiased=true, bool keepdim=false) const;
  Tensor prod(ScalarType dtype) const;
  Tensor prod() const;
  Tensor _prod() const;
  Tensor prod(int64_t dim, bool keepdim, ScalarType dtype) const;
  Tensor prod(int64_t dim, bool keepdim=false) const;
  Tensor prod(int64_t dim, ScalarType dtype) const;
  Tensor _prod(int64_t dim, bool keepdim=false) const;
  Tensor t() const;
  Tensor & t_();
  Tensor tan() const;
  Tensor & tan_();
  Tensor tanh() const;
  Tensor & tanh_();
  Tensor transpose(int64_t dim0, int64_t dim1) const;
  Tensor & transpose_(int64_t dim0, int64_t dim1);
  Tensor flip(IntList dims) const;
  Tensor rot90(int64_t k=1, IntList dims={0,1}) const;
  Tensor trunc() const;
  Tensor & trunc_();
  Tensor type_as(const Tensor & other) const;
  std::tuple<Tensor,Tensor> _unique(bool sorted=false, bool return_inverse=false) const;
  Tensor unsqueeze(int64_t dim) const;
  Tensor & unsqueeze_(int64_t dim);
  Tensor var(bool unbiased=true) const;
  Tensor var(int64_t dim, bool unbiased=true, bool keepdim=false) const;
  Tensor view_as(const Tensor & other) const;
  Tensor where(const Tensor & condition, const Tensor & other) const;
  Tensor _s_where(const Tensor & condition, const Tensor & other) const;
  Tensor _standard_gamma_grad(const Tensor & output) const;
  Tensor _standard_gamma(Generator * generator=nullptr) const;
  Tensor norm(Scalar p=2) const;
  Tensor norm(Scalar p, int64_t dim, bool keepdim=false) const;
  Tensor clone() const;
  Tensor & resize_as_(const Tensor & the_template);
  Tensor pow(Scalar exponent) const;
  Tensor & zero_();
  Tensor sub(const Tensor & other, Scalar alpha=1) const;
  Tensor & sub_(const Tensor & other, Scalar alpha=1);
  Tensor sub(Scalar other, Scalar alpha=1) const;
  Tensor & sub_(Scalar other, Scalar alpha=1);
  Tensor addmm(const Tensor & mat1, const Tensor & mat2, Scalar beta=1, Scalar alpha=1) const;
  Tensor & addmm_(const Tensor & mat1, const Tensor & mat2, Scalar beta=1, Scalar alpha=1);
  Tensor & sparse_resize_(IntList size, int64_t sparseDims, int64_t denseDims);
  Tensor & sparse_resize_and_clear_(IntList size, int64_t sparseDims, int64_t denseDims);
  Tensor _sparse_mask(SparseTensorRef mask) const;
  Tensor to_dense() const;
  int64_t _sparseDims() const;
  int64_t _dimI() const;
  int64_t _denseDims() const;
  int64_t _dimV() const;
  int64_t _nnz() const;
  Tensor coalesce() const;
  bool is_coalesced() const;
  Tensor _indices() const;
  Tensor _values() const;
  int64_t numel() const;
  std::vector<Tensor> unbind(int64_t dim=0) const;
  int64_t get_device() const;
  Scalar _local_scalar() const;

  template <typename F, typename... Args>
  auto m(F func, Args&&... params) const -> decltype(func(*this, std::forward<Args>(params)...)) {
    return func(*this, std::forward<Args>(params)...);
  }

  friend struct WeakTensor;
};

struct AT_API WeakTensor : public detail::WeakTensorBase {
  using WeakTensorBase = detail::WeakTensorBase;
  WeakTensor() : WeakTensorBase() {}
  WeakTensor(TensorImpl * self, bool retain) : WeakTensorBase(self, retain) {}
  WeakTensor(const WeakTensor & rhs) = default;
  WeakTensor(WeakTensor && rhs) noexcept = default;
  WeakTensor(const Tensor& t) : WeakTensorBase(t.pImpl, true) {}

  // reimplemented from TensorBase so the return type is WeakTensor rather than TensorBase
  WeakTensor & operator=(WeakTensor && rhs) & {
    rhs.swap(*this);
    return *this;
  }
  WeakTensor & operator=(WeakTensor const & rhs) & {
    //Tensor ctor retains original rhs.pImpl
    //then rhs.pImpl is swapped with this->pImpl
    //finally Tensor dtor releases rhs.pImpl, which was originally this->pImpl
    WeakTensor(rhs).swap(*this);
    return *this;
  }

  WeakTensor & operator=(const Tensor& t) {
    WeakTensor(t.pImpl, true).swap(*this);
    return *this;
  }

  // non-retaining
  TensorImpl * unsafeGetTensorImpl() const {
    return pImpl;
  }

  // XXX: this can return undefined tensors
  // Ideally it would be at::optional<Tensor>, but MSVC is too cool for that
  Tensor lock() const {
    return pImpl->weak_lock() ? Tensor(pImpl, false) : Tensor();
  }
};

namespace detail {
inline void set_data(Tensor& tensor, Tensor new_data) {
  tensor.pImpl->set_data(new_data);
}
} // namespace detail
} // namespace at