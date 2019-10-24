// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Vector3.proto

#ifndef PROTOBUF_INCLUDED_Vector3_2eproto
#define PROTOBUF_INCLUDED_Vector3_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_Vector3_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_Vector3_2eproto {
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
void AddDescriptors_Vector3_2eproto();
namespace zl {
namespace proto {
class Vector3;
class Vector3DefaultTypeInternal;
extern Vector3DefaultTypeInternal _Vector3_default_instance_;
}  // namespace proto
}  // namespace zl
namespace google {
namespace protobuf {
template<> ::zl::proto::Vector3* Arena::CreateMaybeMessage<::zl::proto::Vector3>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace zl {
namespace proto {

// ===================================================================

class Vector3 final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:zl.proto.Vector3) */ {
 public:
  Vector3();
  virtual ~Vector3();

  Vector3(const Vector3& from);

  inline Vector3& operator=(const Vector3& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Vector3(Vector3&& from) noexcept
    : Vector3() {
    *this = ::std::move(from);
  }

  inline Vector3& operator=(Vector3&& from) noexcept {
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
  static const Vector3& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Vector3* internal_default_instance() {
    return reinterpret_cast<const Vector3*>(
               &_Vector3_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Vector3* other);
  friend void swap(Vector3& a, Vector3& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Vector3* New() const final {
    return CreateMaybeMessage<Vector3>(nullptr);
  }

  Vector3* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Vector3>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Vector3& from);
  void MergeFrom(const Vector3& from);
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
  void InternalSwap(Vector3* other);
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

  // float Z = 3;
  void clear_z();
  static const int kZFieldNumber = 3;
  float z() const;
  void set_z(float value);

  // @@protoc_insertion_point(class_scope:zl.proto.Vector3)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  float x_;
  float y_;
  float z_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Vector3_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Vector3

// float X = 1;
inline void Vector3::clear_x() {
  x_ = 0;
}
inline float Vector3::x() const {
  // @@protoc_insertion_point(field_get:zl.proto.Vector3.X)
  return x_;
}
inline void Vector3::set_x(float value) {
  
  x_ = value;
  // @@protoc_insertion_point(field_set:zl.proto.Vector3.X)
}

// float Y = 2;
inline void Vector3::clear_y() {
  y_ = 0;
}
inline float Vector3::y() const {
  // @@protoc_insertion_point(field_get:zl.proto.Vector3.Y)
  return y_;
}
inline void Vector3::set_y(float value) {
  
  y_ = value;
  // @@protoc_insertion_point(field_set:zl.proto.Vector3.Y)
}

// float Z = 3;
inline void Vector3::clear_z() {
  z_ = 0;
}
inline float Vector3::z() const {
  // @@protoc_insertion_point(field_get:zl.proto.Vector3.Z)
  return z_;
}
inline void Vector3::set_z(float value) {
  
  z_ = value;
  // @@protoc_insertion_point(field_set:zl.proto.Vector3.Z)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace zl

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_Vector3_2eproto
