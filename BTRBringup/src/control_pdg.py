#!/usr/bin/env python

import rospy
from sensor_msgs.msg import JointState
from markers import *
from ManoDEV import *
from roslib import packages
 
import rbdl
 
rospy.init_node("control_pdg")
pub = rospy.Publisher('joint_states', JointState, queue_size=1000)
bmarker_actual  = BallMarker(color['RED'])
bmarker_deseado = BallMarker(color['GREEN'])

# Archivos donde se almacenara los datos
fqact = open("/tmp/qactual.dat", "w")
fqdes = open("/tmp/qdeseado.dat", "w")
fxact = open("/tmp/xactual.dat", "w")
fxdes = open("/tmp/xdeseado.dat", "w")
# Nombres de las articulaciones
jnames = ['base-0_joint', '0-1_joint', '1-2_joint','2-4_joint', '4-5_joint', '5-6_joint']

# Objeto (mensaje) de tipo JointState
jstate = JointState()
# Valores del mensaje
jstate.header.stamp = rospy.Time.now()
jstate.name = jnames

# =============================================================
# Configuracion articular inicial (en radianes)
q = np.array([0, 0.0, -0.0, 0.0, 0.0, 0.15])
# Velocidad inicial
dq = np.array([0., 0., 0., 0., 0., 0.])

# Configuracion articular deseada
qdes = np.array([-0.12, -0.16, -0.31, 1.04, 1.02, -0.59])
# =============================================================

# Posicion resultante de la configuracion articular deseada
xdes = fkine_ur5(qdes)[0:3,3]
# Copiar la configuracion articular en el mensaje a ser publicado
jstate.position = q

# Modelo RBDL
modelo = rbdl.loadModel('../urdf/robot_c.urdf')
ndof   = modelo.q_size     # Grados de libertad

# Frecuencia del envio (en Hz)
freq = 20
dt = 1.0/freq
rate = rospy.Rate(freq)

# Simulador dinamico del robot
robot = Robot(q, dq, ndof, dt)

# Se definen las ganancias del controlador
v=1
valores = 0.1*np.array([v, v, v, v, v, v])
Kp = np.diag(valores)
Kd = 2*np.sqrt(Kp)

# Bucle de ejecucion continua
t = 0.0
while not rospy.is_shutdown():

    # Leer valores del simulador
    q  = robot.read_joint_positions()
    dq = robot.read_joint_velocities()
    # Posicion actual del efector final
    x = fkine_ur5(q)[0:3,3]
    # Tiempo actual (necesario como indicador para ROS)
    jstate.header.stamp = rospy.Time.now()

      # Almacenamiento de datos
    fxact.write(str(t)+' '+str(x[0])+' '+str(x[1])+' '+str(x[2])+'\n')
    fxdes.write(str(t)+' '+str(xdes[0])+' '+str(xdes[1])+' '+
                str(xdes[2])+'\n')
    fqact.write(str(t)+' '+str(q[0])+' '+str(q[1])+' '+ str(q[2])+
                ' '+ str(q[3])+' '+str(q[4])+' '+str(q[5])+'\n ')
    fqdes.write(str(t)+' '+str(qdes[0])+' '+str(qdes[1])+' '+ str(qdes[2])+
                ' '+ str(qdes[3])+' '+str(qdes[4])+' '+str(qdes[5])+'\n ')

    # ----------------------------
     # Control dinamico (COMPLETAR)
    # ----------------------------
    u = np.zeros(ndof)   # Reemplazar por la ley de control
    zeros=np.zeros(ndof)
    g=np.zeros(ndof)
    rbdl.InverseDynamics(modelo, q, zeros, zeros, g)
 
    u = g + Kp. dot (qdes -q)- Kd.dot(dq)

    print("u:")
    print(np.round(u,2))

    # Simulacion del robot
    robot.send_command(u)

    # Publicacion del mensaje
    jstate.position = q
    pub.publish(jstate)
    bmarker_deseado.xyz(xdes)
    bmarker_actual.xyz(x)
    t = t+dt
    # Esperar hasta la siguiente  iteracion
    rate.sleep()

fqact.close()
fqdes.close()
fxact.close()
fxdes.close()