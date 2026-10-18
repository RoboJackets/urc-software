#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to urc_msgs__msg__BatteryInfo

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub cell_voltages: Vec<f32>,

}



impl Default for BatteryInfo {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BatteryInfo::default())
  }
}

impl rosidl_runtime_rs::Message for BatteryInfo {
  type RmwMsg = super::msg::rmw::BatteryInfo;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        cell_voltage: msg.cell_voltage,
        cell_charge_percentage: msg.cell_charge_percentage,
        cell_discharge_current: msg.cell_discharge_current,
        cell_temperature: msg.cell_temperature,
        cell_voltages: msg.cell_voltages.as_slice().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      cell_voltage: msg.cell_voltage,
      cell_charge_percentage: msg.cell_charge_percentage,
      cell_discharge_current: msg.cell_discharge_current,
      cell_temperature: msg.cell_temperature,
        cell_voltages: msg.cell_voltages.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      cell_voltage: msg.cell_voltage,
      cell_charge_percentage: msg.cell_charge_percentage,
      cell_discharge_current: msg.cell_discharge_current,
      cell_temperature: msg.cell_temperature,
      cell_voltages: msg.cell_voltages.into(),
    }
  }
}


// Corresponds to urc_msgs__msg__StatusLightCommand

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::StatusLightCommand::default())
  }
}

impl rosidl_runtime_rs::Message for StatusLightCommand {
  type RmwMsg = super::msg::rmw::StatusLightCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        color: msg.color,
        state: msg.state,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      color: msg.color,
      state: msg.state,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      color: msg.color,
      state: msg.state,
    }
  }
}


// Corresponds to urc_msgs__msg__Waypoint

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Waypoint::default())
  }
}

impl rosidl_runtime_rs::Message for Waypoint {
  type RmwMsg = super::msg::rmw::Waypoint;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        latitude: msg.latitude,
        longitude: msg.longitude,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      latitude: msg.latitude,
      longitude: msg.longitude,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      latitude: msg.latitude,
      longitude: msg.longitude,
    }
  }
}


// Corresponds to urc_msgs__msg__GridLocation

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GridLocation::default())
  }
}

impl rosidl_runtime_rs::Message for GridLocation {
  type RmwMsg = super::msg::rmw::GridLocation;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        x: msg.x,
        y: msg.y,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      x: msg.x,
      y: msg.y,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      x: msg.x,
      y: msg.y,
    }
  }
}


// Corresponds to urc_msgs__msg__OrientationPoses

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OrientationPoses {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: Vec<geometry_msgs::msg::Pose>,

}



impl Default for OrientationPoses {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::OrientationPoses::default())
  }
}

impl rosidl_runtime_rs::Message for OrientationPoses {
  type RmwMsg = super::msg::rmw::OrientationPoses;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        names: msg.names
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        poses: msg.poses
          .into_iter()
          .map(|elem| geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        names: msg.names
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        poses: msg.poses
          .iter()
          .map(|elem| geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      names: msg.names
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      poses: msg.poses
          .into_iter()
          .map(geometry_msgs::msg::Pose::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to urc_msgs__msg__RoverPoses

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RoverPoses {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub names: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub poses: Vec<geometry_msgs::msg::Pose>,

}



impl Default for RoverPoses {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RoverPoses::default())
  }
}

impl rosidl_runtime_rs::Message for RoverPoses {
  type RmwMsg = super::msg::rmw::RoverPoses;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        names: msg.names
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        poses: msg.poses
          .into_iter()
          .map(|elem| geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        names: msg.names
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        poses: msg.poses
          .iter()
          .map(|elem| geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      names: msg.names
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      poses: msg.poses
          .into_iter()
          .map(geometry_msgs::msg::Pose::from_rmw_message)
          .collect(),
    }
  }
}


