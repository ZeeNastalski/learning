// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: EAppMode.proto

#ifndef PROTOBUF_INCLUDED_EAppMode_2eproto
#define PROTOBUF_INCLUDED_EAppMode_2eproto

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
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_EAppMode_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_EAppMode_2eproto {
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
void AddDescriptors_EAppMode_2eproto();
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
namespace zl {
namespace proto {

enum EAppMode {
  UNKNOWN = 0,
  SERVER = 1,
  CLIENT = 2,
  SPECTATOR = 3,
  CONTROLLER_TEST = 4,
  LOCAL_TEST = 5,
  REPLAY_VIEWER = 6,
  GAME_MASTER = 7,
  REMOTE_TEST = 8,
  EAppMode_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::min(),
  EAppMode_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::google::protobuf::int32>::max()
};
bool EAppMode_IsValid(int value);
const EAppMode EAppMode_MIN = UNKNOWN;
const EAppMode EAppMode_MAX = REMOTE_TEST;
const int EAppMode_ARRAYSIZE = EAppMode_MAX + 1;

const ::google::protobuf::EnumDescriptor* EAppMode_descriptor();
inline const ::std::string& EAppMode_Name(EAppMode value) {
  return ::google::protobuf::internal::NameOfEnum(
    EAppMode_descriptor(), value);
}
inline bool EAppMode_Parse(
    const ::std::string& name, EAppMode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<EAppMode>(
    EAppMode_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace zl

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::zl::proto::EAppMode> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::zl::proto::EAppMode>() {
  return ::zl::proto::EAppMode_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_EAppMode_2eproto
