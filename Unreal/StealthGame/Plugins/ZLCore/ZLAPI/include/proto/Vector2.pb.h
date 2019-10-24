// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Vector2.proto

#ifndef PROTOBUF_INCLUDED_Vector2_2eproto
#define PROTOBUF_INCLUDED_Vector2_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Vector2_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_Vector2_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_Vector2_2eproto();
namespace zl {
namespace proto {
class Vector2;
class Vector2DefaultTypeInternal;
extern Vector2DefaultTypeInternal _Vector2_default_instance_;
}  // namespace proto
}  // namespace zl
namespace google {
namespace protobuf {
template<> ::zl::proto::Vector2* Arena::CreateMaybeMessage<::zl::proto::Vector2>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace zl {
namespace proto {

// ===================================================================

class Vector2 final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:zl.proto.Vector2) */ {
 public:
  Vector2();
  virtual ~Vector2();

  Vector2(const Vector2& from);

  inline Vector2& operator=(const Vector2& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Vector2(Vector2&& from) noexcept
    : Vector2() {
    *this = ::std::move(from);
  }

  inline Vector2& operator=(Vector2&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Vector2& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Vector2* internal_default_instance() {
    return reinterpret_cast<const Vector2*>(
               &_Vector2_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Vector2* other);
  friend void swap(Vector2& a, Vector2& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Vector2* New() const final {
    return CreateMaybeMessage<Vector2>(nullptr);
  }

  Vector2* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Vector2>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Vector2& from);
  void MergeFrom(const Vector2& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Vector2* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // float X = 1;
  void clear_x();
  static const int kXFieldNumber = 1;
  float x() const;
  void set_x(float value);

  // float Y = 2;
  void clear_y();
  static const int kYFieldNumber = 2;
  float y() const;
  void set_y(float value);

  // @@protoc_insertion_point(class_scope:zl.proto.Vector2)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float x_;
  float y_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Vector2_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Vector2

// float X = 1;
inline void Vector2::clear_x() {
  x_ = 0;
}
inline float Vector2::x() const {
  // @@protoc_insertion_point(field_get:zl.proto.Vector2.X)
  return x_;
}
inline void Vector2::set_x(float value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:zl.proto.Vector2.X)
}

// float Y = 2;
inline void Vector2::clear_y() {
  y_ = 0;
}
inline float Vector2::y() const {
  // @@protoc_insertion_point(field_get:zl.proto.Vector2.Y)
  return y_;
}
inline void Vector2::set_y(float value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:zl.proto.Vector2.Y)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace zl

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_Vector2_2eproto
