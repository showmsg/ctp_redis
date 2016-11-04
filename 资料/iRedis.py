import redis
import random
import logging
from flask import Flask, redirect

app = Flask(__name__)

rcon = redis.StrictRedis(host='192.168.92.5', db=0, port=6379, password='123456')
prodcons_queue = 'task:prodcons:queue'
pubsub_channel = 'task:pubsub.channel'

@app.route('/')
def index():

    html = """test"""
    return html

@app.route('/prodcons')
def prodcons():
    elem = random.randrange(10)
    rcon.lpush(prodcons_queue, elem)
    logging.info("lpush {} -- {}".format(prodcons_queue, elem))
    return redirect('/')

@app.route('/pubsub')
def pubsub():
    ps = rcon.pubsub()
    ps.subscribe(pubsub_channel)
    elem = random.randrange(10)
    rcon.publish(pubsub_channel, elem)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)

