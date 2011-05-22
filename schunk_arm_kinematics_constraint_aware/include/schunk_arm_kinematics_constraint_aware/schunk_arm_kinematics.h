#ifndef __SCHUNK_ARM_KINEMATICS__
#define __SCHUNK_ARM_KINEMATICS__

#include <cstring>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf_conversions/tf_kdl.h>
#include <tf/transform_datatypes.h>
#include <kdl_parser/kdl_parser.hpp>
#include <kdl/jntarray.hpp>
#include <kdl/chainiksolverpos_nr_jl.hpp>
#include <kdl/chainiksolvervel_pinv.hpp>
#include <kdl/chainiksolvervel_pinv_givens.hpp>
#include <kdl/chainiksolvervel_wdls.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kinematics_msgs/GetPositionFK.h>
#include <kinematics_msgs/GetPositionIK.h>
#include <kinematics_msgs/GetKinematicSolverInfo.h>
#include <kinematics_msgs/KinematicSolverInfo.h>
#include "schunk_arm_kinematics_constraint_aware/GetVelocityIK.h"

class SchunkArmKinematics {
    public:
        SchunkArmKinematics();
        bool init();

    protected:
        ros::NodeHandle nh, nh_private;
        std::string root_name, tip_name;
        KDL::JntArray joint_min, joint_max;
        KDL::Chain chain;
        unsigned int num_joints;
        unsigned int num_links;

        KDL::ChainFkSolverPos_recursive* fk_solver;
        KDL::ChainIkSolverPos_NR_JL *ik_solver_pos;
        KDL::ChainIkSolverVel* ik_solver_vel;

        ros::ServiceServer ik_service, ik_vel_service, ik_solver_info_service;
        ros::ServiceServer fk_service,fk_solver_info_service;

        tf::TransformListener tf_listener;

        kinematics_msgs::KinematicSolverInfo info;

        bool loadModel(const std::string xml);
        bool readJoints(urdf::Model &robot_model);
        int getJointIndex(const std::string &name);
        int getKDLSegmentIndex(const std::string &name);

        /**
         * @brief This is the basic IK service method that will compute and return an IK solution.
         * @param A request message. See service definition for GetPositionIK for more information on this message.
         * @param The response message. See service definition for GetPositionIK for more information on this message.
         */
        bool getPositionIK(kinematics_msgs::GetPositionIK::Request &request,
                           kinematics_msgs::GetPositionIK::Response &response);

        /**
		 * @brief This is the basic IK service method that will compute and return an IK solution.
		 * @param A request message. See service definition for GetPositionIK for more information on this message.
		 * @param The response message. See service definition for GetPositionIK for more information on this message.
		 */
		bool getVelocityIK(schunk_arm_kinematics_constraint_aware::GetVelocityIK::Request &request,
				schunk_arm_kinematics_constraint_aware::GetVelocityIK::Response &response);

        /**
         * @brief This is the basic kinematics info service that will return information about the kinematics node.
         * @param A request message. See service definition for GetKinematicSolverInfo for more information on this message.
         * @param The response message. See service definition for GetKinematicSolverInfo for more information on this message.
         */
        bool getIKSolverInfo(kinematics_msgs::GetKinematicSolverInfo::Request &request,
                             kinematics_msgs::GetKinematicSolverInfo::Response &response);

        /**
         * @brief This is the basic kinematics info service that will return information about the kinematics node.
         * @param A request message. See service definition for GetKinematicSolverInfo for more information on this message.
         * @param The response message. See service definition for GetKinematicSolverInfo for more information on this message.
         */
        bool getFKSolverInfo(kinematics_msgs::GetKinematicSolverInfo::Request &request,
                             kinematics_msgs::GetKinematicSolverInfo::Response &response);

        /**
         * @brief This is the basic forward kinematics service that will return information about the kinematics node.
         * @param A request message. See service definition for GetPositionFK for more information on this message.
         * @param The response message. See service definition for GetPositionFK for more information on this message.
         */
        bool getPositionFK(kinematics_msgs::GetPositionFK::Request &request,
                           kinematics_msgs::GetPositionFK::Response &response);
};

#endif
