# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: src/urc-software/urc_nanopb/proto/urc.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


DESCRIPTOR = _descriptor.FileDescriptor(
    name='src/urc-software/urc_nanopb/proto/urc.proto',
    package='',
    syntax='proto2',
    serialized_options=None,
    create_key=_descriptor._internal_create_key,
    serialized_pb=b'\n+src/urc-software/urc_nanopb/proto/urc.proto\"\xae\x01\n\x12\x41\
      rmEncodersMessage\x12\x19\n\x11shoulderLiftTicks\x18\x01 \x02(\x05\x12\x19\n\x11\
      shouldSwivelTicks\x18\x02 \x02(\x05\x12\x16\n\x0e\x65lbowLiftTicks\x18\x03 \x02\
      (\x05\x12\x18\n\x10\x65lbowSwivelTicks\x18\x04 \x02(\x05\x12\x16\n\x0ewristLiftTicks\
      \x18\x05 \x02(\x05\x12\x18\n\x10wristSwivelTicks\x18\x06 \x02(\x05\"P\n\x14\x44\
      riveEncodersMessage\x12\x11\n\tleftSpeed\x18\x01 \x01(\x05\x12\x12\n\nrightSpeed\
      \x18\x02 \x01(\x05\x12\x11\n\ttimestamp\x18\x03 \x02(\x05\"\x8e\x01\n\x0e\
      RequestMessage\x12\x14\n\x0crequestSpeed\x18\x01 \x02(\x08\x12\x1a\n\x12\
      requestDiagnostics\x18\x02 \x02(\x08\x12\x11\n\tleftSpeed\x18\x03 \x01\
      (\x05\x12\x12\n\nrightSpeed\x18\x04 \x01(\x05\x12\x10\n\x08\x64uration\
      \x18\x05 \x01(\x05\x12\x11\n\ttimestamp\x18\x06 \x02(\x05\"\xfa\x01\n\n\
      IMUMessage\x12\x11\n\ttimestamp\x18\x01 \x02(\x05\x12\x13\n\x0bquaternionX\
      \x18\x02 \x01(\x02\x12\x13\n\x0bquaternionY\x18\x03 \x01(\x02\x12\x13\n\x0b\
      quaternionZ\x18\x04 \x01(\x02\x12\x13\n\x0bquaternionW\x18\x05 \x01(\x02\x12\x14\n\x0c\
      linearAccelX\x18\x06 \x01(\x02\x12\x14\n\x0clinearAccelY\x18\x07 \x01(\x02\x12\x14\n\x0c\
      linearAccelZ\x18\x08 \x01(\x02\x12\x15\n\rangularAccelR\x18\t \x01(\x02\x12\x15\n\r\
      angularAccelP\x18\n \x01(\x02\x12\x15\n\rangualrAccelY\x18\x0b \x01(\x02\"4\n\x12\
      StatusLightCommand\x12\r\n\x05\x63olor\x18\x01 \x01(\x05\x12\x0f\n\x07\x64isplay\
      \x18\x02 \x01(\x05'
)


_ARMENCODERSMESSAGE = _descriptor.Descriptor(
    name='ArmEncodersMessage',
    full_name='ArmEncodersMessage',
    filename=None,
    file=DESCRIPTOR,
    containing_type=None,
    create_key=_descriptor._internal_create_key,
    fields=[
        _descriptor.FieldDescriptor(
            name='shoulderLiftTicks', full_name='ArmEncodersMessage.shoulderLiftTicks', index=0,
            number=1, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='shouldSwivelTicks', full_name='ArmEncodersMessage.shouldSwivelTicks', index=1,
            number=2, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='elbowLiftTicks', full_name='ArmEncodersMessage.elbowLiftTicks', index=2,
            number=3, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='elbowSwivelTicks', full_name='ArmEncodersMessage.elbowSwivelTicks', index=3,
            number=4, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='wristLiftTicks', full_name='ArmEncodersMessage.wristLiftTicks', index=4,
            number=5, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='wristSwivelTicks', full_name='ArmEncodersMessage.wristSwivelTicks', index=5,
            number=6, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
    ],
    extensions=[
    ],
    nested_types=[],
    enum_types=[
    ],
    serialized_options=None,
    is_extendable=False,
    syntax='proto2',
    extension_ranges=[],
    oneofs=[
    ],
    serialized_start=48,
    serialized_end=222,
)


_DRIVEENCODERSMESSAGE = _descriptor.Descriptor(
    name='DriveEncodersMessage',
    full_name='DriveEncodersMessage',
    filename=None,
    file=DESCRIPTOR,
    containing_type=None,
    create_key=_descriptor._internal_create_key,
    fields=[
        _descriptor.FieldDescriptor(
            name='leftSpeed', full_name='DriveEncodersMessage.leftSpeed', index=0,
            number=1, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='rightSpeed', full_name='DriveEncodersMessage.rightSpeed', index=1,
            number=2, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='timestamp', full_name='DriveEncodersMessage.timestamp', index=2,
            number=3, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
    ],
    extensions=[
    ],
    nested_types=[],
    enum_types=[
    ],
    serialized_options=None,
    is_extendable=False,
    syntax='proto2',
    extension_ranges=[],
    oneofs=[
    ],
    serialized_start=224,
    serialized_end=304,
)


_REQUESTMESSAGE = _descriptor.Descriptor(
    name='RequestMessage',
    full_name='RequestMessage',
    filename=None,
    file=DESCRIPTOR,
    containing_type=None,
    create_key=_descriptor._internal_create_key,
    fields=[
        _descriptor.FieldDescriptor(
            name='requestSpeed', full_name='RequestMessage.requestSpeed', index=0,
            number=1, type=8, cpp_type=7, label=2,
            has_default_value=False, default_value=False,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='requestDiagnostics', full_name='RequestMessage.requestDiagnostics', index=1,
            number=2, type=8, cpp_type=7, label=2,
            has_default_value=False, default_value=False,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='leftSpeed', full_name='RequestMessage.leftSpeed', index=2,
            number=3, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='rightSpeed', full_name='RequestMessage.rightSpeed', index=3,
            number=4, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='duration', full_name='RequestMessage.duration', index=4,
            number=5, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='timestamp', full_name='RequestMessage.timestamp', index=5,
            number=6, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
    ],
    extensions=[
    ],
    nested_types=[],
    enum_types=[
    ],
    serialized_options=None,
    is_extendable=False,
    syntax='proto2',
    extension_ranges=[],
    oneofs=[
    ],
    serialized_start=307,
    serialized_end=449,
)


_IMUMESSAGE = _descriptor.Descriptor(
    name='IMUMessage',
    full_name='IMUMessage',
    filename=None,
    file=DESCRIPTOR,
    containing_type=None,
    create_key=_descriptor._internal_create_key,
    fields=[
        _descriptor.FieldDescriptor(
            name='timestamp', full_name='IMUMessage.timestamp', index=0,
            number=1, type=5, cpp_type=1, label=2,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='quaternionX', full_name='IMUMessage.quaternionX', index=1,
            number=2, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='quaternionY', full_name='IMUMessage.quaternionY', index=2,
            number=3, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='quaternionZ', full_name='IMUMessage.quaternionZ', index=3,
            number=4, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='quaternionW', full_name='IMUMessage.quaternionW', index=4,
            number=5, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='linearAccelX', full_name='IMUMessage.linearAccelX', index=5,
            number=6, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='linearAccelY', full_name='IMUMessage.linearAccelY', index=6,
            number=7, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='linearAccelZ', full_name='IMUMessage.linearAccelZ', index=7,
            number=8, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='angularAccelR', full_name='IMUMessage.angularAccelR', index=8,
            number=9, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='angularAccelP', full_name='IMUMessage.angularAccelP', index=9,
            number=10, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='angualrAccelY', full_name='IMUMessage.angualrAccelY', index=10,
            number=11, type=2, cpp_type=6, label=1,
            has_default_value=False, default_value=float(0),
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
    ],
    extensions=[
    ],
    nested_types=[],
    enum_types=[
    ],
    serialized_options=None,
    is_extendable=False,
    syntax='proto2',
    extension_ranges=[],
    oneofs=[
    ],
    serialized_start=452,
    serialized_end=702,
)


_STATUSLIGHTCOMMAND = _descriptor.Descriptor(
    name='StatusLightCommand',
    full_name='StatusLightCommand',
    filename=None,
    file=DESCRIPTOR,
    containing_type=None,
    create_key=_descriptor._internal_create_key,
    fields=[
        _descriptor.FieldDescriptor(
            name='color', full_name='StatusLightCommand.color', index=0,
            number=1, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
        _descriptor.FieldDescriptor(
            name='display', full_name='StatusLightCommand.display', index=1,
            number=2, type=5, cpp_type=1, label=1,
            has_default_value=False, default_value=0,
            message_type=None, enum_type=None, containing_type=None,
            is_extension=False, extension_scope=None,
            serialized_options=None, file=DESCRIPTOR, create_key=_descriptor._internal_create_key),
    ],
    extensions=[
    ],
    nested_types=[],
    enum_types=[
    ],
    serialized_options=None,
    is_extendable=False,
    syntax='proto2',
    extension_ranges=[],
    oneofs=[
    ],
    serialized_start=704,
    serialized_end=756,
)

DESCRIPTOR.message_types_by_name['ArmEncodersMessage'] = _ARMENCODERSMESSAGE
DESCRIPTOR.message_types_by_name['DriveEncodersMessage'] = _DRIVEENCODERSMESSAGE
DESCRIPTOR.message_types_by_name['RequestMessage'] = _REQUESTMESSAGE
DESCRIPTOR.message_types_by_name['IMUMessage'] = _IMUMESSAGE
DESCRIPTOR.message_types_by_name['StatusLightCommand'] = _STATUSLIGHTCOMMAND
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

ArmEncodersMessage = _reflection.GeneratedProtocolMessageType(
    'ArmEncodersMessage', (_message.Message,), {
        'DESCRIPTOR': _ARMENCODERSMESSAGE,
        '__module__': 'src.urc_software.urc_nanopb.proto.urc_pb2'
        # @@protoc_insertion_point(class_scope:ArmEncodersMessage)
    })
_sym_db.RegisterMessage(ArmEncodersMessage)

DriveEncodersMessage = _reflection.GeneratedProtocolMessageType(
    'DriveEncodersMessage', (_message.Message,), {
        'DESCRIPTOR': _DRIVEENCODERSMESSAGE,
        '__module__': 'src.urc_software.urc_nanopb.proto.urc_pb2'
        # @@protoc_insertion_point(class_scope:DriveEncodersMessage)
    })
_sym_db.RegisterMessage(DriveEncodersMessage)

RequestMessage = _reflection.GeneratedProtocolMessageType('RequestMessage', (_message.Message,), {
    'DESCRIPTOR': _REQUESTMESSAGE,
    '__module__': 'src.urc_software.urc_nanopb.proto.urc_pb2'
    # @@protoc_insertion_point(class_scope:RequestMessage)
})
_sym_db.RegisterMessage(RequestMessage)

IMUMessage = _reflection.GeneratedProtocolMessageType('IMUMessage', (_message.Message,), {
    'DESCRIPTOR': _IMUMESSAGE,
    '__module__': 'src.urc_software.urc_nanopb.proto.urc_pb2'
    # @@protoc_insertion_point(class_scope:IMUMessage)
})
_sym_db.RegisterMessage(IMUMessage)

StatusLightCommand = _reflection.GeneratedProtocolMessageType(
    'StatusLightCommand', (_message.Message,), {
        'DESCRIPTOR': _STATUSLIGHTCOMMAND,
        '__module__': 'src.urc_software.urc_nanopb.proto.urc_pb2'
        # @@protoc_insertion_point(class_scope:StatusLightCommand)
    })
_sym_db.RegisterMessage(StatusLightCommand)


# @@protoc_insertion_point(module_scope)