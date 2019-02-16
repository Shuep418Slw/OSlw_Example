import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('MNIST_data', one_hot=True)
import numpy as np
tf.set_random_seed(1)

# 参数设置
BATCH_SIZE = 256
TIME_STEP = 28
INPUT_SIZE = 28
LR = 0.001
NUM_UNITS = 128
ITERATIONS=50000         # 迭代次数
N_CLASSES=10            # 输出大小，0-9十个数字的概率

# 定义 placeholders 以便接收x,y
train_x = tf.placeholder(tf.float32, [None, TIME_STEP * INPUT_SIZE])       # 维度是[BATCH_SIZE，TIME_STEP * INPUT_SIZE]
image = tf.reshape(train_x, [-1, TIME_STEP, INPUT_SIZE])                   # 输入的是二维数据，将其还原为三维，维度是[BATCH_SIZE, TIME_STEP, INPUT_SIZE]
train_y = tf.placeholder(tf.int32, [None, N_CLASSES])

# 定义RNN（LSTM）结构
rnn_cell = tf.nn.rnn_cell.GRUCell(num_units=NUM_UNITS,activation=tf.nn.relu6,
                                  kernel_initializer=tf.truncated_normal_initializer(stddev=1./NUM_UNITS),
                                  bias_initializer=tf.constant_initializer(0.1)
                                  )

outputs,final_state = tf.nn.dynamic_rnn(
    cell=rnn_cell,              # 选择传入的cell
    inputs=image,               # 传入的数据
    initial_state=None,         # 初始状态
    dtype=tf.float32,           # 数据类型
    time_major=False,           # False: (batch, time step, input); True: (time step, batch, input)，这里根据image结构选择False
)

#output = tf.layers.dense(inputs=outputs[:, -1, :], units=N_CLASSES,name='W2')

W2=tf.Variable(tf.random_normal([NUM_UNITS, N_CLASSES],stddev=0.1))
B2=tf.Variable(tf.constant(0.1,dtype=tf.float32,shape=(1,N_CLASSES)))
output = tf.matmul(outputs[:, -1, :], W2) + B2
predication = tf.nn.softmax(output)

tv = tf.trainable_variables()#得到所有可以训练的参数，即所有trainable=True 的tf.Variable/tf.get_variable
regularization_cost = 0.0005* tf.reduce_sum([ tf.nn.l2_loss(v) for v in tv ]) #0.001是lambda超参数

loss = tf.losses.softmax_cross_entropy(onehot_labels=train_y, logits=output) +regularization_cost     # 计算loss
train_op = tf.train.AdamOptimizer(LR).minimize(loss)      #选择优化方法

correct_prediction = tf.equal(tf.argmax(train_y, axis=1),tf.argmax(output, axis=1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction,'float'))  #计算正确率

sess = tf.Session()
sess.run(tf.global_variables_initializer())     # 初始化计算图中的变量

print(sess.run(W2))
print('-----------------')
print(sess.run(rnn_cell.weights[0]).shape)
print('-----------------')
print(sess.run(rnn_cell.weights[1]).shape)
print('-----------------')
print(sess.run(rnn_cell.weights[2]).shape)
print('-----------------')
print(sess.run(rnn_cell.weights[3]).shape)
for step in range(ITERATIONS):    # 开始训练
    x, y = mnist.train.next_batch(BATCH_SIZE)
    x=np.clip(x*np.array(1000),0,1)
    _, loss_ = sess.run([train_op, loss], {train_x: x, train_y: y})
    if step % 500 == 0:      # test（validation）
        test_x, test_y = mnist.test.next_batch(5000)
        test_x = np.clip(test_x * np.array(1000), 0, 1)
        accuracy_ = sess.run(accuracy, {train_x: test_x, train_y: test_y})
        print('train loss: %.4f' % loss_, '| test accuracy: %.5f' % accuracy_)




W_RU=sess.run(rnn_cell.weights[0])
B_RU=sess.run(rnn_cell.weights[1])
W_core=sess.run(rnn_cell.weights[2])
B_core=sess.run(rnn_cell.weights[3])
W_f=sess.run(W2)
B_f=sess.run(B2)

xs_test, ys_test = mnist.train.next_batch(1)
xs_test=np.clip(xs_test*np.array(1000),0,1)
y_pre = sess.run(predication, feed_dict={train_x: xs_test})
np.savez('RnnData',W_RU=W_RU,B_RU=B_RU,W_core=W_core,B_core=B_core,W_f=W_f,B_f=B_f,\
         xin=xs_test,ypre=y_pre,yref=ys_test)

