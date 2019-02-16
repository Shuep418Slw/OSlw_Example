from __future__ import print_function
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import numpy as np

mnist = input_data.read_data_sets('MNIST_data', one_hot=True)

def compute_accuracy(v_xs, v_ys):
    global prediction
    y_pre = sess.run(prediction, feed_dict={xs: v_xs, keep_prob: 1})
    correct_prediction = tf.equal(tf.argmax(y_pre,1), tf.argmax(v_ys,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    result = sess.run(accuracy, feed_dict={xs: v_xs, ys: v_ys, keep_prob: 1})
    return result

def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)

def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='VALID')#不是SAME

def avg_pool_2x2(x):
    return tf.nn.avg_pool(x, ksize=[1,2,2,1], strides=[1,2,2,1], padding='SAME')

def avg_pool_4x4(x):

    return tf.nn.avg_pool(x, ksize=[1,4,4,1], strides=[1,4,4,1], padding='SAME')

xs = tf.placeholder(tf.float32, [None, 784])   # 28x28
ys = tf.placeholder(tf.float32, [None, 10])
keep_prob = tf.placeholder(tf.float32)
x_image = tf.reshape(xs, [-1, 28, 28, 1])

W_conv1 = weight_variable([5,5, 1,32]) 
b_conv1 = bias_variable([32])
h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1) 
h_pool1 = avg_pool_2x2(h_conv1)                         
W_conv2 = weight_variable([5,5, 32, 64]) 
b_conv2 = bias_variable([64])
h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2) 
h_pool2 = avg_pool_2x2(h_conv2)                                       


W_fc1 = weight_variable([4*4*64, 256])#1024*1024 W25Q16装不下
b_fc1 = bias_variable([256])

h_pool2_flat = tf.reshape(h_pool2, [-1, 4*4*64])
h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)


W_fc2 = weight_variable([256, 10])
b_fc2 = bias_variable([10])
prediction = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

cross_entropy = tf.reduce_mean(-tf.reduce_sum(ys * tf.log(prediction),
                                              reduction_indices=[1]))      
train_step = tf.train.AdamOptimizer(4e-5).minimize(cross_entropy)

sess = tf.Session()
init = tf.global_variables_initializer()
sess.run(init)

for i in range(20000):
    batch_xs, batch_ys = mnist.train.next_batch(100)
    sess.run(train_step, feed_dict={xs: np.clip(batch_xs*np.array(1000),0,1)-0.5, ys: batch_ys, keep_prob: 0.5})
    if i % 50 == 0:
        print(compute_accuracy(
            np.clip(mnist.test.images[:1000]*np.array(1000),0,1)-0.5, mnist.test.labels[:1000]))


#保存参数
w_conv1_p=sess.run(W_conv1,feed_dict={keep_prob:1})
b_conv1_p=sess.run(b_conv1,feed_dict={keep_prob:1})
w_conv2_p=sess.run(W_conv2,feed_dict={keep_prob:1})
b_conv2_p=sess.run(b_conv2,feed_dict={keep_prob:1})
w_fc1_p=sess.run(W_fc1,feed_dict={keep_prob:1})
b_fc1_p=sess.run(b_fc1,feed_dict={keep_prob:1})
w_fc2_p=sess.run(W_fc2,feed_dict={keep_prob:1})
b_fc2_p=sess.run(b_fc2,feed_dict={keep_prob:1})


#保存一个样本用于验证
xs_test, ys_test = mnist.train.next_batch(1)
xs_test=np.clip(xs_test*np.array(1000),0,1)-0.5
y_pre = sess.run(prediction, feed_dict={xs: xs_test, keep_prob: 1})
np.savez('CnnData',wec1=w_conv1_p,bic1=b_conv1_p,wec2=w_conv2_p,bic2=b_conv2_p,we3=w_fc1_p,bi3=b_fc1_p,we4=w_fc2_p,bi4=b_fc2_p,\
         xin=xs_test,ypre=y_pre,yref=ys_test)