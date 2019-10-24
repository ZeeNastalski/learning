// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Session.proto

#ifndef PROTOBUF_INCLUDED_Session_2eproto
#define PROTOBUF_INCLUDED_Session_2eproto

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
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include "player/Profile.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Session_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_Session_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_Session_2eproto();
namespace zl {
namespace proto {
class Session;
class SessionDefaultTypeInternal;
extern SessionDefaultTypeInternal _Session_default_instance_;
class Session_ProfilesByProfileIdEntry_DoNotUse;
class Session_ProfilesByProfileIdEntry_DoNotUseDefaultTypeInternal;
extern Session_ProfilesByProfileIdEntry_DoNotUseDefaultTypeInternal _Session_ProfilesByProfileIdEntry_DoNotUse_default_instance_;
}  // namespace proto
}  // namespace zl
namespace google {
namespace protobuf {
template<> ::zl::proto::Session* Arena::CreateMaybeMessage<::zl::proto::Session>(Arena*);
template<> ::zl::proto::Session_ProfilesByProfileIdEntry_DoNotUse* Arena::CreateMaybeMessage<::zl::proto::Session_ProfilesByProfileIdEntry_DoNotUse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace zl {
namespace proto {

// ===================================================================

class Session_ProfilesByProfileIdEntry_DoNotUse : public ::google::protobuf::internal::MapEntry<Session_ProfilesByProfileIdEntry_DoNotUse, 
    ::google::protobuf::int32, ::zl::proto::player::Profile,
    ::google::protobuf::internal::WireFormatLite::TYPE_INT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
static bool _ParseMap(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  typedef ::google::protobuf::internal::MapEntry<Session_ProfilesByProfileIdEntry_DoNotUse, 
    ::google::protobuf::int32, ::zl::proto::player::Profile,
    ::google::protobuf::internal::WireFormatLite::TYPE_INT32,
    ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  Session_ProfilesByProfileIdEntry_DoNotUse();
  Session_ProfilesByProfileIdEntry_DoNotUse(::google::protobuf::Arena* arena);
  void MergeFrom(const Session_ProfilesByProfileIdEntry_DoNotUse& other);
  static const Session_ProfilesByProfileIdEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const Session_ProfilesByProfileIdEntry_DoNotUse*>(&_Session_ProfilesByProfileIdEntry_DoNotUse_default_instance_); }
  void MergeFrom(const ::google::protobuf::Message& other) final;
  ::google::protobuf::Metadata GetMetadata() const;
};

// -------------------------------------------------------------------

class Session final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:zl.proto.Session) */ {
 public:
  Session();
  virtual ~Session();

  Session(const Session& from);

  inline Session& operator=(const Session& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Session(Session&& from) noexcept
    : Session() {
    *this = ::std::move(from);
  }

  inline Session& operator=(Session&& from) noexcept {
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
  static const Session& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Session* internal_default_instance() {
    return reinterpret_cast<const Session*>(
               &_Session_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Session* other);
  friend void swap(Session& a, Session& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Session* New() const final {
    return CreateMaybeMessage<Session>(nullptr);
  }

  Session* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Session>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Session& from);
  void MergeFrom(const Session& from);
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
  void InternalSwap(Session* other);
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

  // map<int32, .zl.proto.player.Profile> ProfilesByProfileId = 1;
  int profilesbyprofileid_size() const;
  void clear_profilesbyprofileid();
  static const int kProfilesByProfileIdFieldNumber = 1;
  const ::google::protobuf::Map< ::google::protobuf::int32, ::zl::proto::player::Profile >&
      profilesbyprofileid() const;
  ::google::protobuf::Map< ::google::protobuf::int32, ::zl::proto::player::Profile >*
      mutable_profilesbyprofileid();

  // @@protoc_insertion_point(class_scope:zl.proto.Session)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::MapField<
      Session_ProfilesByProfileIdEntry_DoNotUse,
      ::google::protobuf::int32, ::zl::proto::player::Profile,
      ::google::protobuf::internal::WireFormatLite::TYPE_INT32,
      ::google::protobuf::internal::WireFormatLite::TYPE_MESSAGE,
      0 > profilesbyprofileid_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Session_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Session

// map<int32, .zl.proto.player.Profile> ProfilesByProfileId = 1;
inline int Session::profilesbyprofileid_size() const {
  return profilesbyprofileid_.size();
}
inline const ::google::protobuf::Map< ::google::protobuf::int32, ::zl::proto::player::Profile >&
Session::profilesbyprofileid() const {
  // @@protoc_insertion_point(field_map:zl.proto.Session.ProfilesByProfileId)
  return profilesbyprofileid_.GetMap();
}
inline ::google::protobuf::Map< ::google::protobuf::int32, ::zl::proto::player::Profile >*
Session::mutable_profilesbyprofileid() {
  // @@protoc_insertion_point(field_mutable_map:zl.proto.Session.ProfilesByProfileId)
  return profilesbyprofileid_.MutableMap();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace zl

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_Session_2eproto
