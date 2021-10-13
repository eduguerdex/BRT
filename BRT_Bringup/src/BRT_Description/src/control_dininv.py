#!/usr/bin/env python

import rospy
from sensor_msgs.msg import JointState
from markers import *
from ManoDEV import *
from roslib import packages
import rbdl


rospy.init_node("control_inv")
pub = rospy.Publisher('joint_states', JointState, queue_size=1000)
bmarker_actual  = BallMarker(color['RED'])
bmarker_deseado = BallMarker(color['GREEN'])
# Archivos donde se almacenara los datos
fqact = open("/tmp/qactual.txt", "w")
fqdes = open("/tmp/qdeseado.txt", "w")
fxact = open("/tmp/xactual.txt", "w")
fxdes = open("/tmp/xdeseado.txt", "w")

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
# Aceleracion inicial
ddq = np.array([0., 0., 0., 0., 0., 0.])
# Configuracion articular deseada
qdes = np.array([-0.12, -0.16, -0.31, 1.04, 1.02, -0.59])
# Velocidad articular deseada
dqdes = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
# Aceleracion articular deseada
ddqdes = np.array([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
# =============================================================

# Posicion resultante de la configuracion articular deseada
xdes = fkine_ur5(qdes)[0:3,3]

# Copiar la configuracion articular en el mensaje a ser publicado

jstate.position = q
pub.publish(jstate)

# Modelo RBDL
modelo = rbdl.loadModel('../urdf/robot_c.urdf')
ndof   = modelo.q_size     # Grados de libertad
zeros = np.zeros(ndof)     # Vector de ceros

# Frecuencia del envio (en Hz)
freq = 20
dt = 1.0/freq
rate = rospy.Rate(freq)

# Simulador dinamico del robot
robot = Robot(q, dq, ndof, dt)
# Bucle de ejecucion continua
t = 0.0

# Se definen las ganancias del controlador
valores = 0.1*np.array([1.0, 1.0, 1.0, 1.0, 1.0, 1.0])
Kp = np.diag(valores)
Kd = 2*np.sqrt(Kp)

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
    # Arrays numpy
    zeros = np.zeros(ndof)          # Vecto
    tau   = np.zeros(ndof)          # Para torque
    g     = np.zeros(ndof)          # Para la gravedad
    c     = np.zeros(ndof)          # Para el vector de Coriolis+centrifuga
    M     = np.zeros([ndof, ndof])  # Para la matriz de inercia
    e     = np.eye(6)               # Vector identidad
 
    # Torque dada la configuracion del robot
    rbdl.InverseDynamics(modelo, q, dq, ddq, tau)
 
    # Parte 1: Calcular vector de gravedad, vector de Coriolis/centrifuga,
    # Gravedad
    rbdl.InverseDynamics(modelo, q, zeros, zeros, g)

    # coriolis
    rbdl.InverseDynamics(modelo, q, dq, zeros, c)
    Co=c-g

    # y matriz M usando solamente InverseDynamics
 
    for i in range(6): 
        mi = np.zeros(ndof)
        rbdl.InverseDynamics(modelo, q, zeros, e[i,:], mi)
        M[i,:]=mi-g
    
    print("Matriz:")
    print(np.round(M,2))
   
    e=qdes-q
    de=dqdes-dq
    dde=ddqdes-ddq
    Kde=Kd.dot(de)
    u=M.dot(ddqdes+Kde+Kp.dot(e))+Co.dot(ddq)+g
    
    if np.linalg.norm(e)<0.01:
        break
    
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
