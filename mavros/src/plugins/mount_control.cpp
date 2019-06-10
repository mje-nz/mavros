/**
 * @brief MountControl plugin
 * @file mount_control.cpp
 * @author Matthew Edwards (matthew@matthewedwards.co.nz)
 *
 * @addtogroup plugin
 * @{
 */
/*
 * Copyright 2017 Matthew Edwards
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */
#include <mavros/mavros_plugin.h>

#include <mavros_msgs/CommandLong.h>
#include <mavros_msgs/MountControl.h>


namespace mavros {
namespace std_plugins {
/**
 * @brief Mount control plugin.
 *
 * Controls gimbal/antenna mount.
 */
class MountControlPlugin : public plugin::PluginBase {
public:
	MountControlPlugin() :
		mount_control_nh("~")
	{ }

	void initialize(UAS &uas_)
	{
		PluginBase::initialize(uas_);
        mount_control_sub = mount_control_nh.subscribe("mount_control", 10, &MountControlPlugin::mount_control_cb, this);
	}

	Subscriptions get_subscriptions() {
		return {};
	}

private:
	ros::NodeHandle mount_control_nh;
	ros::Subscriber mount_control_sub;

	void mount_control_cb(const mavros_msgs::MountControl::ConstPtr &msg) {
		try {
			auto client = mount_control_nh.serviceClient<mavros_msgs::CommandLong>("cmd/command");

			mavros_msgs::CommandLong cmd {};

			cmd.request.command = utils::enum_value(mavlink::common::MAV_CMD::DO_MOUNT_CONTROL);
			cmd.request.param1 = msg->pitch;
			cmd.request.param2 = msg->roll;
			cmd.request.param3 = msg->yaw;
			cmd.request.param4 = msg->alt;
			cmd.request.param5 = msg->lat;
			cmd.request.param6 = msg->lon;
			cmd.request.param7 = msg->mode;

			bool success = client.call(cmd);
			if (!success) {
				ROS_ERROR_NAMED("mount_control", "Service call failed");
			}
		}
		catch (ros::InvalidNameException &ex) {
			ROS_ERROR_NAMED("mount_control", "Could not connect to command service: %s", ex.what());
		}
	}
};
}	// namespace std_plugins
}	// namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::MountControlPlugin, mavros::plugin::PluginBase)
