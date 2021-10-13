import numpy as np
from copy import copy
#import rbdl
cos=np.cos; sin=np.sin; pi=np.pi

#class Robot(object):
#    def __init__(self, q0, dq0, ndof, dt):
#        self.q = q0    # numpy array (ndof x 1)
#        self.dq = dq0  # numpy array (ndof x 1)
#        self.M = np.zeros([ndof, ndof])
#        self.b = np.zeros(ndof)
#       self.dt = dt
#        self.robot = rbdl.loadModel('../urdf/robot_c.urdf')

#    def send_command(self, tau):
#        rbdl.CompositeRigidBodyAlgorithm(self.robot, self.q, self.M)
#        rbdl.NonlinearEffects(self.robot, self.q, self.dq, self.b)
#        ddq = np.linalg.inv(self.M).dot(tau-self.b)
#        self.q = self.q + self.dt*self.dq
#        self.dq = self.dq + self.dt*ddq

#    def read_joint_positions(self):
#       return self.q

#    def read_joint_velocities(self):
#       return self.dq


def dh(d, theta, a, alpha):
    """
    Matriz de transformacion homogenea asociada a los parametros DH.
    Retorna una matriz 4x4
    """
    sth = np.sin(theta)
    cth = np.cos(theta)
    sa  = np.sin(alpha)
    ca  = np.cos(alpha)
    T = np.array([[cth, -ca*sth,  sa*sth, a*cth],
                   [sth,  ca*cth, -sa*cth, a*sth],
                   [0.0,      sa,      ca,     d],
                   [0.0,     0.0,     0.0,   1.0]])
    return T
    
    
def fkine_ur5(q):
    """
    Calcular la cinematica directa del robot UR5 dados sus valores articulares. 
    q es un vector numpy de la forma [q1, q2, q3, q4, q5, q6]
    """
    # Longitudes (en metros)

    # Matrices DH (completar), emplear la funcion dh con los parametros DH para cada articulacion
    m=100
    l1=(7.5/m)
    l2=(12.5/m)
    l3=(12.5/m)
    l4=(6.5/m)
    l5=(13/m)
    # Matrices DH
    T1=dh(l1   ,q[0]     ,0  ,-pi/2)
    T2=dh(0    ,q[1]+pi/2,-l2,0   )
    T3=dh(0    ,q[2]     ,-l3,0    )
    T4=dh(0    ,q[3]-pi/2,0 ,pi/2  )
    T5=dh(l4+l5,q[4]     ,0 ,0     )
    
    # Efector final con respecto a la base
    T = T1.dot(T2).dot(T3).dot(T4).dot(T5)
    return T

def jacobian_ur5(q, delta=0.0001):
    
    # Crear una matriz 3x5
    J = np.zeros((3,2))
    # Transformacion homogenea inicial (usando q)
    T = fkine_ur5(q)    
    # Iteracion para la derivada de cada columna
    for i in range(6):
        # Copiar la configuracion articular inicial
        dq = copy(q)
        # Incrementar la articulacion i-esima usando un delta
        dq[i]=dq[i]+delta
        # Transformacion homogenea luego del incremento (q+delta)
        Ti=fkine_ur5(dq)
        # Aproximacion del Jacobiano de posicion usando diferencias finitas
        J[0,i] = (Ti[0][3]-T[0][3])/delta;
        #J[1,i]= (Ti[1][3]-T[1][3])/delta;
        #J[2,i] = (Ti[2][3]-T[2][3])/delta;        
    return J

def ikine_ur5(xdes, q0):
    """
    Calcular la cinematica inversa de UR5 numericamente a partir de la configuracion articular inicial de q0. 
    """    
    epsilon  = 0.0001
    max_iter = 1000
   
    q  = copy(q0)
    for i in range(max_iter):
            # Main loop
            J=jacobian_ur5(q)           
            f=fkine_ur5(q)
            e=xdes-f[0:3,3]
            q=q+np.dot(np.linalg.pinv(J), e)
            #Condicion de termino
            if (np.linalg.norm(e)<epsilon):
                break            
            
    return q
