import tensorflow as tf
import numpy as np

xin=tf.Variable(tf.constant(np.array([-1.,0.,1.]),shape=[1,3]))
we=tf.Variable(tf.constant(np.array([[0.1,0],[-0.2,0.3],[0.4,-0.6]]),shape=[3,2]))
bi=tf.Variable(tf.constant(np.array([0.3,0.1]),shape=[2]))

yout=tf.nn.tanh(tf.matmul(xin,we)+bi)

g_we = tf.gradients(yout,we)
g_bi = tf.gradients(yout,bi)
g_x=tf.gradients(yout,xin)



sess=tf.Session()
sess.run(tf.global_variables_initializer())

print(sess.run(yout))

print(sess.run(g_we))
print(sess.run(g_bi))
print(sess.run(g_x))