#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__BatteryInfo() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__BatteryInfo__init(msg: *mut BatteryInfo) -> bool;
    fn urc_msgs__msg__BatteryInfo__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BatteryInfo>, size: usize) -> bool;
    fn urc_msgs__msg__BatteryInfo__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BatteryInfo>);
    fn urc_msgs__msg__BatteryInfo__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BatteryInfo>, out_seq: *mut rosidl_runtime_rs::Sequence<BatteryInfo>) -> bool;
}

// Corresponds to urc_msgs__msg__BatteryInfo
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BatteryInfo {

    // This member is not documented.
    #[allow(missing_docs)]
    pub cell_voltage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cell_charge_percentage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cell_discharge_current: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cell_temperature: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub cell_voltages: rosidl_runtime_rs::Sequence<f32>,

}



impl Default for BatteryInfo {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__BatteryInfo__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__BatteryInfo__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BatteryInfo {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__BatteryInfo__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__BatteryInfo__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__BatteryInfo__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BatteryInfo {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BatteryInfo where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/BatteryInfo";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__BatteryInfo() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__StatusLightCommand() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__StatusLightCommand__init(msg: *mut StatusLightCommand) -> bool;
    fn urc_msgs__msg__StatusLightCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StatusLightCommand>, size: usize) -> bool;
    fn urc_msgs__msg__StatusLightCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StatusLightCommand>);
    fn urc_msgs__msg__StatusLightCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StatusLightCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<StatusLightCommand>) -> bool;
}

// Corresponds to urc_msgs__msg__StatusLightCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StatusLightCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub color: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

}

impl StatusLightCommand {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const BLUE: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const GREEN: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const RED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const OFF: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ON: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const BLINK: u8 = 2;

}


impl Default for StatusLightCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__StatusLightCommand__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__StatusLightCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StatusLightCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__StatusLightCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__StatusLightCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__StatusLightCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StatusLightCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StatusLightCommand where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/StatusLightCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__StatusLightCommand() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__Waypoint() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__Waypoint__init(msg: *mut Waypoint) -> bool;
    fn urc_msgs__msg__Waypoint__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Waypoint>, size: usize) -> bool;
    fn urc_msgs__msg__Waypoint__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Waypoint>);
    fn urc_msgs__msg__Waypoint__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Waypoint>, out_seq: *mut rosidl_runtime_rs::Sequence<Waypoint>) -> bool;
}

// Corresponds to urc_msgs__msg__Waypoint
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Waypoint {

    // This member is not documented.
    #[allow(missing_docs)]
    pub latitude: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub longitude: f64,

}



impl Default for Waypoint {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__Waypoint__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__Waypoint__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Waypoint {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__Waypoint__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__Waypoint__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__Waypoint__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Waypoint {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Waypoint where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/Waypoint";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__Waypoint() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__GridLocation() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__GridLocation__init(msg: *mut GridLocation) -> bool;
    fn urc_msgs__msg__GridLocation__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GridLocation>, size: usize) -> bool;
    fn urc_msgs__msg__GridLocation__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GridLocation>);
    fn urc_msgs__msg__GridLocation__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GridLocation>, out_seq: *mut rosidl_runtime_rs::Sequence<GridLocation>) -> bool;
}

// Corresponds to urc_msgs__msg__GridLocation
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GridLocation {

    // This member is not documented.
    #[allow(missing_docs)]
    pub x: u16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: u16,

}



impl Default for GridLocation {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__GridLocation__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__GridLocation__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GridLocation {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__GridLocation__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__GridLocation__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__GridLocation__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GridLocation {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GridLocation where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/GridLocation";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__GridLocation() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__OrientationPoses() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__OrientationPoses__init(msg: *mut OrientationPoses) -> bool;
    fn urc_msgs__msg__OrientationPoses__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<OrientationPoses>, size: usize) -> bool;
    fn urc_msgs__msg__OrientationPoses__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<OrientationPoses>);
    fn urc_msgs__msg__OrientationPoses__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<OrientationPoses>, out_seq: *mut rosidl_runtime_rs::Sequence<OrientationPoses>) -> bool;
}

// Corresponds to urc_msgs__msg__OrientationPoses
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OrientationPoses {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Pose>,

}



impl Default for OrientationPoses {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__OrientationPoses__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__OrientationPoses__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for OrientationPoses {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__OrientationPoses__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__OrientationPoses__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__OrientationPoses__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for OrientationPoses {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for OrientationPoses where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/OrientationPoses";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__OrientationPoses() }
  }
}


#[link(name = "urc_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__RoverPoses() -> *const std::ffi::c_void;
}

#[link(name = "urc_msgs__rosidl_generator_c")]
extern "C" {
    fn urc_msgs__msg__RoverPoses__init(msg: *mut RoverPoses) -> bool;
    fn urc_msgs__msg__RoverPoses__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RoverPoses>, size: usize) -> bool;
    fn urc_msgs__msg__RoverPoses__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RoverPoses>);
    fn urc_msgs__msg__RoverPoses__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RoverPoses>, out_seq: *mut rosidl_runtime_rs::Sequence<RoverPoses>) -> bool;
}

// Corresponds to urc_msgs__msg__RoverPoses
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RoverPoses {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: rosidl_runtime_rs::Sequence<rosidl_runtime_rs::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Pose>,

}



impl Default for RoverPoses {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !urc_msgs__msg__RoverPoses__init(&mut msg as *mut _) {
        panic!("Call to urc_msgs__msg__RoverPoses__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RoverPoses {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__RoverPoses__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__RoverPoses__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { urc_msgs__msg__RoverPoses__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RoverPoses {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RoverPoses where Self: Sized {
  const TYPE_NAME: &'static str = "urc_msgs/msg/RoverPoses";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__urc_msgs__msg__RoverPoses() }
  }
}


