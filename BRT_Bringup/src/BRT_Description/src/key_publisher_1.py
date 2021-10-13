#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from sensor_msgs.msg import JointState
from markers import *
from BraccioDEV import *

global press_key
press_key = "0"

def callback(msg):

    global press_key
    press_key = msg.data


if __name__ == '__main__':

    rospy.init_node("testForwardKinematics")
    pub = rospy.Publisher('joint_states', JointState, queue_size=1000)
    bmarker = BallMarker(color['GREEN'])
    rospy.Subscriber("/keys", String, callback)

    z = [3.14, 1.7, 1.7,3.14,2.8]
    q = [0, 0, 0, 0, 0, 0]

    # Joint names
    jnames = ['base_joint','shoulder_joint', 'elbow_joint', 'wrist_pitch_joint','wrist_roll_joint', 'gripper_joint']
   # Joint Configuration

    # Object (message) whose type is JointState
    jstate = JointState()
    # Set values to the message
    jstate.header.stamp = rospy.Time.now()
    jstate.name = jnames
    # Add the head joint value (with value 0) to the joints
    jstate.position = q
    # Loop rate (in Hz)
    rate = rospy.Rate(100)

while not rospy.is_shutdown():
            
        if press_key=="q":
            if q[0]<= z[0]:
                q[0] = q[0]+0.05
                
            
        if press_key=="a":
            if q[0]>= z[1]:
                q[0] = q[0]-0.05

        if press_key=="w":
            if q[1]<= z[0]:
                q[1] = q[1]+0.05
    
        if press_key=="s":
            if q[1]>= z[1]:
                q[1] = q[1]-0.05

        if press_key=="e":
            if q[2]<= z[2]:
                q[2] = q[2]+0.05
        
        if press_key=="d":
            if q[2]>= z[3]:
                q[2] = q[2]-0.05

        if press_key=="r":
            if q[3]<= z[0]:
                q[3] = q[3]+0.05

        if press_key=="f":
            if q[3]>= z[1]:
                q[3] = q[3]-0.05

        if press_key=="t":
            if q[4]<= z[0]:
                q[4] = q[4]+0.05

        if press_key=="g":
            if q[5]>= z[1]:
                q[4] = q[4]-0.05

        if press_key=="y":
            if q[5]<= z[0]:
                q[5] = q[5]+0.05
       
        if press_key=="h":
            if q[5]>= z[1]:
                q[5] = q[5]-0.05


        T = fkine_BRT(q)
        bmarker.position(T)
        '''
        print(q)
        '''
        jstate = JointState()

        jstate.header.stamp = rospy.Time.now()
        jstate.name = jnames
        jstate.position = q
        pub.publish(jstate)
        rate.sleep()
